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
  * ```
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
