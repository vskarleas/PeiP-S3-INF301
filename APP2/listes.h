#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

#endif

extern bool silent_mode;

typedef enum
{
    INT,
    CHAR,
    CHAR_LISTE,
} type_valeur_cellule;

struct cellule
{
    /* vous pouvez rajouter d'autres champs ici */
    union
    {
        int n;
        char l;
        struct sequence *s;
    } valeur;

    type_valeur_cellule type_valeur;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence
{
    cellule_t *tete;
};
typedef struct sequence sequence_t;

/*Créé une nouvelle cellule*/
cellule_t *nouvelleCellule(void);

/*Detruit une cellule*/
void detruireCellule(cellule_t *);

/*Detruit une sequence*/
void detruire_seq(sequence_t *seq);

/*Converti une chaine de caractere en sequence
(liste chainee) de caracteres*/
void conversion(char *texte, sequence_t *seq);

/*Affiche la séquence*/
void afficher(sequence_t *seq);

/*Ajoute une nouvelle cellule avec la commande
passée en argument au debut de la sequence*/
void ajout_debut(sequence_t *seq, cellule_t *nouvelle_tete);
#define empiler ajout_debut

/*Ajoute au sommet de la pile un entier*/
void empiler_int(sequence_t *pile, int n);

/*Ajoute au sommet de la pile un charactere*/
void empiler_char(sequence_t *pile, char n);

/*Ajoute au sommet de la pile une sequence*/
void empiler_seq(sequence_t *pile, sequence_t *n);

/*Supprime la tete de la sequence en definissant comme
tete l'element suivant de la sequence*/
void retirer_tete(sequence_t *seq);

/*Retourne la tete de notre sequence comme une cellule*/
cellule_t *tete(sequence_t *seq);

/*Dépile le sommet*/
cellule_t *depiler(sequence_t *seq);

/*Supprime le premier element (entier)
de la pile tout en retournant sa valeur*/
int depiler_int(sequence_t *seq);

/*Supprime le premier element (charactere)
de la pile tout en retournant sa valeur*/
char depiler_char(sequence_t *pile);

/*Supprime le premier element (sequence)
de la pile tout en retournant sa valeur*/
sequence_t *depiler_seq(sequence_t *pile);

/*Vide la séquence*/
void vider(sequence_t *seq);

/*Créé une nouvelle séquence*/
sequence_t *nouvelle_seq();

/*Insere une sequence au debut d'une autre sequence*/
void inserer_liste_debut(sequence_t *seq, sequence_t *seq_a_inserer);

/*Retourne la queue de la séquence*/
cellule_t *queue(sequence_t *seq);

/*Fais une copie de la séquence donnée en argument*/
sequence_t *copie_sequence(sequence_t *seq);

/*Retourne une copie d'une cellule passé en argument*/
cellule_t *copie_cellule(cellule_t *cell);
/*

*/
void retourner_sequence(sequence_t *seq);

#endif
