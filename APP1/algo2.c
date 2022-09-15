#include<stdio.h>
#include <string.h>

char remplacer_lettre(char lettre, int decalage){
    return (lettre + decalage);
}

void remplacer_texte(char* nom_fichier_code){
    FILE* fichier_code = fopen(nom_fichier_code,"r");
    char nom_fichier_decode[512];
    strcpy(nom_fichier_decode,nom_fichier_code);
    strcat(nom_fichier_decode, "_encode");
    FILE *fichier_decode = fopen(nom_fichier_decode, "w");
    char lettre;
    fscanf(fichier_code, "%c", &lettre);
    while(!feof(fichier_code)){
        if (lettre == 'a'||lettre == 'e'||lettre == 'i'||lettre == 'o'||lettre == 'u') {
            char lettre_encode = remplacer_lettre(lettre, 3);
            fprintf(fichier_decode, "%c", lettre_encode);
            fscanf(fichier_code, "%c", &lettre);
        }
        else {
            fprintf(fichier_decode, "%c", lettre);
        }
    }
    fclose(fichier_code);
    fclose(fichier_decode);
}


int main() {
    remplacer_texte("texte2.txt");
}
