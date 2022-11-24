#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
    L->tete = "";
}

void liberer_liste(liste_t* L) {
   printf ("<<<<< À faire: fonction liberer_liste fichier " __FILE__ "\n >>>>>");
    /* a completer */
}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
    string k = L->tete;
    L->tete = c;
    L->tete->suivant = k;
   printf ("<<<<< À faire: fonction ajouter_tete fichier " __FILE__ " >>>>>\n");
    /* a completer */
        return 1;
}

