#include <stdio.h>
#include <string.h>


void decalage(char* texte, int n){
    int j;
    for (j = n; texte[j] != '\0'; j++)
    {
        texte[j - n] = texte[j];
    }
    texte [j-n]='\0';
}

void copier_bloc_de_lettres(char* texte, char* texte_tmp, int n){
    for (int k = 0; k < n;k++)
    {
        texte_tmp[k] = texte[k];
    }
    texte_tmp [n] = '\0';
}

void coder_texte(char* texte){
    char lettre;
    char texte_code[100000];
    int index_texte_code = 0;
    while (texte[0] != '\0')
    {
        lettre = texte[0];
        texte_code[index_texte_code] =lettre;
        int x = lettre % 8;
        decalage(texte, 1);
        char texte_a_bouger[9];
        if (strlen(texte) >= x)
        {
            copier_bloc_de_lettres(texte, texte_a_bouger, x);
            decalage(texte, x);
            strcat(texte, texte_a_bouger);
        }
        index_texte_code++;
    }
    printf("%s", texte_code);
}

int main() {
    char texte[] = "Petit message court.";
    char texte_tmp[100];
    copier_bloc_de_lettres(texte, texte_tmp, 2);
    coder_texte(texte);
    int a;
}