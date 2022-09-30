#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "algos_decodage_codage.h"

#define MAXMSG MAXREP



int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    //char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    envoyer_recevoir("load OneMillion", reponse);
    char texte_code[10000];
    char texte_decode[10000];
    strcpy(texte_code, reponse);
    decoder_texte_decrypteMove(texte_code, texte_decode);
    printf("%s\n", texte_decode);

    envoyer_recevoir("aide", reponse);
    char chaine_a_repeter[101];
    strcpy(chaine_a_repeter, reponse);

    envoyer_recevoir("start", reponse);
    char clef[101];
    strcpy(clef, reponse);


    char texte_crypte[1000001];
    char texte_decrypte[1000001];
    for (int i = 0; i < 9999; i++)
    {
        strcat(texte_crypte, chaine_a_repeter);
    }
    strcat(texte_crypte, clef);
    texte_crypte[1000000] = '\0';

    decoder_texte_decrypteMove_rapide(texte_crypte, texte_decrypte);
    char texte_a_envoyer[101];
    int i;
    for (i = 0; i < 100; i++)
    {
        texte_a_envoyer[i] = texte_decrypte[i];
    }
    texte_a_envoyer[i + 1] = '\0';
    envoyer_recevoir(texte_a_envoyer, reponse);

    printf("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
