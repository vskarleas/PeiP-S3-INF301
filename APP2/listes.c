#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
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
    int lg_texte = strlen(texte);
    for (int i = lg_texte; i >= 0; i--)
    {
        ajout_debut(seq, texte[i]);
    }
}

void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *cell_actuelle = seq->tete;
    while (cell_actuelle != NULL)
    {
        printf("%c ", cell_actuelle->command);
        cell_actuelle = cell_actuelle->suivant;
    }
    printf("\n");
}

void ajout_debut(sequence_t * seq, char commande) // Ajoute une nouvelle cellule avec la commande passée en argument au debut de la sequence
{
    // Creation de la cellule a ajouter
    cellule_t *nouvelle_tete = malloc(sizeof(cellule_t));
    nouvelle_tete->command = commande;

    // Insertion en modifiant les references
    nouvelle_tete->suivant = seq->tete;
    seq->tete = nouvelle_tete;
}
