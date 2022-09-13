#Program 1
print("Program 1")
l=[]
for i in range (10):
    l.append(input())

while len(l)>0:
    x=l.pop()
    print(x)

#program 2
print("Program 2")
l=[]

#Program 3
print("Program 3")
l=[]
for i in range(10):
    l=l+[input()]

while l != []:
    x=l[-1]
    l=l[:-1]
    print(x)