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
    //char texte[10000];
    char texte_decode[100000];
    char texte_code[100000];
    char mdp[1000];
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    envoyer_recevoir("load Northwoods", reponse);
    envoyer_recevoir("aide", reponse);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("hasta la victoria siempre", reponse);
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    strcpy(texte_code, reponse);
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);
    recuperer_mdp(texte_decode, mdp);
    envoyer_recevoir(mdp, reponse);

    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    strcpy(texte_code, reponse);
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);
    

    texte_decode[0] = '\0';
    texte_code[0] = '\0';

    char texte_decode1[100000];
    char texte_code1[100000];
    strcpy(texte_decode1, "There will be no Nineteen Eighty-Four");
    crypter_txt_crypteSeq(texte_decode1, texte_code1);

    envoyer_recevoir(texte_code1, reponse);
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    int i;
    for (i = 0; reponse[i] != 'B'; i++)
    {

    }
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    int j;
    for (j = 0; reponse[j + i] != '\0'; j++)
    {
        texte_code[j] = reponse[j + i];
    }
    texte_code[j+1] = '\0';
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);

/*
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    strcpy(texte_code, reponse);
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);
*/
    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    //#endif
    return 0;
}
