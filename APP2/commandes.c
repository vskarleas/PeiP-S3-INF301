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

/*Soustraction entre deux elements
de la pile (le resulat est empile
sur la pile)*/
void soustraction(sequence_t *pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, y - x);
}

/*Multiplication entre deux elements
de la pile (le resulat est empile sur
la pile)*/
void multiplication(sequence_t *pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x * y);
}

/*
Selon l'entier au sommet de la pile,
un groupe de commande délimité par
des accolades sera empiler puis exécuté
*/
void execution_coditionnelle(sequence_t *routine, sequence_t *pile) // FIXME: il faudrait libérer l'espace des deux commandes mais ça cause problème
{
    sequence_t *commande_1 = depiler_seq(pile);
    sequence_t *commande_2 = depiler_seq(pile);
    sequence_t *commande_a_ajouter;
    int x = depiler_int(pile);
    /*Selon la valeur de x, on n'exécute pas le même bloc de commande*/
    if (x == 0)
    {
        commande_a_ajouter = copie_sequence(commande_1);
    }
    else
    {
        commande_a_ajouter = copie_sequence(commande_2);
    }
    inserer_liste_debut(routine, commande_a_ajouter);
}

//#define ACTE_V
#ifdef ACTE_V
/* Acte V */

// Il me semble beaucoup à la fonctionalité retirer_tete

#endif

/*
Echange les deux elements au sommet de la pile
*/
void echange(sequence_t *pile)
{
    cellule_t *cell1 = depiler(pile);
    cellule_t *cell2 = depiler(pile);
    /*On dépile les deux éléments et on les ré-empile en les échangeant*/
    empiler(pile, cell1);
    empiler(pile, cell2);
}

/*
Extrait l'élement au sommet de la pile,
le met dans la routine est l'exécute
*/
void exec(sequence_t *routine, sequence_t *pile)
{
    /*On a une séquence pour prendre en compte tout les cas possible
    (un caractere ou une chaine de caractere)*/
    sequence_t *seq = depiler_seq(pile);
    inserer_liste_debut(routine, seq);
}

/*
Clone le sommet de la pile
*/
void clone(sequence_t *pile)
{
    cellule_t *cell = tete(pile);
    cellule_t *cell2 = nouvelleCellule();
    /*On sépare deux cas, si le sommet est une séquence ou pas.
    Si c'est le cas il faut copier tout les éléments un par un dans le nouvelle cellule */
    if (cell->type_valeur == CHAR_LISTE)
    {
        cell2->valeur.s = copie_sequence(cell->valeur.s);
    }
    else
    {
        cell2->valeur = cell->valeur;
    }
    /*Les deux cellules (sommet et nouvelle cellule) ont le même type*/
    cell2->type_valeur = cell->type_valeur;
    cell2->suivant = NULL;
    /*On empile le clone du sommet*/
    empiler(pile, cell2);
}

/*
Ignore l'élément en haut de la pile
*/
void ignore(sequence_t *pile)
{
    /*On retire la tete de la pile, la nouvelle tete
    sera alors le suivant de la tete initiale*/
    retirer_tete(pile);
}

/*
Exécute une commande n fois
*/
void boucle(sequence_t *routine, sequence_t *pile)
{
    /*On dépile ne nombre de fois que l'on va exécuter la commande*/
    cellule_t *cell_n = depiler(pile);
    /*On dépile la commande à exécuter*/
    sequence_t *cmd = depiler_seq(pile);

    if (cell_n->valeur.n > 0)
    {
        /*décrémente n de 1*/
        cell_n->valeur.n--;
        cellule_t *cell_cmd = nouvelleCellule();
        cell_cmd->valeur.s = cmd;
        cell_cmd->type_valeur = CHAR_LISTE;
        cell_cmd->suivant = NULL;
        /*Empile la commande a exécuter et la nouvelle valeur de n dans la pile*/
        empiler(pile, cell_cmd);
        empiler(pile, cell_n);
        /*On empile B dans la routine pour rappeler cette fonction*/
        cellule_t *cell_B = nouvelleCellule();
        cell_B->valeur.l = 'B';
        cell_B->type_valeur = CHAR;
        cell_B->suivant = NULL;
        empiler(routine, cell_B);
        inserer_liste_debut(routine, copie_sequence(cmd));
    }
}

/*
Effectue une rotation de certains
éléments en haut de la pile vers la gauche
*/
void rotation(sequence_t *pile)
{
    int x = depiler_int(pile);
    int n = depiler_int(pile);
    /*Un décalage de 1 element vers la gauche ne change pas la séquence*/
    if (n == 1)
    {
        return;
    }
    cellule_t *cell;
    cellule_t *cell2;
    sequence_t *seq = nouvelle_seq();
    /*seq est une copie de la pile*/
    for (int i = 0; i < n; i++)
    {
        cell = depiler(pile);
        ajout_debut(seq, cell);
    }
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
    for (int i = 0; i < x; i++)
    {
        cell2 = nouvelleCellule();
        cell2->valeur = cell->valeur;
        cell2->type_valeur = cell->type_valeur;
        empiler(pile, cell2);
        cell = cell->suivant;
    }
}

void operation_Z(sequence_t *pile)
{
    retourner_sequence(pile);
}