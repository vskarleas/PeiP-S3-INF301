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
    char texte[10000];
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    envoyer_recevoir("load BayOfPigs", reponse);
    strcpy(texte, reponse);
    remplacer_texte_cesar(texte,21);
    printf("%s\n", texte);
    envoyer_recevoir("aide", reponse);
    strcpy(texte, reponse);
    remplacer_texte_cesar(texte,21);
    printf("%s\n", texte);
    envoyer_recevoir("start", reponse);
    char texte_code[100000];
    /*
    char texte_decode[100000];
    strcpy(texte_code, reponse);
    decoder_texte_decrypteMove(texte_code, texte_decode);
    envoyer_recevoir(texte_decode, reponse);
    */
    strcpy(texte, "Patria o muerte");
    coder_texte_crypteMove(texte, texte_code);
    envoyer_recevoir(texte_code, reponse);
    char texte_decode[100000];
    strcpy(texte_code, reponse);
    decoder_texte_decrypteMove(texte_code, texte_decode);
    envoyer_recevoir(texte_decode, reponse);

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
