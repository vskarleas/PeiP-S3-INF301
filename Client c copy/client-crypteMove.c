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

    //ouvre l'exercise crypteMove
    envoyer_recevoir("load crypteMove", reponse);

    //envoyer la commande 'aide' pour requpere le texte qu'on doit crypter
    envoyer_recevoir("aide", reponse);

    //On fait une copie de la reponse sur la variable texte pour le 
    //crypter comme la varibale reponse est dynamique et il change en
    //chaque action 'envoyer_recevoir'
    char texte[10000];
    strcpy(texte, reponse);

    //envoyer la commande 'start'. Apres server attend notre message crypte
    envoyer_recevoir("start", reponse);

    //initialisation du tableau pour le texte crypte
    char texte_code[100000];

    //crypte le texte en utilisant l'algorithme 
    coder_texte_crypteMove(texte, texte_code);

    //envoyer le texte crypte
    envoyer_recevoir(texte_code, reponse);

    printf("Reponse du serveur: %s", reponse);

    //Connection termine
    printf ("Fin de la connection au serveur\n");
    return 0;
}
