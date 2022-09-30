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
    //char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    char texte[10000];
    char texte_decode[100000];
    char texte_code[100000];
    FILE *fichier = fopen("texte.txt", "r");

    for (int i = 0; !feof(fichier); i++)
    {
        fscanf(fichier, "%c", &texte_code[i]);
    }
    decrypter_txt_crypteSeq(texte_code, texte_decode);
    printf("%s\n", texte_decode);

    crypter_txt_crypteSeq(texte_decode, texte_code);
    envoyer_recevoir("login 12108112 TREHIN", reponse);
    envoyer_recevoir("load crypteSeq", reponse);
    strcpy(texte, reponse);
    decoder_texte_decrypteMove(texte, texte_decode);
    printf("%s\n", texte_decode);
    envoyer_recevoir("aide", reponse);
    envoyer_recevoir("start", reponse);
    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    strcpy(texte_code, reponse);
    decoder_texte_decrypteMove(texte_code, texte_decode);

    printf("%s\n", texte_decode);
    crypter_txt_crypteSeq(texte_decode, texte_code);
    envoyer_recevoir(texte_code, reponse);

    texte_decode[0] = '\0';
    texte_code[0] = '\0';
    strcpy(texte_code, reponse);
    decrypter_txt_crypteSeq(texte_code, texte_decode);

    envoyer_recevoir(texte_decode, reponse);



    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    //#endif
    return 0;
}
