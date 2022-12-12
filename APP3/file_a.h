#ifndef _FILE_A_H
#define _FILE_A_H

#include <stdbool.h>
#include "arbres.h"

typedef struct cellule_f_f_a cellule_f_a;

struct cellule_f_f_a
{
    arbre *valeur;
    cellule_f_a *suivant;
    cellule_f_a *precedent;
};

typedef struct
{
    cellule_f_a *tete;
    cellule_f_a *queue;
} file_a;

cellule_f_a *nvelle_cellule_a();

file_a *nvelle_file_a();

void ajouter_fin_a(file_a *fl, arbre *n);

void supprimer_tete_a(file_a *fl);

arbre *tete_file_a(file_a *fl);

bool est_vide_file_a(file_a *fl);

#endif