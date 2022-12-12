#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"
#include "file.h"
#include "file_a.h"

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
   }
   if (a->droit != NULL)
   {
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
      if (seq == NULL)
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
   else if ((*a)->gauche == NULL && (*a)->droit == NULL)
   {
      if (seq == NULL)
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
   else if (seq == NULL || strcmp(valeur(seq), (*a)->valeur) != 0)
   {
      return ajouter_espece(&(*a)->gauche, espece, seq);
   }
   else if (strcmp(valeur(seq), (*a)->valeur) == 0)
   {
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
   }
   return 1;
}

bool est_carac(noeud *n)
{
   if (n == NULL)
      return false;
   return n->gauche != NULL || n->droit != NULL;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */

void afficher_par_niveau(arbre racine, FILE *fout)
{
   if (racine != NULL)
   {
      int index_noeud = 0;
      int nb_noeuds_passes = 1;
      int nb_noeuds_niveau_prochain = 0;
      /*
      if (racine->gauche != NULL)
      {
         nb_noeuds_niveau_prochain++;
      }
      if (racine->droit != NULL)
      {
         nb_noeuds_niveau_prochain++;
      }
      */
      file *fl = nvelle_file();
      ajouter_fin(fl, racine);
      while (!est_vide_file(fl))
      {
         noeud *n = tete_file(fl);
         supprimer_tete(fl);
         index_noeud++;

         if (est_carac(n))
         {
            fprintf(fout, "%s ", n->valeur);
            if (n->gauche != NULL)
            {
               nb_noeuds_niveau_prochain++;
               ajouter_fin(fl, n->gauche);
            }
            if (n->droit != NULL)
            {
               nb_noeuds_niveau_prochain++;
               ajouter_fin(fl, n->droit);
            }
         }
         if (index_noeud == nb_noeuds_passes)
         {
            nb_noeuds_passes += nb_noeuds_niveau_prochain;
            nb_noeuds_niveau_prochain = 0;
            fprintf(fout, "\n");
         }
      }
   }
}

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
   bool tout_dedans;
   bool que_ca;
   bool ajoute = false;
   file_a *fl = nvelle_file_a();
   liste_t *animaux = malloc(sizeof(liste_t));
   init_liste_vide(animaux);
   ajouter_fin_a(fl, a);
   while (!est_vide_file_a(fl) && !ajoute)
   {
      arbre *a1 = tete_file_a(fl);
      supprimer_tete_a(fl);
      liste_animaux(a1, animaux);
      tout_dedans = est_tout_dedans(animaux, seq);
      if (tout_dedans)
      {
         que_ca = est_que_ca(animaux, seq);
         if (que_ca)
         {
            inserer_cara(a1, carac);
            ajoute = true;
            return 1;
         }
         if ((*a1)->gauche != NULL)
         {
            ajouter_fin_a(fl, &((*a1)->gauche));
         }
         if ((*a1)->droit != NULL)
         {
            ajouter_fin_a(fl, &((*a1)->droit));
         }
      }
   }
   if (!ajoute)
   {
      eprintf("Ne peut ajouter %s : ne forme pas un sous-arbre\n", carac);
      return 0;
   }
   return 1;
}

void liste_animaux(arbre *a, liste_t *liste)
{
   if (a != NULL)
   {
      if ((*a)->gauche != NULL)
      {
         liste_animaux(&(*a)->gauche, liste);
      }
      if ((*a)->droit != NULL)
      {
         liste_animaux(&(*a)->droit, liste);
      }
      if ((*a)->gauche == NULL && (*a)->droit == NULL)
      {
         ajouter_tete(liste, (*a)->valeur);
      }
   }
}

bool est_tout_dedans(liste_t *liste, cellule_t *seq)
{
   if (seq == NULL)
   {
      return true;
   }
   bool a = est_dedans(liste->tete, seq->val);
   if (!a)
      return false;
   bool b = est_tout_dedans(liste, seq->suivant);
   return a && b;
}

bool est_dedans(cellule_t *liste, char *espece)
{
   if (liste == NULL)
   {
      return false;
   }
   bool a = (strcmp(liste->val, espece) == 0);
   if (a)
      return true;
   bool b = est_dedans(liste->suivant, espece);
   if (b)
      return true;
   return false;
}

bool est_que_ca(liste_t *liste, cellule_t *seq)
{
   int lg_seq = 0;
   cellule_t *cell = seq;
   while (cell != NULL)
   {
      lg_seq++;
      cell = cell->suivant;
   }
   cellule_t *cell2 = liste->tete;
   int lg_liste = 0;
   while (cell2 != NULL)
   {
      lg_liste++;
      cell2 = cell2->suivant;
   }
   return lg_seq == lg_liste;
}

void inserer_cara(arbre *a, char *carac)
{
   noeud *n = nouveau_noeud();
   n->valeur = malloc(sizeof(char) * 512);
   strcpy(n->valeur, carac);
   n->droit = *a;
   *a = n;
}