#include "file.h"
#include <stdlib.h>

cellule *nvelle_cellule()
{
    cellule *cell = malloc(sizeof(cellule));
    cell->val=NULL;
    cell->suivant = NULL;
    return cell;
}

void ajouter_fin(file *f, char *s)
{
    cellule *cell = nvelle_cellule();
    strcpy(cell->val, s);
    f->queue = cell;
}

void supprimer_tete(file *f)
{
    f->tete = f->tete->suivant;
}

char *valeur_tete(file *f)
{
    char s[512];
    strcpy(s, f->tete->valeur);
    return s;
}
