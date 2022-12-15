#ifndef _TABLE_PHYLO_H
#define _TABLE_PHYLO_H

#include <stdbool.h>
#include "arbres.h"

typedef struct liste_p liste_p_t;
/* Type de liste à compléter selon votre besoin. */

typedef char *string;

typedef struct tableau_p tableau_p_t;

struct cellule_p
{
    string carac;
    int nb_especes;
    liste_t *especes;
    struct cellule_p *suivant;
};

typedef struct cellule_p cellule_p_t;

struct liste_p
{
    cellule_p_t *tete;
};

liste_p_t *init_liste_p_t();

void lire_table(char *nom_fichier, int nb_carac, liste_p_t *caracs, liste_p_t *table);

void ajouter_carac_a_espece(liste_p_t *table, char *espece, char *carac);

void tri_liste_p(liste_p_t *l);

/*Ajoute un string à la liste*/
int ajouter_tete_p(liste_p_t *L, string carac, int n);

void insertion_trie_croissant(liste_p_t *l, cellule_p_t *cell);

void creer_arbre_table(arbre *a, char *nom_fichier, int nb_carac);

#endif