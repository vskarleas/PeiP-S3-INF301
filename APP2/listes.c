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
#define PROGSIZE 400000096
#include <time.h>

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;

/*Créé une nouvelle cellule*/
cellule_t *nouvelleCellule(void)
{
    cellule_t *cell = malloc(sizeof(cellule_t));
    return cell;
}

/*Detruit une cellule*/
void detruireCellule(cellule_t *cel)
{
    free(cel);
}

/*Detruit une sequence*/
void detruire_seq(sequence_t *seq)
{
    free(seq);
}

/* Acte I.1 */

/*Converti une chaine de caractere en sequence
(liste chainee) de caracteres*/
void conversion(char *texte, sequence_t *seq)
{
    unsigned long compteur_passages = 0;

    cellule_t *cell;
    char c;
    bool est_dans_accolade = false;
    char *contenu_accolade;
    int compteur_accolades = 0;
    int indice_accolade_fermante;
    sequence_t *accolade = NULL;
    int lg_texte = strlen(texte);
    for (int i = lg_texte; i >= 0; i--)
    {
        compteur_passages++;

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
                indice_accolade_fermante = i;
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
                texte[indice_accolade_fermante] = '}';
                cell = nouvelleCellule();
                cell->valeur.s = accolade;
                cell->type_valeur = CHAR_LISTE;
                cell->suivant = NULL;
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
                cell->suivant = NULL;
            }
            else
            {
                cell->valeur.l = texte[i];
                cell->type_valeur = CHAR;
                cell->suivant = NULL;
            }
            ajout_debut(seq, cell);
        }
    }
    // printf("\n%lu\n\n", compteur_passages);
}
/* ----------- */

/*Affiche la séquence*/
void afficher(sequence_t *seq)
{
    assert(seq); /* Le pointeur doit être valide */
    cellule_t *cell_actuelle = seq->tete;
    printf("[");
    while (cell_actuelle != NULL)
    {
        if (cell_actuelle->type_valeur == INT)
        {
            printf("%d", cell_actuelle->valeur.n); // Affichage du typage INT
        }
        if (cell_actuelle->type_valeur == CHAR)
        {
            printf("%c", cell_actuelle->valeur.l); // Affichage du typage CHAR
        }
        if (cell_actuelle->type_valeur == CHAR_LISTE)
        {
            afficher(cell_actuelle->valeur.s); // Affichage du typage CHAR_LISTE / Liste chainee
        }
        cell_actuelle = cell_actuelle->suivant;
    }
    printf("]");
}

/*Ajoute une nouvelle cellule avec la commande
passée en argument au debut de la sequence*/
void ajout_debut(sequence_t *seq, cellule_t *nouvelle_tete)
{
    // Insertion en modifiant les references
    nouvelle_tete->suivant = seq->tete;
    seq->tete = nouvelle_tete;
}

/*----------*/
/* Acte II */

/*Ajoute au sommet de la pile un entier*/
void empiler_int(sequence_t *pile, int n)
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.n = n;
    cell->type_valeur = INT; // definit l'élément à insérer comme un entier
    empiler(pile, cell);
}

/*Ajoute au sommet de la pile un charactere*/
void empiler_char(sequence_t *pile, char n)
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.l = n;
    cell->type_valeur = CHAR; //  definit l'élément à insérer comme un entier charactere
    empiler(pile, cell);
}

/*Ajoute au sommet de la pile une sequence*/
void empiler_seq(sequence_t *pile, sequence_t *n)
{
    cellule_t *cell = nouvelleCellule();
    cell->valeur.s = n;
    cell->type_valeur = CHAR_LISTE; //  definit l'élément à insérer comme une sequence
    empiler(pile, cell);
}

/*Supprime la tete de la sequence en definissant comme
tete l'element suivant de la sequence*/
void retirer_tete(sequence_t *seq) // FIXME: potentielle fuite de mémoire
{
    cellule_t *suivant = seq->tete->suivant;
    seq->tete = suivant; // initialisation de la nouvelle tete
}

/*Retourne la tete de notre sequence comme une cellule*/
cellule_t *tete(sequence_t *seq)
{
    return seq->tete;
}

/*Dépile le sommet*/
cellule_t *depiler(sequence_t *seq)
{
    cellule_t *cell = tete(seq);
    retirer_tete(seq);
    return cell;
}

