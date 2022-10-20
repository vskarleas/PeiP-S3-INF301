#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#ifdef AAAAAAh
#include <stdébile.h>
#endif

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;

cellule_t *nouvelleCellule(void) // Créé une nouvelle cellule
{
    cellule_t *cell = malloc(sizeof(cellule_t));
    return cell;
}

void detruireCellule(cellule_t *cel)
{
    free(cel);
}

/* Acte I.1 */
void conversion(char *texte, sequence_t *seq) // Converti une chaine de caractere en sequence (liste chainee) de caracteres
{
    cellule_t *cell;
    char c;
    bool est_dans_accolade = false;
    char *contenu_accolade;
    int compteur_accolades = 0;
    sequence_t *accolade = NULL;
    int lg_texte = strlen(texte);
    for (int i = lg_texte; i >= 0; i--)
    {
        c = texte[i];
        if (isspace(c))
        {
            // RIEN
        }
        else if (c == '}')
        {
            if (est_dans_accolade)
            {
                compteur_accolades++;
            }
            else
            {
                est_dans_accolade = true;
                texte[i] = '\0';
                // nouvelle_seq(accolade);
                accolade = nouvelle_seq();
            }
        }
        else if (c == '{')
        {
            if (compteur_accolades == 0)
            {
                est_dans_accolade = false;
                contenu_accolade = &texte[i + 1];
                conversion(contenu_accolade, accolade);
                cell = nouvelleCellule();
                cell->valeur.s = accolade;
                cell->type_valeur = CHAR_LISTE;
                ajout_debut(seq, cell);
            }
            else
            {
                compteur_accolades--;
            }
        }
        else if (est_dans_accolade)
        {
            // RIEN!
        }
        else
        {
            cell = nouvelleCellule();
            if (c >= '0' && c <= '9')
            {
                cell->valeur.n = texte[i] - '0';
                cell->type_valeur = INT;
            }
            else
            {
                cell->valeur.l = texte[i];
                cell->type_valeur = CHAR;
            }
            ajout_debut(seq, cell);
        }
    }
}
/* ----------- */

void afficher(sequence_t *seq)
{
    assert(seq); /* Le pointeur doit être valide */
    cellule_t *cell_actuelle = seq->tete;
    printf("[ ");
    while (cell_actuelle != NULL)
    {
        if (cell_actuelle->type_valeur == INT)
        {
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
    printf("]");
}

void ajout_debut(sequence_t *seq, cellule_t *nouvelle_tete) // Ajoute une nouvelle cellule avec la commande passée en argument au debut de la sequence
{
    // Insertion en modifiant les references
    nouvelle_tete->suivant = seq->tete;
    seq->tete = nouvelle_tete;
}

/* Acte II */
void empiler_int(sequence_t *pile, int n) // Ajout au debut de notre pile un entier
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.n = n;
    cell->type_valeur = INT; // definit que le typage de notre action d'empilage est un entier
    empiler(pile, cell);
}

void empiler_char(sequence_t *pile, char n) // Ajout au debut de notre pile un caracter
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.l = n;
    cell->type_valeur = CHAR; // definit que le typage de notre action d'empilage est un caracter
    empiler(pile, cell);
}

void empiler_seq(sequence_t *pile, sequence_t *n) // Ajout au debut de notre pile une sequence
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.s = n;
    cell->type_valeur = CHAR_LISTE; // definit que le typage de notre action d'empilage est une sequence
    empiler(pile, cell);
}

void retirer_tete(sequence_t *seq) // Supprime le tete de la sequence en definisant comme tete l'ement suivant de la sequence
{
    cellule_t *suivant = seq->tete->suivant;
    seq->tete = suivant;
}

cellule_t *tete(sequence_t *seq) // Retourne le tete de notre sequence comme une cellule
{
    return seq->tete;
}

cellule_t *depiler(sequence_t *seq) //
{
    cellule_t *cell = tete(seq);
    retirer_tete(seq);
    return cell;
}

int depiler_int(sequence_t *pile) // Suprime le premier element (entier) par le pile tout en retournant sa valeur
{
    return depiler(pile)->valeur.n;
}

char depiler_char(sequence_t *pile) // Suprime le premier element (character) par le pile tout en retournant sa valeur
{
    return depiler(pile)->valeur.l;
}

sequence_t *depiler_seq(sequence_t *pile) // Suprime le premier element (character) par le pile tout en retournant sa valeur
{
    return depiler(pile)->valeur.s;
}

void vider(sequence_t *seq)
{
    seq->tete = NULL;
}

sequence_t *nouvelle_seq()
{
    return malloc(sizeof(sequence_t));
}

void inserer_liste_debut(sequence_t *seq, sequence_t *seq_a_inserer)
{
    cellule_t *dernier_elem = queue(seq_a_inserer);
    if (dernier_elem != NULL)
    {
        dernier_elem->suivant = seq->tete;
        seq->tete = seq_a_inserer->tete;
    }
}

cellule_t *queue(sequence_t *seq)
{
    cellule_t *cell = seq->tete;
    if (cell == NULL)
    {
        return NULL;
    }
    else
    {
        while (cell->suivant != NULL)
        {
            cell = cell->suivant;
        }
        return cell;
    }
}