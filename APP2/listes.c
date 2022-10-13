#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"

/*
 *  Auteur(s) : 
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void) // Créé une nouvelle cellule
{
    cellule_t *cell = malloc (sizeof (cellule_t));
    return cell;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}

void conversion (char *texte, sequence_t *seq) // Converti une chaine de caractere en sequence (liste chainee) de caracteres
{
    cellule_t *cell;
    int lg_texte = strlen(texte);
    for (int i = lg_texte; i >= 0; i--)
    {
        cell = nouvelleCellule();
        cell->valeur.l = texte[i];
        cell->type_valeur = CHAR;
        ajout_debut(seq, cell);
    }
}

void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *cell_actuelle = seq->tete;
    while (cell_actuelle != NULL)
    {
        if (cell_actuelle->type_valeur == INT){
            printf("%d ", cell_actuelle->valeur.n);
        }
        if (cell_actuelle->type_valeur == CHAR)
        {
            printf("%c ", cell_actuelle->valeur.l);
        }
        if (cell_actuelle->type_valeur == CHAR_LISTE)
        {
            afficher(cell_actuelle->valeur.s);
        }
        cell_actuelle = cell_actuelle->suivant;
    }
    printf("\n");
}

void ajout_debut(sequence_t * seq, cellule_t *nouvelle_tete) // Ajoute une nouvelle cellule avec la commande passée en argument au debut de la sequence
{
    // Insertion en modifiant les references
    nouvelle_tete->suivant = seq->tete;
    seq->tete = nouvelle_tete;
}

void empiler_int(sequence_t *pile, int n)
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.n = n;
    cell->type_valeur = INT;
    empiler(pile, cell);
}

void retirer_tete(sequence_t *seq)
{
    seq->tete = seq->tete->suivant;
}

cellule_t *tete(sequence_t *seq)
{
    return seq->tete;
}

cellule_t *depiler(sequence_t *seq)
{
    cellule_t *cell = tete(seq);
    retirer_tete(seq);
    return cell;
}

int depiler_int(sequence_t *pile)
{
    return depiler(pile)->valeur.n;
}

void addition(sequence_t *pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x + y);
}

void soustraction(sequence_t *pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x - y);
}

void multiplication(sequence_t *pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x * y);
}