/*Supprime le premier element (entier)
de la pile tout en retournant sa valeur*/
int depiler_int(sequence_t *pile)
{
    cellule_t *cell = depiler(pile);
    int retour = cell->valeur.n;
    // detruireCellule(cell); //FIXME: fuite de memoire, on devrait pouvoir detruire la cellule ici mais ca casse tout...
    return retour;
}

/*Supprime le premier element (charactere)
de la pile tout en retournant sa valeur*/
char depiler_char(sequence_t *pile)
{
    cellule_t *cell = depiler(pile);
    char retour = cell->valeur.l;
    // detruireCellule(cell); //FIXME: fuite de memoire, on devrait pouvoir detruire la cellule ici mais ca casse tout...
    return retour;
}

/*Supprime le premier element (sequence)
de la pile tout en retournant sa valeur*/
sequence_t *depiler_seq(sequence_t *pile)
{
    cellule_t *cell = depiler(pile);
    sequence_t *retour = cell->valeur.s;
    // detruireCellule(cell); //FIXME: fuite de memoire, on devrait pouvoir detruire la cellule ici mais ca casse tout...
    return retour;
}

/*Vide la séquence*/
void vider(sequence_t *seq) // FIXME: ne libere pas la memoire!
{
    seq->tete = NULL;
}

/*Créé une nouvelle séquence*/
sequence_t *nouvelle_seq()
{
    return malloc(sizeof(sequence_t));
}

/*Insere une sequence au debut d'une autre sequence*/
void inserer_liste_debut(sequence_t *seq, sequence_t *seq_a_inserer)
{
    cellule_t *dernier_elem = queue(seq_a_inserer);
    if (dernier_elem != NULL)
    {
        dernier_elem->suivant = seq->tete; // le suivant de la queue de la sequence à inserer est la tete de la sequence initiale
        seq->tete = seq_a_inserer->tete;   // initialisation de la nouvelle tete
    }
    detruire_seq(seq_a_inserer);
}

/*Retourne la queue de la séquence*/
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

/*Fais une copie de la séquence donnée en argument*/
sequence_t *copie_sequence(sequence_t *seq)
{
    cellule_t *cell = seq->tete;
    cellule_t *nvelle_cell;
    sequence_t *nvelle_seq = nouvelle_seq();
    if (cell == NULL) // Traitment de cas ou la sequence est vide -> nouvelle_sequence vide aussi
    {
        nvelle_seq->tete = NULL;
        return nvelle_seq;
    }
    nvelle_cell = nouvelleCellule();              // Initialisation du cellule vide / Il va lire les elements de la sequence pour le mettre dans la nouvelle sequence (une copie)
    nvelle_cell->valeur = cell->valeur;           // Premier element de la sequence passé dans la cellue
    nvelle_cell->type_valeur = cell->type_valeur; // Le typage du premier element de la sequence passé dans le typage du cellule
    nvelle_seq->tete = nvelle_cell;               // Initialisation de la tete de la nouvelle sequence

    while (cell->suivant != NULL) // Parcourir le reste de las sequence pour l'ajouter a la nouvelle sequence (copie)
    {
        nvelle_cell->suivant = nouvelleCellule();
        nvelle_cell->suivant->valeur = cell->suivant->valeur;
        nvelle_cell->suivant->type_valeur = cell->suivant->type_valeur;
        nvelle_cell = nvelle_cell->suivant;
        cell = cell->suivant;
    }
    nvelle_cell->suivant = NULL; // Indication du fin de la sequence
    return nvelle_seq;           // Envoie la nouvelle sequence (copie)
}

// Retourne une copie d'une cellule passé en argument
cellule_t *copie_cellule(cellule_t *cell)
{
    cellule_t *nvelle_cell = malloc(sizeof(cellule_t)); // Position en endroit de la memoire pour la nouvelle cellule
    nvelle_cell->valeur = cell->valeur;
    nvelle_cell->suivant = cell->suivant;
    nvelle_cell->type_valeur = cell->type_valeur;
    return nvelle_cell;
}

/*

*/
void retourner_sequence(sequence_t *seq)
{
    sequence_t *seq_retournee = nouvelle_seq(); // Initiliasation d'une sequence (liste chainee)
    cellule_t *cell = seq->tete;                // Tete de la sequence passé à la cellule pour effectuer le parcours
    while (cell != NULL)                        // Parcourir tout la sequence jusque la fin
    {
        ajout_debut(seq_retournee, copie_cellule(cell));
        cell = cell->suivant;
    }
    seq->tete = seq_retournee->tete;
}