#include "arbres.h"
#include <stdbool.h>
#include <stdio.h>

arbre inserer_rec(arbre a) //, int n
{
    return a;
}

void inserer_abr(arbre *a_p, int n) {
    noeud *tmp = NULL;
    if (!(*a_p))
    {
        tmp = (noeud *)malloc(sizeof(noeud));
        tmp->gauche = NULL;
        tmp->droit = NULL;
        tmp->valeur = n;
        *a_p = tmp;
        return;
    }
    if (n < (*a_p)->valeur)
    {
        inserer_abr(&(*a_p)->gauche, n);
    }
    else if (n > (*a_p)->valeur)
    {
        inserer_abr(&(*a_p)->droit, n);
    }
}