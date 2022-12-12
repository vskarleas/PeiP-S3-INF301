#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include <stdbool.h>

#include "listes.h"


/* Analyse un arbre: doit mettre à jour le nombre d'espèces et de 
 * caractéristiques.
 */
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac);

void compte_esp_carac(arbre racine, int *nb_esp, int *nb_carac);

void creer_graph(arbre a, char *nom_fichier);

void ecrire_arbre(arbre a, FILE *f);

/* Recherche une espèce dans l'arbre et remplit seq avec la séquence de ses
 * caractéristiques.
 *
 * Doit retourner 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre racine, char *espece, liste_t *seq);

bool carac_espece(arbre a, liste_t *seq, char *espece);

int ajouter_espece(arbre *racine, char *espece, cellule_t *seq);

void afficher_par_niveau(arbre racine, FILE* fout);

// on considère qu'il n'est pas possible
// d'insérer une caractéristique à un arbre vide, ni d'insérer une caractéristique
// qui n'est possédée par aucune espèce déjà présente dans l'arbre (pour ce
// cas-là, ajout_espece fait l'affaire). Ceci permet d'éviter d'avoir à ajouter
// des noeuds caractéristique sans enfant qui seraient confondues avec des
// espèces/feuilles.
int ajouter_carac(arbre* a, char* carac, cellule_t* seq);

void liste_animaux(arbre *a, liste_t *liste);

bool est_tout_dedans(liste_t *liste, cellule_t *seq);

bool est_dedans(cellule_t *liste, char *espece);

bool est_que_ca(liste_t *liste, cellule_t *seq);

void inserer_cara(arbre *a, char *carac);

#endif
