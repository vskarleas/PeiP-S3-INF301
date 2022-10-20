#include "listes.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char texte[] = "{ 1 M { D } { A } ? }{XC 32R !C !} C !";
    sequence_t *seq = malloc(sizeof(sequence_t));
    conversion(texte, seq);
    afficher(seq);
    printf("\n");
}