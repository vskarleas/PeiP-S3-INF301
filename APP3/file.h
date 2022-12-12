#ifndef _FILE_H
#define _FILE_H

#include <stdbool.h>
#include "arbres.h"

typedef struct cellule_f_f cellule_f;

struct cellule_f_f
{
    noeud *valeur;
    cellule_f *suivant;
    cellule_f *precedent;
};

typedef struct
{
    cellule_f *tete;
    cellule_f *queue;
} file;

cellule_f *nvelle_cellule();

file *nvelle_file();

void ajouter_fin(file *fl, noeud *n);

void supprimer_tete(file *fl);

noeud *tete_file(file *fl);

bool est_vide_file(file *fl);

#endif