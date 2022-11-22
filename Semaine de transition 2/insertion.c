#include "arbres.h"
#include <stdbool.h>
#include <stdio.h>

/* Somme des valeurs de l'arbre */
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