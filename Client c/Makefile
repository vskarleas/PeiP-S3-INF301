CC=clang
CFLAGS=-g -Wall -Wextra -Werror

EXEC=client-introduction client-tutoriel client-interactif client-TUTORIEL client-projetX client-crypteMove client-BayOfPigs client-planB client-crypteSeq client-Northwoods client-LostCause client-OneMillion

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-tutoriel: client-tutoriel.o client.o

client-TUTORIEL: client-TUTORIEL.o client.o

client-projetX: client-projetX.o client.o

client-planB: client-planB.o client.o algos_decodage_codage.o

client-crypteMove: client-crypteMove.o client.o algos_decodage_codage.o

client-BayOfPigs: client-BayOfPigs.o client.o algos_decodage_codage.o

client-crypteSeq: client-crypteSeq.o client.o algos_decodage_codage.o

client-LostCause: client-LostCause.o client.o algos_decodage_codage.o

client-OneMillion: client-OneMillion.o client.o algos_decodage_codage.o

client-introduction: client-introduction.o client.o

client.o: client.c client.h

algos_decodage_codage.o: algos_decodage_codage.c algos_decodage_codage.h

client-Northwoods: client-Northwoods.o client.o algos_decodage_codage.o

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
