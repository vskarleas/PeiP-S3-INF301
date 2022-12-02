#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "listes.h"

/* fichier à complvaléter au besoin */

void init_liste_vide(liste_t *L)
{
    L->tete = NULL;
}

void liberer_liste(liste_t *L)
{
    if (L != NULL)
    {
        if (L->tete != NULL)
        {
            liste_t L2;
            L2.tete = L->tete->suivant;
            liberer_liste(&L2);
            free(L->tete);
        }
    }
}

int ajouter_tete(liste_t *L, string c)
{ /* retourne 0 si OK, 1 sinon  */
    // renvoyer 1 si les mallocs renvoient null (plus assez de memoire)
    cellule_t *nv_tete = malloc(sizeof(cellule_t));
    nv_tete->val = malloc(sizeof(char) * strlen(c));
    nv_tete->suivant = L->tete;
    strcpy(nv_tete->val, c);
    L->tete = nv_tete;
    return 0;
}

void afficher_liste_t(liste_t *L)
{
    printf("[ ");
    afficher_aaaa(L->tete);

    printf("]\n");
}

void afficher_aaaa(cellule_t *cell)
{
    if (cell != NULL)
    {
        printf("%s, ", cell->val);
        afficher_aaaa(cell->suivant);
    }
}

bool est_vide(liste_t *L)
{
    return (L->tete == NULL);
}

string depiler(liste_t *L)
{
    string ret = malloc(sizeof(strlen(L->tete->val)));
    strcpy(ret, L->tete->val);
    cellule_t *tete = L->tete;
    L->tete = L->tete->suivant;
    //free(tete);
    return ret;
}

cellule_t *tete(liste_t *L)
{
    return L->tete;
}

char *valeur(cellule_t *cell)
{
    return cell->val;
}