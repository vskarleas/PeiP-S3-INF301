#include "file.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

cellule_f *nvelle_cellule()
{
    cellule_f *cell = malloc(sizeof(cellule_f));
    cell->valeur = malloc(sizeof(char *));
    cell->suivant = NULL;
    cell->precedent = NULL;
    return cell;
}

file *nvelle_file()
{
    file *fl = malloc(sizeof(file));
    fl->tete = NULL;
    fl->queue = NULL;
    return fl;
}

void ajouter_fin(file *fl, noeud *n)
{
    cellule_f *cell = nvelle_cellule();
    cell->valeur = n;
    if (est_vide_file(fl))
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

void supprimer_tete(file *fl)
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

noeud *tete_file(file *fl)
{
    return fl->tete->valeur;
}

bool est_vide_file(file *fl)
{
    if (fl->tete == NULL)
    {
        if (fl->queue == NULL)
        {
            return true;
        }
        fprintf(stderr, "\033[0;31mTete de la file vide mais queue non vide !\n\033[0m");

        exit(1);
    }
    if (fl->queue == NULL)
    {
        fprintf(stderr, "\033[0;31mTete de la file non vide mais queue vide !\n\033[0m");

        exit(1);
    }
    return false;
}
