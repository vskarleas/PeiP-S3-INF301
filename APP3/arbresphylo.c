#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

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

void creer_graph(arbre a, char *nom_fichier)
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
   init_liste_vide(seq);
   bool est_animal_trouve = carac_espece(racine, seq, espece);
   if (est_animal_trouve)
   {
      afficher_liste_t(seq);
      return 0;
   }
   else
   {
      printf("%s n'existe pas dans l'arbre.\n", espece);
      return 1;
   }

   
}

bool carac_espece(arbre a, liste_t *seq, char *espece)
{
   if (a == NULL)
   {
      return false;
   }
   if (strcmp(espece, a->valeur) == 0)
   {
      return true;
   }
   if (a->gauche != NULL)
   {
      if (carac_espece(a->gauche, seq, espece))
      {
         return true;
      }
      if (carac_espece(a->droit, seq, espece))
      {
         ajouter_tete(seq, a->valeur);
         return true;
      }
   }
   return false;
}

/* Doit renvoyer 0 si l’espèce a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq)
{
   if (*a == NULL)
   {
      noeud *n = nouveau_noeud();
      if (seq==NULL)
      {
         modifier_valeur_noeud(n, espece);
         *a = n;
         return 0;
      }
      else
      {
         modifier_valeur_noeud(n, seq->val);
         *a = n;
         return ajouter_espece(&(*a)->droit, espece, seq->suivant);
      }
      
   }
   else if ((*a)->gauche==NULL && (*a)->droit==NULL)
   {
      if (seq==NULL)
      {
         eprintf("Ne peut ajouter %s : possède les mêmes caractères que %s", espece, (*a)->valeur);
         return 1;
      }
      noeud *n = nouveau_noeud();
      modifier_valeur_noeud(n, seq->val);
      n->gauche = *a;
      *a = n;
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
   }
   else if (strcmp(valeur(seq), (*a)->valeur)==0)
   {
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
   }
   else
   {
      return ajouter_espece(&(*a)->gauche, espece, seq);
   }
   return 1;
}

bool est_carac(noeud *n){
   if(n == NULL)
      return false;
   return n->gauche != NULL || n->droit != NULL;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
/*
void afficher_par_niveau(arbre racine, FILE* fout)
{
   if (racine!=NULL)
   {
      int index_noeud = 0;
      int nb_noeuds_passes = 0;
      int nb_noeud_niveau_prochaine = 0;

   }
}
*/

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
   printf("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
