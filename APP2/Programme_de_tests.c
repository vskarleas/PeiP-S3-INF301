#include "listes.h"
#include <stdio.h>
#include <stdlib.h>

/*
Programme de tester le comportement des nos fonctions avant l'execution de vraies tests.
*/
int main()
{
    char texte[] = "{ 1 M { D } { A } ? }{XC 32R !C !} C !";
    sequence_t *seq = malloc(sizeof(sequence_t));
    conversion(texte, seq); //Changement de l'appele par rapport le test qu'on voudrait faire chaque fois
    afficher(seq);
    printf("\n");
}