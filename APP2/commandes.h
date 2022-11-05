#include "listes.h"
/*
Addition entre deux elements de la pile (le resulat est empile sur le pile)
*/
void addition(sequence_t *pile);

/*
Soustraction entre deux elements de la pile (le resulat est empile sur le pile)
*/
void soustraction(sequence_t *pile);

/*
Multiplication entre deux elements de la pile (le resulat est empile sur le pile)
*/
void multiplication(sequence_t *pile);

/*
Selon l'entier au sommet de la pile, un groupe de commande délimité par des accolades
sera empiler puis exécuté
*/
void execution_coditionnelle(sequence_t *routine, sequence_t *pile);

/*
Echange les deux elements au sommet de la pile
*/
void echange(sequence_t *pile);

/*
Extrait l’élément au sommet de la pile, le met dans la routine est l'exécute
*/
void exec(sequence_t *routine, sequence_t *pile);

/*
Clone le sommet de la pile
*/
void clone(sequence_t *pile);

/*
Ignore l'élément en haut de la pile
*/
void ignore(sequence_t *pile);

/*
Exécute une commande n fois
*/
void boucle(sequence_t *routine, sequence_t *pile);

/*
Effectue une rotation de certains éléments en haut de la pile vers la gauche
*/
void rotation(sequence_t *pile);

void operation_Z(sequence_t *pile);
