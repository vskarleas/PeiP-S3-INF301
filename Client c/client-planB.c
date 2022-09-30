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
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    

    char texte[10000];
    envoyer_recevoir("load planB", reponse);
    envoyer_recevoir("aide", reponse);
    strcpy(texte, reponse);
    int decalage = trouver_decalage(texte);
    remplacer_texte_cesar_automatique(texte);
    printf("%s\n", texte);

    envoyer_recevoir("start", reponse);
    printf("%d\n", decalage);
    char mot_de_passe[] = "hasta la revolucion";
    remplacer_texte_cesar(mot_de_passe, decalage);
    envoyer_recevoir(mot_de_passe, reponse);

    strcpy(texte, reponse);
    remplacer_texte_cesar(texte, decalage);
    printf("%s\n", texte);

    printf ("Reponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
