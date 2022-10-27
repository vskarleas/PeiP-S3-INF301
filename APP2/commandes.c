#include <stdlib.h>
#include <stdio.h>
#include "listes.h"

/*Addition entre deux elements de
la pile (le resulat est empile sur
la pile)*/
void addition(sequence_t *pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x + y);
}

void soustraction(sequence_t *pile) // Soustraction entre deux elements de la pile (le resulat est empile sur le pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, y - x);
}

void multiplication(sequence_t *pile) // Multiplication entre deux elements de la pile (le resulat est empile sur le pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x * y);
}

void   execution_coditionnelle(sequence_t *routine, sequence_t *pile)
{
    sequence_t *commande_1 = depiler_seq(pile);
    sequence_t *commande_2 = depiler_seq(pile);
    int x = depiler_int(pile);
    if (x == 0)
    {
        inserer_liste_debut(routine, commande_1);
    }
    else
    {
        inserer_liste_debut(routine, commande_2);
    }
}

//#define ACTE_V
#ifdef ACTE_V
/* Acte V */



//Il me semble beaucoup à la fonctionalité retirer_tete

#endif
void echange(sequence_t *pile)
{
    cellule_t *cell1 = depiler(pile);
    cellule_t *cell2 = depiler(pile);
    empiler(pile, cell1);
    empiler(pile, cell2);
}

void exec(sequence_t *routine, sequence_t *pile)
{
    sequence_t *seq = depiler_seq(pile);
    inserer_liste_debut(routine, seq);
}

void clone(sequence_t *pile)
{
    cellule_t *cell = tete(pile);
    cellule_t *cell2 = nouvelleCellule();
    if (cell->type_valeur == CHAR_LISTE)
    {
        cell2->valeur.s = copie_sequence(cell->valeur.s);
    }
    else
    {
        cell2->valeur = cell->valeur;
    }
    cell2->type_valeur = cell->type_valeur;
    cell2->suivant = NULL;
    empiler(pile, cell2);
}

void ignore(sequence_t *pile)
{
    retirer_tete(pile);
}

void boucle(sequence_t *routine, sequence_t *pile)
{
    cellule_t *cell_n = depiler(pile);
    sequence_t *cmd = depiler_seq(pile);
    
    if (cell_n->valeur.n > 0)
    {
        cell_n->valeur.n--;
        cellule_t *cell_cmd = nouvelleCellule();
        cell_cmd->valeur.s = cmd;
        cell_cmd->type_valeur = CHAR_LISTE;
        cell_cmd->suivant = NULL;
        empiler(pile, cell_cmd);
        empiler(pile, cell_n);
        cellule_t *cell_B = nouvelleCellule();
        cell_B->valeur.l = 'B';
        cell_B->type_valeur = CHAR;
        cell_B->suivant = NULL;
        empiler(routine, cell_B);
        inserer_liste_debut(routine, copie_sequence(cmd));
    }
}

void rotation(sequence_t *pile)
{
    int x = depiler_int(pile);
    int n = depiler_int(pile);
    if (n == 1){
        return;
    }
    cellule_t *cell;
    cellule_t *cell2;
    sequence_t *seq = nouvelle_seq();
    for (int i = 0; i < n; i++)
    {
        cell = depiler(pile);
        ajout_debut(seq, cell);
    }
    afficher(seq);
    printf("\n");
    cell = seq->tete;
    for (int i = 0; i < n; i++)
    {

        if (i >= x)
        {
            cell2 = nouvelleCellule();
            cell2->valeur = cell->valeur;
            cell2->type_valeur = cell->type_valeur;
            empiler(pile, cell2);
        }
        cell = cell->suivant; 
    }

    cell = seq->tete;
    for (int i = 0; i <x; i++)
    {
        cell2 = nouvelleCellule();
        cell2->valeur = cell->valeur;
        cell2->type_valeur = cell->type_valeur;
        empiler(pile, cell2);
        cell = cell->suivant;
    }
}