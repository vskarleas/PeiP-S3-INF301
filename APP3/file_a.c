#include "file_a.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

cellule_f_a *nvelle_cellule_a()
{
    cellule_f_a *cell = malloc(sizeof(cellule_f_a));
    cell->valeur = malloc(sizeof(arbre));
    cell->suivant = NULL;
    cell->precedent = NULL;
    return cell;
}

file_a *nvelle_file_a()
{
    file_a *fl = malloc(sizeof(file_a));
    fl->tete = NULL;
    fl->queue = NULL;
    return fl;
}

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

arbre *tete_file_a(file_a *fl)
{
    return fl->tete->valeur;
}

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
