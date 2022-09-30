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
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    char messages[100][100] = {"load TUTORIEL", "aide", "start", "OK", "OUI"};
    int messages_len = 5;
    for (int i = 0; i < messages_len; i++)
    {
        envoyer_recevoir(messages[i], reponse);
    }

    int i;
    for (int j = 0; j < 6; j++)
    {
        i = 0;
        while (reponse[i] != '\0'){
            char lettre = reponse[i];
            if (isalpha(lettre)){
                char lettre_majuscule = toupper(lettre);
                message[i] = lettre_majuscule;
            }else{
                message[i] = lettre;
            }
            i++;
        }
        message[i] = '\0';
        envoyer_recevoir(message, reponse);
    }

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
