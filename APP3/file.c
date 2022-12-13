#include "file.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*Cree une nouvelle cellule*/
cellule_f *nvelle_cellule()
{
    cellule_f *cell = malloc(sizeof(cellule_f));
    cell->valeur = malloc(sizeof(char *));
    cell->suivant = NULL;
    cell->precedent = NULL;
    return cell;
}

/*Cree une nouvelle file*/
file *nvelle_file()
{
    file *fl = malloc(sizeof(file));
    fl->tete = NULL;
    fl->queue = NULL;
    return fl;
}

/*Ajoute une valeur à la fin de la file */
void ajouter_fin(file *fl, noeud *n)
{
    cellule_f *cell = nvelle_cellule();
    cell->valeur = n;
    if (est_vide_file(fl)) //Verification si la file est vide
    {
        fl->queue = cell;
        fl->tete = cell;
    }
    else
    {//Si file pas vide, alors tete est change et nouvelle cellule est ajouté dans le queue
        fl->queue->suivant = cell;
        cell->precedent = fl->queue;
        fl->queue = cell;
    }
}

/*Supprime la tete de la file quand on l'enleve de la file*/
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

/*Renvoi la tete de la file (du type noeud)*/
noeud *tete_file(file *fl)
{
    return fl->tete->valeur;
}

/*Renvoi true si la file est vide, false sinon*/
bool est_vide_file(file *fl)
{
    if (fl->tete == NULL) //Verification que la tete est video
    {
        if (fl->queue == NULL)//Verification que la queue de la file vide aussi
        {
            return true; //Allor retourne true
        } //sinon par definition, si queue de la file n'est pas NULL, il y auccun moyenne que la tete est vide aussi
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
