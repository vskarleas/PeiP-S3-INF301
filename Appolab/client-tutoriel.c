#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115361 SKARLEAS", reponse);
    envoyer_recevoir("load tutoriel", reponse);
    // Notez qu'ici on n'utilise pas la reponse du serveur
    FILE *f;
    f = fopen("file.txt", "r");
    if (f == NULL) {
        printf("Je ne pourrait pas ouvrir le fichier\n") ;
		return 1 ;
    }
    int lignes;
    fscanf(f, "%d", &lignes);
    for (int i=0; i<lignes; i++) {
        fscanf(f, "%s", message);
        envoyer_recevoir(message, reponse);
    }
    

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
