#include "arbres.h"
#include <stdbool.h>
#include <stdio.h>

bool present(arbre a, int n) {
    if (a != NULL)
    {
        if (n == a->valeur)
        {
            return true;
        }
        else 
        {
            if (present(a->gauche, n))
            {
                return true;
            }
            else if (present(a->droit, n))
            {
                return true;
            }
            
        }
    }
    return false;
}

bool inserer_abr(arbre *a_p, int n) {
    if (present((*a_p), n)){
        return false;
    }
    else
    {
    noeud *tmp = NULL;
    if (!(*a_p))
    {
        tmp = (noeud *)malloc(sizeof(noeud));
        tmp->gauche = NULL;
        tmp->droit = NULL;
        tmp->valeur = n;
        *a_p = tmp;
    }
    if (n < (*a_p)->valeur)
    {
        inserer_abr(&(*a_p)->gauche, n);
    }
    else if (n > (*a_p)->valeur)
    {
        inserer_abr(&(*a_p)->droit, n);
    }
    return true;
    }
}