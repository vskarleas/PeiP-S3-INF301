#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "algos_decodage_codage.h"

#define MAXMSG MAXREP



int main() {
    char reponse[MAXREP]; // pour stocker la reponse du serveur
    //char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les echanges avec le serveur (false pour desactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    envoyer_recevoir("load crypteMove", reponse);
    envoyer_recevoir("aide", reponse);
    char texte[10000];
    strcpy(texte, reponse);
    envoyer_recevoir("start", reponse);
    char texte_code[100000];
    coder_texte_crypteMove(texte, texte_code);
    envoyer_recevoir(texte_code, reponse);

    printf("Reponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
