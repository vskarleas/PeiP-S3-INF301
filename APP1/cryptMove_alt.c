#include <stdio.h>
#include <string.h>


void coder_texte(char* nom_fichier_a_code){
    FILE* fichier_a_code = fopen(nom_fichier_a_code,"r");
    char nom_fichier_code[512];
    strcpy(nom_fichier_code,nom_fichier_a_code);
    strcat(nom_fichier_code, "_code");
    FILE *fichier_code = fopen(nom_fichier_code, "w");
    char lettre;
    char texte[100000];
    char texte_code[100000];
    int i=0;
    while(!feof(fichier_a_code)){
        fscanf(fichier_a_code, "%c", &texte[i]);
        i++;
    }
    texte[i]='\0';

    int index_texte_code = 0;
    while (texte[0] != '\0')
    {
        lettre = texte[0];
        texte_code[index_texte_code] =lettre;
        int x = lettre % 8;
        int j;
        for (j = 1; texte[j] != '\0'; j++)
        {
            texte[j - 1] = texte[j];
        }
        texte [j-1]='\0';
        char texte_a_bouger[9];
        if (strlen(texte) >= x)
        {
            for (int k = 0; k < x;k++)
            {
                texte_a_bouger[k] = texte[k];
            }
            int u;
            for (u = x; texte[u] != '\0'; u++)
            {
                texte[u - x] = texte[u];
            }
            texte [u-x]='\0';
            strcat(texte, texte_a_bouger);
        }
        index_texte_code++;
    }
    fprintf(fichier_code, "%s", texte);
    fclose(fichier_a_code);
    fclose(fichier_code);
}

int main() {
    remplacer_texte("texte.txt");
}