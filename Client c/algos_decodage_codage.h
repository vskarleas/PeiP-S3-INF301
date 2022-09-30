#include <stdio.h>
#include <string.h>


char remplacer_lettre(char lettre, int decalage);

void remplacer_texte_cesar(char *nom_fichier_code, int decalage);

int trouver_decalage(char *texte);

void remplacer_texte_cesar_automatique(char *texte);

void decalage_a_gauche(char *texte, int n);

void decalage_a_droite(char *texte, int longueur_texte, int n);

void copier_bloc_de_lettres(char *texte, char *texte_tmp, int debut, int fin);

void coder_texte_crypteMove(char *texte, char* texte_code);

void ecrire_bloc_de_lettres_au_debut(char *texte_source, char *texte_destination, int taille_texte_source);

void ajouter_au_debut(char *texte, int longueur_texte, char lettre_a_ajouter);

void decoder_texte_decrypteMove(char *texte_code, char* texte_decode);

void crypter_txt_crypteSeq(char *txt, char *txt_crypte);

void decrypter_txt_crypteSeq(char *txt_crypte, char *txt_decrypte);

void recuperer_mdp(char *txt, char *mdp);