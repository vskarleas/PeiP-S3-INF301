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

/*Trouve le nombre des especes et des caracteristiques sur un arbre donné*/
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

/*Fonction principale qui ouvre le fichier ou 
l'arbre en format dot va être sauvegradé*/
void creer_graph(arbre a, char *nom_fichier)
{
   FILE *f = fopen(nom_fichier, "w");
   fprintf(f, "digraph arbre {\n");
   ecrire_arbre(a, f); //Analyse de l'arbre qui le transform en format dot
   fprintf(f, "}\n");
   fclose(f);
}

/*Ecris l'arbre en format dot*/
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

/*Retourne vrai si la valeur de l'arbre est l'espece passée en argument, faux sinon*/
bool carac_espece(arbre a, liste_t *seq, char *espece)
{
   if (a == NULL)
   {
      return false; //Par definition si l'arbre est vide, il est impossible que l'espece existe
   }
   if (strcmp(espece, a->valeur) == 0)
   {
      return true;
   }
   /*On verifie les valeurs des fils recursivement*/
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
 * message d'erreur. Objectif: Ajouter un espece dans un arbre phylogenetique
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq)
{
   if (*a == NULL)
   {
      noeud *n = nouveau_noeud();
      /*Si l'arbre et la séquence sont null, on ajoute un noeud puis on lui donne comme valeur l'espece 
      a insérer*/
      if (seq == NULL) 
      {
         modifier_valeur_noeud(n, espece);
         *a = n;
         return 0;
      }
      /*Si juste l'arbre est null, on modifie la valeur du noeud et on fait un appel récursif sur l'arbre droit*/
      else
      {
         modifier_valeur_noeud(n, seq->val);
         *a = n;
         return ajouter_espece(&(*a)->droit, espece, seq->suivant);
      }
   }
   else if ((*a)->gauche == NULL && (*a)->droit == NULL)
   {
      /*Si on arrive à une feuille dans l'arbre et que la sequence est vide, on ne peut pas
      ajouter l'espece car elle a les memes caracteristiques qu'une autre.*/
      if (seq == NULL)
      {
         eprintf("Ne peut ajouter %s : possède les mêmes caractères que %s", espece, (*a)->valeur);
         return 1;
      }
      /*Si la sequence n'est pas vide, alors on cree un nouveau noeud et on ajoute la caracteristique
      de la sequence puis on fait un appel recursif de cette fonction sur l'arbre droit
      jusqu'à ce que l'espece soit inséree*/
      noeud *n = nouveau_noeud();
      modifier_valeur_noeud(n, seq->val);
      n->gauche = *a;
      *a = n;
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
   }
   /*Si la sequence est null ou que la valeur de la sequence et la valeur de l'arbre ne sont pas les meme,
   alors on fait un appel recursif sur l'arbre gauche pour que l'espece n'ai pas cette caracteristique*/
   else if (seq == NULL || strcmp(valeur(seq), (*a)->valeur) != 0)
   {
      return ajouter_espece(&(*a)->gauche, espece, seq);
   }
   /*Si la valeur de la séquence et la valeur de l'arbre sont les memes, alors on fait un appel
   recursif sur l'abre droit */
   else if (strcmp(valeur(seq), (*a)->valeur) == 0)
   {
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
   }
   return 1;
}

/*Renvoi true si la aleur du noeud est un caractere, false sinon*/
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
      /*Initialisation des variables*/
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
      /*Creation de la file et ajout de la racine dans la file*/
      file *fl = nvelle_file();
      ajouter_fin(fl, racine);
      while (!est_vide_file(fl))
      {
         noeud *n = tete_file(fl);
         supprimer_tete(fl);
         index_noeud++;

         if (est_carac(n))
         {
            /*Si n est une caracteristique, alors on l'écrit dans le fichier*/
            fprintf(fout, "%s ", n->valeur);
            if (n->gauche != NULL)
            {
               /*Si la partie gauche à partir n'est pas null, alors on incremente la variable
               et on ajouter à la file la partie gauche du noeud*/
               nb_noeuds_niveau_prochain++;
               ajouter_fin(fl, n->gauche);
            }
            if (n->droit != NULL)
            {
               /*Si la partie droit à partir n'est pas null, alors on incremente la variable
               et on ajouter à la file la partie droit du noeud*/
               nb_noeuds_niveau_prochain++;
               ajouter_fin(fl, n->droit);
            }
         }
         if (index_noeud == nb_noeuds_passes)
         {
            /*Si les deux variables sont égales, on change de niveau*/
            nb_noeuds_passes += nb_noeuds_niveau_prochain;
            nb_noeuds_niveau_prochain = 0;
            fprintf(fout, "\n");
         }
      }
   }
}

