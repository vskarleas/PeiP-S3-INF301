#include "arbres.h"
#include <stdio.h>

/* Somme des valeurs de l'arbre */
int somme_valeurs(arbre a) 
{
    int somme=0;
    if (a != NULL) 
    {
        somme = a->valeur + somme_valeurs(a->gauche) + somme_valeurs(a->droit);
    }
    return somme;
}