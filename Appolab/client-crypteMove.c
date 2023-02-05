#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void remove_lettre(char *str){
    memmove(str, str+1, strlen(str));
}
void swap_last(char *str) {
    const size_t len = strlen(str);
    if (len >1) {
        const char first=str[0];
        memmove(str, str+1, len-1);
        str[len-1]=first;
    }
}
int decalage(char *str) {
    return str[0]%8;
}
void premierLettre(char *str, char *coded) {
    char premlettre = str[0];
    coded[0]=premlettre;
}
void coder_texte(char *texte_originale, char *texte_code) {
    premierLettre(texte_originale, texte_code);
    remove_lettre(texte_originale);
    int dec;
    char lte;
    while(texte_originale[0]!='\0'){
        lte=texte_originale[0];
        dec=decalage(texte_originale);
        int len = strlen(texte_originale);
        if (dec<len){
            texte_code[strlen(texte_code)]=lte;
            remove_lettre(texte_originale);
            for (int i=0; i<dec; i++){
                swap_last(texte_originale);
            }
        }
        else {
            remove_lettre(texte_originale);
            texte_code[strlen(texte_code)]=lte;
        }
    }
}

int main() {
    char reponse[MAXREP];
    // pour stocker la réponse du serveur
    //char message[MAXMSG]; pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115361 SKARLEAS", reponse);

    char messages[100][100]={"load crypteMove"};
    int long_message=1;
    for (int i=0; i<long_message; i++) {
        envoyer_recevoir(messages[i], reponse);
    }

    char texteql[50000];
    envoyer_recevoir("aide", texteql);
    char final[50000];
    coder_texte(texteql, final);
    envoyer_recevoir("depart", reponse);
    envoyer_recevoir(final, reponse);
    

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