// Acte 4

/*Ajouter une caractéristique dans un arbre*/
int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
   /*Initialisation des variables, liste, file*/
   bool tout_dedans;
   bool que_ca;
   bool ajoute = false;
   file_a *fl = nvelle_file_a();
   liste_t *animaux = malloc(sizeof(liste_t));
   init_liste_vide(animaux);
   ajouter_fin_a(fl, a);
   /**/
   while (!est_vide_file_a(fl) && !ajoute)
   {
      arbre *a1 = tete_file_a(fl);
      supprimer_tete_a(fl);
      liste_animaux(a1, animaux);
      tout_dedans = est_tout_dedans(animaux, seq);
      if (tout_dedans)
      {
         que_ca = est_que_ca(animaux, seq);
         /* FIXME: Si cette fonction renvoi true, alors on admet qu'il que l'espece qu'on
a commencé la verification dans la liste. Ici on ne verifie que le 
longueur de la liste et de la sequence, comme on a déjà verifié que l'espece est 
dans la liste via la fonction "est_tout_dedans". */
         if (que_ca)
         {
            //FIXME:Si dans la sequence, il y a tous les elements est pas plus alors on ajoute la caractéristique
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
   /*Si on a pas pu ajouter la caractéristique, on renvoi un message d'erreur*/
   if (!ajoute)
   {
      eprintf("Ne peut ajouter %s : ne forme pas un sous-arbre\n", carac);
      return 0;
   }
   return 1;
}

//FIXME: je ne sais plus exactement
/*Creation d'une liste des especes par un arbre
passé en argument.*/
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
         /*On a trouvé un espece, alors on l'ajout sur la 
         liste ou on a son addresse memoire en argument de 
         la fonction "liste_animaux"*/
         ajouter_tete(liste, (*a)->valeur);
      }
   }
}

/*Revoi true si tous les elements de la sequence sont dans la liste, false sinon*/
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

/*Renvoi true si l'espece est dans la 
liste passé en argument, false sinon*/
bool est_dedans(cellule_t *liste, char *espece)
{
   if (liste == NULL)
   {
      return false; //Par definition, si la liste est vide, alors impossible que l'espece est dans la liste
   }
   bool a = (strcmp(liste->val, espece) == 0); //Comparaison avec la tete de la liste
   if (a)
      return true;
   bool b = est_dedans(liste->suivant, espece);//Comparaison avec la reste de la liste recursivement
   if (b)
      return true;
   return false;
}

/*Renvoi true si la longueur de la sequence et de la liste sont les memes, c'est-à-dire
si dans le liste et la séquence il n'y a pas plus d'elements, false sinon*/
bool est_que_ca(liste_t *liste, cellule_t *seq)
{
   //Initialisation des variables
   int lg_seq = 0;
   int lg_liste = 0;
   cellule_t *cell = seq;
   //Parcours de la liste
   while (cell != NULL)
   {
      lg_seq++;
      cell = cell->suivant;
   }
   cellule_t *cell2 = liste->tete;
   //Parcours de la sequence
   while (cell2 != NULL)
   {
      lg_liste++;
      cell2 = cell2->suivant;
   }
   //Comparaison des resultats des parcours
   return lg_seq == lg_liste;
}

/*Insere une caractéristique et met le sous arbre à droite de cette caractéristique*/
void inserer_cara(arbre *a, char *carac)
{
   noeud *n = nouveau_noeud();
   n->valeur = malloc(sizeof(char) * 512);
   strcpy(n->valeur, carac);
   /*On doit l'insere à doit par defintion de l'arbre 
   phylogenetqiue de l'APP3*/
   n->droit = *a;
   *a = n;
}