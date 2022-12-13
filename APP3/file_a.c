#include "file_a.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*Meme explications suplementaires qu'on
trouve sue file.c */

/*Cree une nouvelle cellule*/
cellule_f_a *nvelle_cellule_a()
{
    cellule_f_a *cell = malloc(sizeof(cellule_f_a));
    cell->valeur = malloc(sizeof(arbre));
    cell->suivant = NULL;
    cell->precedent = NULL;
    return cell;
}

/*Cree une nouvelle file*/
file_a *nvelle_file_a()
{
    file_a *fl = malloc(sizeof(file_a));
    fl->tete = NULL;
    fl->queue = NULL;
    return fl;
}

/*Ajoute une valeur à la fin de la file */
void ajouter_fin_a(file_a *fl, arbre *a)
{
    cellule_f_a *cell = nvelle_cellule_a();
    cell->valeur = a;
    if (est_vide_file_a(fl))
    {
        fl->queue = cell;
        fl->tete = cell;
    }
    else
    {
        fl->queue->suivant = cell;
        cell->precedent = fl->queue;
        fl->queue = cell;
    }
}

/*Supprime la tete de la file quand on l'enleve de la file*/
void supprimer_tete_a(file_a *fl)
{
    if (fl->tete == fl->queue)
    {
        fl->queue = NULL;
    }
    fl->tete = fl->tete->suivant;
    if (fl->tete != NULL)
    {
        fl->tete->precedent = NULL;
    }
}

/*Renvoi la tete de la file (du type arbre)*/
arbre *tete_file_a(file_a *fl) //<- Ici on renvoi un arbre au lieu d'un noeud comme on faisait sue file.c
{
    return fl->tete->valeur;
}

/*Renvoi true si la file est vide, false sinon*/
bool est_vide_file_a(file_a *fl)
{
    if (fl->tete == NULL)
    {
        if (fl->queue == NULL)
        {
            return true;
        }
        fprintf(stderr, "\033[0;31mTete de la file_a vide mais queue non vide !\n\033[0m");

        exit(1);
    }
    if (fl->queue == NULL)
    {
        fprintf(stderr, "\033[0;31mTete de la file_a non vide mais queue vide !\n\033[0m");

        exit(1);
    }
    return false;
}
