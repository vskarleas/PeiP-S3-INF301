#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac)
{
   *nb_esp = 0;
   *nb_carac = 0;
   compte_esp_carac(racine, nb_esp, nb_carac);
}

void compte_esp_carac(arbre racine, int *nb_esp, int *nb_carac)
{
   if (racine != NULL)
   {

      if (racine->gauche == NULL && racine->droit == NULL)
      {
         *nb_esp += 1;
      }
      else
      {
         compte_esp_carac(racine->gauche, nb_esp, nb_carac);
         compte_esp_carac(racine->droit, nb_esp, nb_carac);
         *nb_carac += 1;
      }
   }
}

void creer_graph(arbre a, char* nom_fichier)
{
   FILE *f = fopen(nom_fichier, "w");
   fprintf(f, "digraph arbre {\n");
   ecrire_arbre(a, f);
   fprintf(f, "}\n");
   fclose(f);
}

void ecrire_arbre(arbre a, FILE *f)
{
   if (a != NULL)
   {
      if (a->gauche != NULL)
      {
         fprintf(f, "\t%s -> %s [label = \"non\"]\n", a->valeur, a->gauche->valeur);
         ecrire_arbre(a->gauche, f);
      }
      if (a->droit != NULL)
      {
         fprintf(f, "\t%s -> %s [label = \"oui\"]\n", a->valeur, a->droit->valeur);
         ecrire_arbre(a->droit, f);
      }
   }
}

    /* ACTE II */
    /* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
     * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
     */
    int rechercher_espece(arbre racine, char *espece, liste_t *seq)
{
   /* à compléter */
   return 1;
}

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq)
{

   return 1;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE *fout)
{
   printf("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
   printf("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
