#ifndef _LISTES_H
#define _LISTES_H

#include <stdbool.h>

typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

typedef char* string;

struct cellule {
	string val;
	struct cellule* suivant;
};

typedef struct cellule cellule_t;

struct liste {
	cellule_t *tete;
};

typedef struct liste liste_t;

/* cree une nouvelle liste, initialement vide */
void init_liste_vide(liste_t* L);

/* libère toutes les cellules de la liste */
void liberer_liste(liste_t *L);

/* Ajouter une nouvelle cellule contenant c
 * en tête de la liste L.
 * Si l'ajout est réussi, le résultat est 0,
 * et 1 sinon (échec de l'ajout)
 */
int ajouter_tete(liste_t *L, string c);

void afficher_liste_t(liste_t *L);

void afficher_aaaa(cellule_t *cell);

bool est_vide(liste_t *L);

string depiler(liste_t *L);

cellule_t *tete(liste_t *L);

char *valeur(cellule_t *cell);

#endif /* _LISTES_H */


