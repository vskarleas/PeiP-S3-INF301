#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
int main() {
    char texte_originale[50000]="Petit message court."; //On doit trouver une maniere pour l'appliquer sur le texte d'aide qui normalment doit le metttre dans un fichier, mais je ne suis pas sure.
    char texte_code[10000];
    premierLettre(texte_originale, texte_code);
    remove_lettre(texte_originale);
    const size_t len = strlen(texte_originale);
    int dec;
    char lte;
    while(texte_originale[0]!='\0'){
        lte=texte_originale[0];
        dec=decalage(texte_originale);
        if (dec<strlen(texte_originale)){
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

    
    printf("%s\n", texte_code);
}