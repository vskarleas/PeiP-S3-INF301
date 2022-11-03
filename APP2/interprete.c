#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "commandes.h"

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop(void)
{
    char enter = '\0';
    printf("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n')
    {
        enter = getchar();
    }
}

/* Acte I.2 */
int interprete(sequence_t *seq, bool debug)
{
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.

    char commande;
    sequence_t *pile = malloc(sizeof(sequence_t));

    // debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf("Programme:");
    afficher(seq);
    printf("\n");
    if (debug)
        stop();

    // À partir d'ici, beaucoup de choses à modifier dans la suite.
    cellule_t *cell_actuelle = depiler(seq);
    cellule_t *cell_a_ajouter = NULL;

    int ret; // utilisée pour les valeurs de retour

    while (seq->tete != NULL)
    { //à modifier: condition de boucle
        switch (cell_actuelle->type_valeur)
        {
        case INT:
            empiler_int(pile, cell_actuelle->valeur.n);
            break;
        case CHAR:
            commande = cell_actuelle->valeur.l;
            switch (commande)
            {
                /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

            case 'A':
                ret = avance();
                if (ret == VICTOIRE)
                    return VICTOIRE; /* on a atteint la cible */
                if (ret == RATE)
                    return RATE; /* tombé dans l'eau ou sur un rocher */
                break;           /* à ne jamais oublier !!! */
            case 'G':
                gauche();
                break;
            case 'D':
                droite();
                break;
            case '+':
                /* Addition: depile les deux éléments
                en haut de la pile, les somme, puis ré-empile le
                résultat.*/
                addition(pile);
                break;
            case '-':
                /* Soustraction: depile les deux éléments en haut
                de la pile, les soustrait, puis ré-empiler
                le résultat.*/
                soustraction(pile);
                break;
            case '*':
                /* Multiplication: depile les deux éléments
                en haut de la pile, les multiplis, puis
                ré-empiler le résultat.*/
                multiplication(pile);
                break;
            case 'M':
                /*Mesure : effectue une mesure dans une certaine direction
                et empile le numéro de la direction associé*/
                empiler_int(pile,mesure(depiler_int(pile)));
                break;
            case 'P':
                /*Pose ou enleve une marque au sol*/
                pose(depiler_int(pile));
                break;
            case '?':
                /*Selon l'entier au sommet de la pile, 
                un groupe de commande délimité par des 
                accolades sera empiler puis exécuté*/
                execution_coditionnelle(seq, pile);
                break;
            case 'X':
                /*Echange les deux elements au
                sommet de la pile*/
                echange(pile);
                break;
            case '!':
                /*Extrait l'élement au sommet 
                de la pile, le met dans la routine 
                est l'exécute*/
                exec(seq, pile);
                break;
            case 'C':
                /*Clone le sommet de la pile*/
                clone(pile);
                break;
            case 'I':
                /*Ignore l'élément en haut de la pile*/
                ignore(pile);
                break;
            case 'B':
                /*Exécute une commande n fois*/
                boucle(seq, pile);
                break;
            case 'R':
                /*Effectue une rotation de certains éléments 
                en haut de la pile vers la gauche*/
                rotation(pile);
                break;
            case 'Z':
                operation_Z(pile);
                break;
            }
            break;
        case CHAR_LISTE:
            cell_a_ajouter = nouvelleCellule();
            cell_a_ajouter->valeur.s = cell_actuelle->valeur.s;
            cell_a_ajouter->type_valeur = CHAR_LISTE;
            empiler(pile, cell_a_ajouter);
            break;
        }

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf("Programme:");
        afficher(seq);
        printf("\n");
        printf("Pile : ");
        afficher(pile);
        printf("\n");
        if (debug)
            stop();
        cell_actuelle = depiler(seq);
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
