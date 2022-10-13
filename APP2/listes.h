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
        struct sequence * s;
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

cellule_t *nouvelleCellule(void);

void detruireCellule(cellule_t *);

void conversion(char *texte, sequence_t *seq);

void afficher(sequence_t *seq);

void ajout_debut(sequence_t *seq, cellule_t *nouvelle_tete);
#define empiler ajout_debut

void empiler_int(sequence_t *pile, int n);

void retirer_tete(sequence_t *seq);

cellule_t* tete(sequence_t *seq);

cellule_t *depiler(sequence_t *seq);

int depiler_int(sequence_t *seq);

void addition(sequence_t *pile);

void soustraction(sequence_t *pile);

void multiplication(sequence_t *pile);

#endif
