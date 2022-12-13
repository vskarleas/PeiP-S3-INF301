#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "listes.h"

/* fichier à complvaléter au besoin */

/*Initialisation de la liste*/
void init_liste_vide(liste_t *L)
{
    L->tete = NULL;
}

/*Libere la liste*/
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

/*Ajoute un string à la liste*/
int ajouter_tete(liste_t *L, string c)
{ /* retourne 0 si OK, 1 sinon  */
    // renvoyer 1 si les mallocs renvoient null (plus assez de memoire)c 
    cellule_t *nv_tete = calloc(1,sizeof(cellule_t));
    if (nv_tete == NULL)
    {
        return 1;
    }
    if (strlen(c) != 0)
    {

        nv_tete->val = malloc(sizeof(char) * (strlen(c)+1));
        strcpy(nv_tete->val, c);
    }
    else
    {
    nv_tete->val = malloc(1);
    nv_tete->val[0] = '\0';
    }
    nv_tete->suivant = L->tete;
    L->tete = nv_tete;

    return 0;
}

/*Affiche la liste*/
void afficher_liste_t(liste_t *L)
{
    printf("[ ");
    afficher_aaaa(L->tete);

    printf("]\n");
}

/*Affiche la valeur de la cellule*/
void afficher_aaaa(cellule_t *cell)
{
    if (cell != NULL)
    {
        printf("%s, ", cell->val);
        afficher_aaaa(cell->suivant);
    }
}

/*Revoi true si la liste est vide, false sinon*/
bool est_vide(liste_t *L)
{
    return (L->tete == NULL);
}

/*Depile la premiere valeur de la liste*/
string depiler(liste_t *L)
{
    string ret = malloc(sizeof(strlen(L->tete->val)));
    strcpy(ret, L->tete->val);
    L->tete = L->tete->suivant;
    return ret;
}

/*Renvoi la tete de la liste*/
cellule_t *tete(liste_t *L)
{
    return L->tete;
}

/*Renvoi la valeur de la cellule*/
char *valeur(cellule_t *cell)
{
    return cell->val;
}