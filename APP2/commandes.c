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
    empiler_int(pile, x - y);
}

void multiplication(sequence_t *pile) // Multiplication entre deux elements de la pile (le resulat est empile sur le pile)
{
    int x = depiler_int(pile);
    int y = depiler_int(pile);
    empiler_int(pile, x * y);
}

void execution_coditionnelle(sequence_t *routine, sequence_t *pile)
{
    sequence_t *commande_1 = depiler_seq(pile);
    sequence_t *commande_2 = depiler_seq(pile);
    int x = depiler_int(pile);
    if (x == 0)
    {
        empiler_seq(routine, commande_1);
    }
    else
    {
        empiler_seq(routine, commande_2);
    }
}

/* Acte V */
/*
void clone(sequence_t *pile)
{
    if (depiler(pile)->type_valeur == INT){
        cellule_t *cell = tete(pile);

    }
    else if (depiler(pile)->type_valeur == CHAR){

    }
    else if (depiler(pile)->type_valeur == CHAR_LISTE)
    {

    }
}
*/

/*
//Il me semble beaucoup à la fonctionalité retirer_tete
void ignore(sequence_t *pile)
{
    retirer_tete(pile);
}
*/

/*
void echange(sequence_t *pile)
{
    if (depiler(pile)->type_valeur == INT){
        int x = depiler_int(pile);
        int y = depiler_int(pile);
        empiler_int(pile, x);
        empiler_int(pile, y);
    }
    else if (depiler(pile)->type_valeur == CHAR){
        char xi = depiler_char(pile);
        char yi = depiler_char(pile);
        empiler_char(pile, xi);
        empiler_char(pile, yi);
    }
    else if (depiler(pile)->type_valeur == CHAR_LISTE)
    {
        cellule_t *cell1 = depiler_seq(pile);
        cellule_t *cell2 = depiler_seq(pile);
        empiler_seq(pile, cell1);
        empiler_seq(pile, cell1);
    }
}
*/