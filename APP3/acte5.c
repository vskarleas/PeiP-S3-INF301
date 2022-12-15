#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "listes.h"
#include "table_phylo.h"
#include "arbres.h"
#include "arbresphylo.h"

int main(int argc, char **argv)
{
    arbre a = nouveau_noeud();
    int nb_carac;
    sscanf(argv[2], "%d", &nb_carac);
    creer_arbre_table(&a, argv[1], nb_carac);
    FILE *f_sortie = fopen(argv[3], "w");
    ecrire_arbre(a, f_sortie);
    fclose(f_sortie);
}
