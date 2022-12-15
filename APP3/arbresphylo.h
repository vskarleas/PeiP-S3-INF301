#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include <stdbool.h>

#include "listes.h"


/* Analyse un arbre: doit mettre à jour le nombre d'espèces et de 
 * caractéristiques.
 */
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac);

/*Trouve le nombre des especes et des caracteristiques sur un arbre donné*/
void compte_esp_carac(arbre racine, int *nb_esp, int *nb_carac);

/*Fonction principale qui ouvre le fichier ou 
l'arbre en format dot va être sauvegradé*/
void creer_graph(arbre a, char *nom_fichier);

/*Ecris l'arbre en format dot*/
void ecrire_arbre(arbre a, FILE *f);

/* Recherche une espèce dans l'arbre et remplit seq avec la séquence de ses
 * caractéristiques.
 *
 * Doit retourner 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre racine, char *espece, liste_t *seq);

/*Retourne vrai si la valeur de l'arbre est l'espece passée en argument, faux sinon*/
bool carac_espece(arbre a, liste_t *seq, char *espece);

/* Doit renvoyer 0 si l’espèce a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur. Objectif: Ajouter un espece dans un arbre phylogenetique
 */
int ajouter_espece(arbre *racine, char *espece, cellule_t *seq);

/*Renvoi true si la aleur du noeud est un caractere, false sinon*/
bool est_carac(noeud *n);

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE* fout);

// on considère qu'il n'est pas possible
// d'insérer une caractéristique à un arbre vide, ni d'insérer une caractéristique
// qui n'est possédée par aucune espèce déjà présente dans l'arbre (pour ce
// cas-là, ajout_espece fait l'affaire). Ceci permet d'éviter d'avoir à ajouter
// des noeuds caractéristique sans enfant qui seraient confondues avec des
// espèces/feuilles.

/*Ajouter une caractéristique dans un arbre*/
int ajouter_carac(arbre* a, char* carac, cellule_t* seq);

//FIXME: je ne sais plus exactement
/*Creation d'une liste des especes par un arbre
passé en argument.*/
void liste_especes(arbre *a, liste_t *liste);

/*Revoi true si tous les elements de la sequence sont dans la liste, false sinon*/
bool est_tout_dedans(liste_t *liste, cellule_t *seq);

/*Renvoi true si l'espece est dans la 
liste passé en argument, false sinon*/
bool est_dedans(cellule_t *liste, char *espece);

/*Renvoi true si la longueur de la sequence et de la liste sont les memes, c'est-à-dire
si dans le liste et la séquence il n'y a pas plus d'elements, false sinon*/
bool est_que_ca(liste_t *liste, cellule_t *seq);

/*Insere une caractéristique et met le sous arbre à droite de cette caractéristique*/
void inserer_cara(arbre *a, char *carac);

#endif
