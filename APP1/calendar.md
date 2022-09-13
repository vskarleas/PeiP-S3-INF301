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
    - On applique la formule suivante
