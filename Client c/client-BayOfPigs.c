#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "algos_decodage_codage.h"

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    //char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    char texte[10000];
    envoyer_recevoir("login 12108112 TREHIN", reponse);

    //ouvre l'exercice BayOfPigs
    envoyer_recevoir("load BayOfPigs", reponse);

    //la variable reponse est une variable dynamique. Alors on utilise strcpy pour recupere le contenu et le traiter
    strcpy(texte, reponse);
    //decrypte la reponse en utilisant le l'agorithme de decryptage de cesar
    remplacer_texte_cesar(texte,21); //decalge connue: 5 ~ on a mis 21 comme notre fonction est construit a l'inverse

    //affiche le texte decrypte pour qu'on puisse le lire
    printf("%s\n", texte);

    //envoie la commande 'aide'
    envoyer_recevoir("aide", reponse);
    strcpy(texte, reponse);

    //decrypte la reponse en utilisant l'agorithme de decryptage de cesar
    remplacer_texte_cesar(texte,21); //decalge connue: 5 ~ on a mis 21 comme notre fonction est construit a l'inverse

    //affiche le texte decrypte pour qu'on puisse le lire
    printf("%s\n", texte);

    //envoie la commande 'start'. Apres le serveur attend notre reponse
    envoyer_recevoir("start", reponse);

    //initilisation du tableau pour stoquer la phrase crypte
    char texte_code[100000];
    
    /*
    char texte_decode[100000];
    strcpy(texte_code, reponse);
    decoder_texte_decrypteMove(texte_code, texte_decode);
    envoyer_recevoir(texte_decode, reponse);
    */

   //Phrase recupere par le texte decrypte
    strcpy(texte, "Patria o muerte");

    //cryptage de la phrase un utilisant l'algorithme crypteMove
    coder_texte_crypteMove(texte, texte_code);

    //envoyer la phrase crypte
    envoyer_recevoir(texte_code, reponse);

    //initilisation du tableau pour stocker le message decrypte 
    char texte_decode[100000];
    strcpy(texte_code, reponse);

    //decrypte la reponse en utilisant l'algorithme de decryptage de crypteMove
    decoder_texte_decrypteMove(texte_code, texte_decode);

    //envoyer la reponse recopure decode 
    envoyer_recevoir(texte_decode, reponse);

    printf ("Réponse du serveur: %s", reponse);


    //Connection terminee
    printf ("Fin de la connection au serveur\n");
    return 0;
}
