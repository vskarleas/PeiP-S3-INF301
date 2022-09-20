# Calendar

## 13/9/2022 Premier seance

- Departition des roles
- Probleme
  - On veut decrypter des messages qui sont echnagé entre Alice et Bob. Ils sont utlise des lettres majuscules et miniscules.
- Discussion sur l'alorythme (du groupe)) suivante
  - Paer definiton on a une fonctionne qui lit un ligne
  - On a evidement besoin une deuxieme fonctinne qui lit les characteres de la ligne on utilise la logique suivante qui etait proposé penandt la premiere seance. On considere un 2-uplet (u,v)) pour chaque lettre lu par la fonctione specifique. u=lettre lu & v=nombre de decalage (pour l'instant on sait le decalage ~ *il sera etre modifié par une autre fonctionne*):
    - Si ce n'est pas un lettre (ex: point, espace, ! etc.) on ne touche pas, sinon
    - On verifie si c'est un lettre majuscule ou miniscule et on avance selon:
      - Si c'est un lettre majuscule, alors on reste entre les limites des indices de code d'ASCII pour les lettres najuscules
        - On applique la formule qu'on a trouvé:
          ```
          ((lettre-'A')+decalage)%26 + 'A'
          ```
      - Si c'est un lettre miniscule, alors on reste entre les limites des indices de code d'ASCII pour les lettres miniscules
        - On applique la formule qu'on a trouvé:
          ```
          ((lettre-'a')+decalage)%26 + 'a'
          ```
- Creation du programme qui prend un message et qui le decrypte selon un decalage donne pour l'alphabet. Le code est sur le fichier **algo1.c**.

## 15/9/2022 Premier seance de TP

* Exercise pereparatoire est veirfié avec des tests
* Travail sur le decodage du programme
* tutoriel est terminé
* TUTORIEL est terminé
* projectX est terminé
* But pour la prochaine seance est de trouver an algorythm qui crypte un message.
* Le message projectX de Bob et Alice est decrypté

  ```
  Chere Alice,

  Je crois que nous sommes sur ecoute, nous allons devoir changer notre methode 
  de chiffrement. J'ai une petite idee derriere la tete pour cela. Vu la 
  situation, nous ne pouvons etre trop prudents avant de passer au plan prevu.
  Je te laisse un prochain message dans l'exercice 'crypteMove', reste vigilante 
  et efface tes traces.

  Au fait, la solution pour reussir projetX est d'envoyer "veni vidi vici" au serveur. Tu 
  auras ainsi acces a l'exercice 'crypteMove'.

  Bien a toi,
  Bob.

  PS : Si tu as le temps, j'ai mis des codes secrets pour ce que tu sais dans 
  l'exercice challenge 'planB' mais ce n'est pas la priorite pour l'instant. En 
  cas de doute, retrouve-moi plutot rapidement sur crypteMove.
  ```

## 20/9/2022 Seance TD

* Discussion sur l'agorithme CrypteMove par l'APP1.
* Les indices de l'agorytme sont les suivantes (on a les pris via l'AppoLab):
  * `>>>recu >>> Durant l'encryption, nous allons modifier l'ordre des lettres du texte selon
    >>> recu >>> des regles bien etablies. Voici le principe :
    >>> recu >>> - soit TXT la sequence des caracteres a encrypter
    >>> recu >>> - soit ENC la sequence de sortie
    >>> recu >>>   (au debut, ENC est vide)
    >>> recu >>> - j'effectue ensuite la manipulation suivante:
    >>> recu >>>   * je prends C le premier caractere de TXT et le rajoute a la fin de ENC
    >>> recu >>>   * soit X le code ASCII de C modulo 8 (par exemple pour la lettre 'b', son
    >>> recu >>>     code ASCII est 98 donc X = 2)
    >>> recu >>>   * je prends les X premiers caracteres de TXT et les deplace a la fin de TXT
    >>> recu >>>     (s'il reste au moins X caracteres dans TXT)
    >>> recu >>>   * je recommence jusqu'a ce que TXT soit vide
    >>> recu >>> - a la fin, ENC contiendra le message encrypte.
    >>> recu >>>
    >>> recu >>> Je te donne un exemple sur le message suivant :
    >>> recu >>>       "Petit message court."`
    >>>
    >>
    >
* Le texte qu'on doit crypter est le suivante:
  * `>>>recu >>> Alice,
    >>> recu >>> J'espere que c'est bien toi. Je t'ai mis un message personnel dans l'aide de cet
    >>> recu >>> exercice. Une fois l'exercice demarre, il faut que tu m'envoies ce message
    >>> recu >>> d'aide au complet encrypte a l'aide de mon nouvel algorithme a base de
    >>> recu >>> deplacements de caracteres. Une fois que tu m'auras prouve ainsi que c'est bien
    >>> recu >>> toi, nous pourrons continuer notre conversation de maniere securisee.`
    >>>
    >>
    >
* L'algorithme est le suivante:
  * `#include <stdlib.h>
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
    char texte_originale[10000]="Petit message court.";
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
    }`
