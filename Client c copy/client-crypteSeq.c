#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "algos_decodage_codage.h"

#define MAXMSG MAXREP

int main() {
    /*
    char texte_decode[100000];
    char texte_code[100000];
    strcpy(texte_code, "abcaabc");
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);
    #if 0*/
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    //initilisation du tableau qui stocke les reponses du serveur necessaire comme reponse est utilise comme une variable dynamique
    char texte[10000];

    //initilisation du tableau pour stocker le contenu decode
    char texte_decode[100000];

    //initilisation du tableau pour stocker le contenu code
    char texte_code[100000];

    //ECRIRE COMMENTAIRES POUR CETTE PARTIE
    FILE *fichier = fopen("texte.txt", "r");

    for (int i = 0; !feof(fichier); i++)
    {
        fscanf(fichier, "%c", &texte_code[i]);
    }
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);

    crypter_txt_crypteSeq(texte_decode, texte_code);

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12108112 TREHIN", reponse);

    //ouvre l'exercise crypteSeq
    envoyer_recevoir("load crypteSeq", reponse);

    //On fait une copie de la reponse sur la variable texte pour le 
    //decrypter, comme la variable reponse est dynamique et il change en
    //chaque action 'envoyer_recevoir'
    strcpy(texte, reponse);

    //decodage du texte recu en reponse
    decoder_texte_decrypteMove(texte, texte_decode);

    //affichage sur l'ecran pour qu'on peut le lire
    printf("%s\n", texte_decode);

    //envoyer la commande 'aide'
    envoyer_recevoir("aide", reponse);

    //envoyer la commande 'start'. Apres server attend notre message crypte
    envoyer_recevoir("start", reponse);

    //re-initiliase les tableaux declares au debut du programme 
    texte_decode[0] = '\0';
    texte_code[0] = '\0';

    //On fait une copie de la reponse sur la variable texte pour le 
    //decrypter, comme la variable reponse est dynamique et il change en
    //chaque action 'envoyer_recevoir'
    strcpy(texte_code, reponse);

    //decrypte en utilisant l'algorithme de decryptage crypteMove
    decoder_texte_decrypteMove(texte_code, texte_decode);

    //affiche sur l'ecran le message pour qu'on peut le lire
    printf("%s\n", texte_decode);

    //cryptage du texte_decode en utilisant l'alorithme de cryptage crypteSeq
    crypter_txt_crypteSeq(texte_decode, texte_code);

    //envoyer le texte_code au server
    envoyer_recevoir(texte_code, reponse);

    //re-initiliase les tableaux declares au debut du programme 
    texte_decode[0] = '\0';
    texte_code[0] = '\0';

    //On fait une copie de la reponse sur la variable texte pour le 
    //decrypter, comme la variable reponse est dynamique et il change en
    //chaque action 'envoyer_recevoir'
    strcpy(texte_code, reponse);

    //decryptage du texte en utilisant l'algorithme de decryptage crypteSeq
    decrypter_txt_crypteSeq(texte_code, texte_decode);

    //envoyer le texte decrypte
    envoyer_recevoir(texte_decode, reponse);



    printf ("Réponse du serveur: %s", reponse);

    //Connection termine
    printf ("Fin de la connection au serveur\n");
    //#endif
    return 0;
}
