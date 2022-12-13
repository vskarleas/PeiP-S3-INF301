#ifndef _FILE_A_H
#define _FILE_A_H

#include <stdbool.h>
#include "arbres.h"

typedef struct cellule_f_f_a cellule_f_a;

/*On a modifié notre structure originalle de la cellule 
utilisé par une fille pour l'acte 4*/

struct cellule_f_f_a
{
    arbre *valeur; //<- on utilise un pointeur vers un noeud (un arbre) au lieu d'un noeud.
    cellule_f_a *suivant;
    cellule_f_a *precedent;
};

typedef struct
{
    cellule_f_a *tete;
    cellule_f_a *queue;
} file_a;

/*Cree une nouvelle cellule*/
cellule_f_a *nvelle_cellule_a();

/*Cree une nouvelle file*/
file_a *nvelle_file_a();

/*Ajoute une valeur à la fin de la file */
void ajouter_fin_a(file_a *fl, arbre *n);

/*Supprime la tete de la file quand on l'enleve de la file*/
void supprimer_tete_a(file_a *fl);

/*Renvoi la tete de la file (du type arbre)*/
arbre *tete_file_a(file_a *fl);

/*Renvoi true si la file est vide, false sinon*/
bool est_vide_file_a(file_a *fl);

#endif