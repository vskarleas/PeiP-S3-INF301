#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "algos_decodage_codage.h"

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    char texte_decode[100000];
    char texte_code[100000];
    char mdp[1000];

     // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108112 TREHIN", reponse);

    //ouvre l'exercise NothWoods
    envoyer_recevoir("load Northwoods", reponse);

    //envoyer la commande 'aide'
    envoyer_recevoir("aide", reponse);

    //envoyer la commande 'start'. Apres server attend le mot de passe metnione avant
    envoyer_recevoir("start", reponse);

    //envoyer mot de page
    envoyer_recevoir("hasta la victoria siempre", reponse);

    //re-initiliase les tableaux declares au debut du programme 
    texte_decode[0] = '\0';
    texte_code[0] = '\0';

    //On fait une copie de la reponse sur la variable texte pour le 
    //decrypter, comme la variable reponse est dynamique et il change en
    //chaque action 'envoyer_recevoir'
    strcpy(texte_code, reponse);

    //decryptage du texte code en utilisant l'alorithme de decryptage crypteSeq
    decrypter_txt_crypteSeq(texte_code, texte_decode);

    //affichage sur l'ecran du message pour qu'on peut le lire
    printf("%s\n", texte_decode);

    //recuperation du mot de passe dynamique ~ il change chaque fois que le programme relanche
    recuperer_mdp(texte_decode, mdp);

    //envoyer le mot de passe lu dans cette execution du programme par la fonctionne precedente
    envoyer_recevoir(mdp, reponse);


    //re-initiliase les tableaux declares au debut du programme 
    texte_decode[0] = '\0';
    texte_code[0] = '\0';

    //On fait une copie de la reponse sur la variable texte pour le 
    //decrypter, comme la variable reponse est dynamique et il change en
    //chaque action 'envoyer_recevoir'
    strcpy(texte_code, reponse);

    //decryptage du texte code en utilisant l'alorithme de decryptage crypteSeq
    decrypter_txt_crypteSeq(texte_code, texte_decode);

    //affichage sur l'ecran du message pour qu'on peut le lire
    printf("%s\n", texte_decode);

    //initilisation des tableaux pour faire le cryptage de mot de passe trouve en message precedent
    char texte_decode1[100000];
    char texte_code1[100000];

    //On fait une copie du mot de passe sur la variable texte_decode1 pour le crypter
    strcpy(texte_decode1, "There will be no Nineteen Eighty-Four");

    //cryptage du mot de passe en utilisant l'algorithme crypteSeq
    crypter_txt_crypteSeq(texte_decode1, texte_code1);

    //envoyer le mot de passe crypte
    envoyer_recevoir(texte_code1, reponse);

    //re-initiliase les tableaux declares au debut du programme 
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    int i;
    for (i = 0; reponse[i] != 'B'; i++) //On passe tous les autres characters jusque qu'on arrive à B comme le message qu'on doit decrypter commence par le mot Bob
    {

    }
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    int j;
    for (j = 0; reponse[j + i] != '\0'; j++) //sauvgarder le message qu'on doit decrypter via un parcours du message code character par character
    {
        texte_code[j] = reponse[j + i];
    }
    texte_code[j+1] = '\0';

    //decryptage du message lu 
    decrypter_txt_crypteSeq(texte_code, texte_decode);

    //affichage du message sur l'ecran pour qu'on peut le lire 
    printf("%s\n", texte_decode);

    printf ("Réponse du serveur: %s", reponse);

    //Connection termine
    printf ("Fin de la connection au serveur\n");
    //#endif
    return 0;
}
