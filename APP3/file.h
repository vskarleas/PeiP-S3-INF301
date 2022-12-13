#ifndef _FILE_H
#define _FILE_H

#include <stdbool.h>
#include "arbres.h"

typedef struct cellule_f_f cellule_f;

/*La structure de la file est utilise dans le parcours en largeur
qu'on utilise sur l'Acte 3B*/

struct cellule_f_f
{
    noeud *valeur;
    cellule_f *suivant;
    cellule_f *precedent;
};


//File composé par la tete et le queue. Est de la forme First In, First Out
typedef struct
{
    cellule_f *tete;
    cellule_f *queue;
} file;

/*Cree une nouvelle cellule*/
cellule_f *nvelle_cellule();

/*Cree une nouvelle file*/
file *nvelle_file();

/*Ajoute une valeur à la fin de la file */
void ajouter_fin(file *fl, noeud *n);

/*Supprime la tete de la file quand on l'enleve de la file*/
void supprimer_tete(file *fl);

/*Renvoi la tete de la file (du type noeud)*/
noeud *tete_file(file *fl);

/*Renvoi true si la file est vide, false sinon*/
bool est_vide_file(file *fl);

#endif