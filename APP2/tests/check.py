#!/usr/bin/env python3

import sys
import os
from subprocess import check_output, run, Popen, PIPE, CalledProcessError

if len(sys.argv) == 1:
  print("Usage: python {} c  [mem] [silent] (to test C implementation)".format(sys.argv[0]))
  print("    or python {} py [silent] (to test Python implementation)".format(sys.argv[0]))
  sys.exit(1)

PROG = "./main.py -ascii" if 'py' in sys.argv else "timeout 30 ./main"
VALG = 'mem' in sys.argv
SILENT = '-silent' if 'silent' in sys.argv else ''

CHKPROG = "python {}".format(sys.argv[0])
CHKDIR = os.path.dirname(sys.argv[0])
CHKDIR = "." if CHKDIR == "" else CHKDIR
TSTDIR = CHKDIR
TSTFILE=os.path.join(TSTDIR, "LISEZMOI.txt")

print("Directory for tests:", TSTDIR)

# accumulate failed tests in this variable
failed = []

RED=check_output(['tput', 'setaf' ,'1'], text=True)
GREEN=check_output(['tput', 'setaf' ,'2'], text=True)
ORANGE=check_output(['tput', 'setaf' ,'3'], text=True)
BLUE=check_output(['tput', 'setaf' ,'4'], text=True)+check_output(['tput', 'bold'], text=True)
NORMAL=check_output(['tput', 'sgr0'], text=True)

def color(text, color):
    return "{}{}{}".format(color, text, NORMAL)

COL=int(check_output(['tput', 'cols']))
COL -= 20
if COL > 60:
    COL = 60

# accumulate failed tests in this variable
failed = []

def do_test(test_name):

    # using 'yes' command to cancel all keypresses waiting
    try:
        test_file = os.path.join(TSTDIR, test_name+".test")
        if VALG:
            # output valgrind stderr
            print(run("yes | valgrind {} {} {} > /dev/null".format(PROG, SILENT, test_file), capture_output=True, text=True, shell=True, check=True).stderr)
        else:
            run("yes 2> /dev/null | {} {} {} > /dev/null 2>&1".format(PROG, SILENT, test_file), shell=True, check=True)


        print("\r", " "*COL, color("[pass]", GREEN), end='')
        print("\r    Test "+color(test_name, ORANGE), end="")
        print("\r"+color("[+]", GREEN))
    except CalledProcessError as e:
        failed.append(test_name)
        if e.returncode == 1:
            print("\r", " "*COL, color("[FAIL]", RED), end='')
        elif e.returncode == 2:
            print("\r", " "*COL, color("[TRICHE]", RED), end='')
        elif e.returncode == 134:
            print("\r", " "*COL, color("[ASSERTION]", RED), end='')
        elif e.returncode == 139:
            print("\r", " "*COL, color("[SEGFAULT]", RED), end='')
        else:
            print("\r", " "*COL, color("[SOME PROBLEM]", RED), end='')
        print("\r    Test "+color(test_name, ORANGE), end="")
        print("\r"+color("[-]", RED))

print("Getting tests files from", TSTFILE)
with open(TSTFILE) as f:
    for line in f.readlines():
        if line.startswith('-'):
            do_test(line[1:].strip())
        elif "Acte" in line:
            print(color("\n"+line+"=================", BLUE))

print("Finished testing")

if failed:
  print("************")
  print(color(" Failed tests: "+" ".join(failed), RED))
  print("************")

for t in failed:
  print("Press <q> to quit the tests")
  print("Press <r> to restart test '"+color(t, RED)+"' with output")
  print("(then press <q> to continue)")
  key = input()
  if key == "r" : run("{} {}/{}.test 2>&1 | less".format(PROG, TSTDIR, t), shell=True)
