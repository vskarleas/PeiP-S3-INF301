#include <stdio.h>
#include <string.h>
char remplacer_lettre(char lettre, int decalage){
    if(lettre>='A' && lettre<='Z'){
        return (((lettre-'A')+decalage)%26+'A');
    }else if(lettre>='a' && lettre<='z'){
        return (((lettre - 'a') + decalage) % 26 + 'a');
    }else{
        return lettre;
    }
}

void remplacer_texte(char* nom_fichier_code, int decalage){
    FILE* fichier_code = fopen(nom_fichier_code,"r");
    char nom_fichier_decode[512];
    strcpy(nom_fichier_decode,nom_fichier_code);
    strcat(nom_fichier_decode, "_decode");
    FILE *fichier_decode = fopen(nom_fichier_decode, "w");
    char lettre;
    fscanf(fichier_code, "%c", &lettre);
    while(!feof(fichier_code)){
        char lettre_decode = remplacer_lettre(lettre, decalage);
        fprintf(fichier_decode, "%c", lettre_decode);
        fscanf(fichier_code, "%c", &lettre);
    }
    fclose(fichier_code);
    fclose(fichier_decode);
}

int main() {
    remplacer_texte("texte.txt", 21);
}