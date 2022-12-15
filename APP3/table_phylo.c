#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "table_phylo.h"
#include "arbres.h"
#include "arbresphylo.h"

#define TAILLE_MAX_LIGNE 1024
#define TAILLE_MAX_CASE 1024

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

liste_p_t *init_liste_p_t()
{
    liste_p_t *l = malloc(sizeof(liste_p_t));
    l->tete = NULL;
    return l;
}

void lire_table(char *nom_fichier, int nb_carac, liste_p_t *caracs, liste_p_t *table)
{
    FILE *f = fopen (nom_fichier, "r");
    if (f == NULL)
    {
        eprintf ("Erreur lors de l'ouverture du fichier : %s\n",nom_fichier);
        exit (1);
    }
    char ligne[TAILLE_MAX_LIGNE];
    //char contenu_case[TAILLE_MAX_CASE];
    int index_colonne;

    // Récupérer les caractérisiques
    fgets(ligne, TAILLE_MAX_LIGNE, f);
    char *contenu_case= strtok(ligne, ",");
    for (index_colonne = 0; index_colonne < nb_carac + 1; index_colonne++)
    {
        if (index_colonne == 0)
        {
            contenu_case = strtok(NULL, ",");
            continue;
        }
        ajouter_tete_p(caracs, contenu_case, 0);
        contenu_case = strtok(NULL, ",");
    }
    cellule_p_t *cell_carac;

    // compte le nombre de oui de chaque caractérisitque
    char espece[TAILLE_MAX_CASE];
    while (fgets(ligne, TAILLE_MAX_LIGNE, f))
    {
        cell_carac = caracs->tete;
        char *contenu_case = strtok(ligne, ",");
        for (index_colonne = 0; index_colonne < nb_carac; index_colonne++)
        {
            if (index_colonne == 0)
            {
                strcpy(espece, contenu_case);
                ajouter_tete_p(table, espece, 0);
            }
            if (strcmp(contenu_case, "oui") == 0)
            {
                ajouter_tete(cell_carac->especes, espece);

                cell_carac->nb_especes++;
            }
            contenu_case = strtok(NULL, ",");
            cell_carac = cell_carac->suivant;
        }
    }

    tri_liste_p(caracs);
    cellule_t *cell_especes;
    cell_carac = caracs->tete;
    while (cell_carac != NULL)
    {
        cell_especes = cell_carac->especes->tete;
        while (cell_especes != NULL)
        {
            ajouter_carac_a_espece(table, cell_especes->val, cell_carac->carac);
            cell_especes = cell_especes->suivant;
        }
        cell_carac = cell_carac->suivant;
    }

    fclose(f);
}

void ajouter_carac_a_espece(liste_p_t *table, char *espece, char * carac)
{
    cellule_p_t *cell = table->tete;
    while (strcmp(cell->carac,espece)!=0)
    {
        cell = cell->suivant;
    }
    ajouter_tete(cell->especes, carac);
}

void tri_liste_p(liste_p_t *l)
{
    cellule_p_t *cell = l->tete;
    if (l->tete != NULL)
    {
        l->tete = l->tete->suivant;
    }
    liste_p_t l_tmp;
    l_tmp.tete = NULL;
    while (cell != NULL)
    {
        cell->suivant = NULL;
        insertion_trie_croissant(&l_tmp, cell);
        cell = l->tete;
        if (l->tete != NULL)
        {
        l->tete = l->tete->suivant;
        }
    }
    l->tete = l_tmp.tete;
}

/*Ajoute un string à la liste*/
int ajouter_tete_p(liste_p_t *L, string carac, int n)
{ /* retourne 0 si OK, 1 sinon  */
    // renvoyer 1 si les mallocs renvoient null (plus assez de memoire)c
    cellule_p_t *nv_tete = calloc(1, sizeof(cellule_p_t));
    if (nv_tete == NULL)
    {
        return 1;
    }
    if (strlen(carac) != 0)
    {
        nv_tete->carac = malloc(sizeof(char) * (strlen(carac) + 1));
        strcpy(nv_tete->carac, carac);
    }
    else
    {
        nv_tete->carac = malloc(1);
        nv_tete->carac[0] = '\0';
    }
    nv_tete->nb_especes = n;
    nv_tete->suivant = L->tete;
    L->tete = nv_tete;
    L->tete->especes = malloc(sizeof(char) * TAILLE_MAX_CASE);

    return 0;
}

void insertion_trie_croissant(liste_p_t *l, cellule_p_t *cell)
{
    cellule_p_t *cell_l = l->tete;
    if (cell_l == NULL)
    {
        l->tete = cell;
        return;
    }
    if (cell->nb_especes < cell_l->nb_especes)
    {
        cell->suivant = l->tete;
        l->tete = cell;
    }
    while (cell_l->suivant != NULL && cell_l->nb_especes < cell_l->suivant->nb_especes)
    {
        cell_l = cell_l->suivant;
    }
    cell->suivant = cell_l->suivant;
    cell_l->suivant = cell;
}

void creer_arbre_table(arbre *a,char *nom_fichier, int nb_carac)
{
    liste_p_t *caracs = init_liste_p_t();
    liste_p_t *table = init_liste_p_t();
    lire_table(nom_fichier, nb_carac, caracs, table);

    cellule_p_t *cell_table;
    cell_table = table->tete;
    while (cell_table != NULL)
    {
        ajouter_espece(a, cell_table->carac, cell_table->especes->tete);
        cell_table = cell_table->suivant;
    }
}