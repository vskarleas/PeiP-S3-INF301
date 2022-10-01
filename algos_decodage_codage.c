#include <stdio.h>
#include <string.h>
#include "tableaux.h"

char remplacer_lettre(char lettre, int decalage)
{
    if (lettre >= 'A' && lettre <= 'Z')
    {
        return (((lettre - 'A') + decalage) % 26 + 'A'); //Il permet de faire le decalage pour les lettres majuscules
    }
    else if (lettre >= 'a' && lettre <= 'z')
    {
        return (((lettre - 'a') + decalage) % 26 + 'a'); //Il permet de faire le decalage pour les lettres miniscules
    }
    else
    {
        return lettre; //Si ce n'est pas un lettre, on retourne le character
    }
}

void remplacer_texte_cesar(char *texte, int decalage) //Algorithme de decryptage de cesar
{
    char lettre;
    for (int i = 0; texte[i] != '\0'; i++)
    {
        lettre = texte[i]; //On recupere chaque lettre par le chaine des characters
        char lettre_decode = remplacer_lettre(lettre, decalage); //On decode le character en utilisant la logique d'alogirithme pour le decalage de cesar
        texte[i] = lettre_decode; //Le character decode replace le character code
    }
}

int trouver_decalage(char *texte)
{
    for (int i = 0; i <= 25; i++)
    {
        if (remplacer_lettre(texte[0], i) == 'C') //Les messages qui demande un decryptace de Ceasar commence toujours par le mot "Cher". 
                                                  //On trouver la difference entre le character lu et le character "C" pour qu'il peut etre utilise par l'aglgo 'remplacer_texte_cesar' 
        {
            return i;
        }
    }
    return 0;
}

void remplacer_texte_cesar_automatique(char *texte) //Fonction pour automatiser le decryptage des quelques messages sur Appolab
{
    int decalage = trouver_decalage(texte); //trouve le decalage automatiquement selon 'trouver_decalage'
    remplacer_texte_cesar(texte, decalage); //il execute l'algo 'remplacer_texte_cesar'
}

void decalage_a_gauche(char *texte, int n)
{
    int j;
    for (j = n; texte[j] != '\0'; j++)
    {
        texte[j - n] = texte[j]; //Le premier character avant le decalage est suprime apres le decalage a gauche
    }
    texte[j - n] = '\0'; //On ajoute le nouvele fin du chaine de character
}

void decalage_a_droite(char *texte, int longueur_texte, int n)
{
    int j;
    for (j = longueur_texte - n; j >= 0; j--) //Le longueur de la sequence augmente par 1.
    {
        texte[j + n] = texte[j];
    }
}

void copier_bloc_de_lettres(char *texte, char *texte_tmp, int debut, int fin)
{
    for (int k = debut; k <= fin; k++)
    {
        texte_tmp[k - debut] = texte[k];
    }
    texte_tmp[fin + 1 - debut] = '\0';
}

void coder_texte_crypteMove(char *texte, char *texte_code)
{
    char lettre;
    int index_texte_code = 0;
    while (texte[0] != '\0')
    {
        lettre = texte[0]; //(*1)
        texte_code[index_texte_code] = lettre;
        int valeur_decalage = lettre % 8;
        decalage_a_gauche(texte, 1); //Grace au decalage a gauche, on peut utiliser toujours la meme idice [0] (voir (*1)) pour lire le lettre qu'on doit coder
        char texte_a_bouger[9];
        int longueur_texte = strlen(texte); //on doit verifier qu'il y a un nombre suffisant des lettres pour faire le decalage
        if (longueur_texte >= valeur_decalage)
        {
            copier_bloc_de_lettres(texte, texte_a_bouger, 0, valeur_decalage - 1);
            decalage_a_gauche(texte, valeur_decalage);
            strcat(texte, texte_a_bouger);
        }
        index_texte_code++;
    }
}

void ecrire_bloc_de_lettres_au_debut(char *texte_source, char *texte_destination, int taille_texte_source)
{
    for (int i = 0; i < taille_texte_source; i++)
    {
        texte_destination[i] = texte_source[i];
    }
}
/*
void ajouter_au_debut(texte, longueur_texte, lettre_a_ajouter){

}
*/
void decoder_texte_decrypteMove(char *texte_code, char *texte_decode)
/*
 * Fonction:
 *  decoder_texte_decrypteMove
 *
 * Description:
 *  Décrypte un texte crypté à l'aide de l'agorithme crypteMove
 *
 * Arguments
 *  texte_code: le texte que l'on cherche a décoder
 *  texte_decode: le texte dans lequel on veut stoquer le texte decodé
 *
 * return: vide
 */
{
    char lettre;
    int longueur_texte_code = strlen(texte_code) - 1;
    int longueur_texte_decode = 0; // initialement le texte decode est vide et sera rempli au fur et a mesure
    for (int index_texte_code = longueur_texte_code; index_texte_code >= 0; index_texte_code--)
    {
        lettre = texte_code[index_texte_code];
        int valeur_decalage = lettre % 8;
        if (longueur_texte_decode > valeur_decalage) // On vérifie si le texte est suffisamment long pour effectuer le Décalage
        {
            char texte_a_bouger[9];
            copier_bloc_de_lettres(texte_decode, texte_a_bouger, longueur_texte_decode - valeur_decalage, longueur_texte_decode);
            decalage_a_droite(texte_decode, longueur_texte_decode, valeur_decalage);
            ecrire_bloc_de_lettres_au_debut(texte_a_bouger, texte_decode, valeur_decalage);
        }
        if (longueur_texte_decode > 0)
        {
            decalage_a_droite(texte_decode, longueur_texte_decode, 1);
        }
        texte_decode[0] = lettre;
        longueur_texte_decode++;
    }
}

<<<<<<< Updated upstream
void ajouter_debut(struct liste_chainee texte_decode, int valeur_decalage)
{
    struct cellule *precedent;
    struct cellule *actuel = texte_decode.queue;
    struct cellule *nvlle_queue;
    struct cellule *nvlle_tete;
    struct cellule *ancienne_queue = texte_decode.queue;
    struct cellule *ancienne_tete = texte_decode.tete;
    for (int i = 0; i < valeur_decalage - 1; i++)
    {
        precedent = actuel->precedent;
    }
    nvlle_tete = precedent;
    nvlle_queue = nvlle_tete->precedent;
    ancienne_queue->suivant = ancienne_tete;
    ancienne_tete->precedent = ancienne_queue;
    nvlle_tete->precedent = NULL;
    nvlle_queue->suivant = NULL;
    texte_decode.tete = nvlle_tete;
    texte_decode.queue = nvlle_queue;
}

void ajouter_lettre_au_debut(char lettre, struct liste_chainee texte_decode)
{
    struct cellule ancienne_tete;
    ancienne_tete.precedent = texte_decode.tete->precedent;
    ancienne_tete.suivant = texte_decode.tete->suivant;
    ancienne_tete.valeur = texte_decode.tete->valeur;
    struct cellule nvlle_tete;

    nvlle_tete.valeur = lettre;
    nvlle_tete.suivant = &ancienne_tete;
    ancienne_tete.precedent = &nvlle_tete;
    texte_decode.tete = &nvlle_tete;
}

void decoder_texte_decrypteMove_rapide(char *texte_code, char *texte_decode)
/*
 * Fonction:
 *  decoder_texte_decrypteMove
 *
 * Description:
 *  Décrypte un texte crypté à l'aide de l'agorithme crypteMove
 *
 * Arguments
 *  texte_code: le texte que l'on cherche a décoder
 *  texte_decode: le texte dans lequel on veut stoquer le texte decodé
 *
 * return: vide
 */
{
    char lettre;
    struct liste_chainee texte_decode_chainee;
    texte_decode_chainee.tete = NULL;
    texte_decode_chainee.queue = NULL;
    texte_decode_chainee.longueur = 0;
    int longueur_texte_code = strlen(texte_code) - 1;
    int longueur_texte_decode_chainee = 0; // initialement le texte decode est vide et sera rempli au fur et a mesure
    for (int index_texte_code = longueur_texte_code; index_texte_code >= 0; index_texte_code--)
    {
        lettre = texte_code[index_texte_code];
        int valeur_decalage = lettre % 8;
        if (longueur_texte_decode_chainee > valeur_decalage) // On vérifie si le texte est suffisamment long pour effectuer le Décalage
        {
            ajouter_debut(texte_decode_chainee, valeur_decalage);
        }
        ajouter_lettre_au_debut(lettre, texte_decode_chainee);
        longueur_texte_decode_chainee++;
    }

    struct cellule *cellule_actuelle = NULL;
    for (int i = 0; cellule_actuelle != texte_decode_chainee.queue; i++)
    {
        texte_decode[i] = cellule_actuelle->valeur;
        cellule_actuelle = cellule_actuelle->suivant;
    }
}

int dans(char lettre, char *seq)
=======
int dans(char lettre, char *seq) 
>>>>>>> Stashed changes
{
    for (int i = 0; seq[i] != '\0'; i++)
    {
        if (seq[i] == lettre) //verfier si un element existe dans une sequence
        {
            return 1; //on utilise le resultat pour performer des actions
        }
    }
    return 0; //reponse si n'est pas dans la sequence
}

void ajouter_lettre(char lettre, char *seq, int *lg_seq) //il ajoute une character-lettre a la fin de la sequence donnee en argument
{
    seq[*lg_seq] = lettre;
    *lg_seq = *lg_seq + 1; //la partie memoire doit etre assez grand pour qu'on peut faire ça. À l'inisialisation des tablaux aux programmes principales on a donne une memoire assez grande
}

int indice_lettre(char lettre, char *seq) //il trouve l'indice d'un lettre sur un sequence par rapport son occurencen dans cette sequence donnee en argument
{
    for (int i = 0; seq[i] != '\0'; i++)
    {
        if (lettre == seq[i])
        {
            return i; //renvoi l'indice
        }
    }
    return -1;
}

char dernier_char(char *seq, int lg_seq)
{
    return seq[lg_seq - 1]; //renvoie le dernier character d'une sequence
}

char lettre_precedente(char lettre, char *seq)
{
    return seq[indice_lettre(lettre, seq) - 1]; //renvoie le character avant un lettre sur une sequence. Cette fonctione est bien utilisé quand on n'est pas en premier lettre de la sequence sur nos algos
}

void deplacer_fin(char lettre, char *seq, int *lg_seq)
{
    int indice = indice_lettre(lettre, seq);
    for (int i = indice; seq[i + 1] != '\0'; i++)
    {
        seq[i] = seq[i + 1];
    }
    seq[*lg_seq - 1] = lettre;
}

char trouver_lettre_precedente(char lettre, char *seq, int lg_seq)
{
    if (indice_lettre(lettre, seq) == 0)
    {
        return dernier_char(seq, lg_seq);
    }
    else
    {
        return lettre_precedente(lettre, seq);
    }
}

void crypter_txt_crypteSeq(char *txt, char *txt_crypte) //Algorithme de cryptage crypteSeq
{

    char lettre;
    char lettre_cryptee;
    char seq[1000] = ""; // lettres déjà trouvée
    int lg_seq = 0;      // longueur de seq

    for (int i = 0; txt[i] != '\0'; i++)
    {
        lettre = txt[i];
        int lg_txt_crypte = i;
        if (!dans(lettre, seq)) //Si n'exitse pas dans la sequence on ajoute le lettre lu
        {
            ajouter_lettre(lettre, seq, &lg_seq);
            ajouter_lettre(lettre, txt_crypte, &lg_txt_crypte);
        }
        else
        {
            lettre_cryptee = trouver_lettre_precedente(lettre, seq, lg_seq);
            ajouter_lettre(lettre_cryptee, txt_crypte, &lg_txt_crypte);
            deplacer_fin(lettre, seq, &lg_seq); //on modifie la sequence comme il est demande pour faire le bon cryptage
        }
    }
}

int indice_lettre_doublesaut(char lettre, char *seq) //Utilise par l'alorithme LostCause
{
    for (int i = 0; seq[i] != '\0'; i = i + 2)
    {
        if (lettre == seq[i])
        {
            return i;
        }
    }
    return -1;
}

<<<<<<< Updated upstream
char trouver_lettre_assoc(char lettre, char *seq_assoc)
=======
char trouver_lettre_assoc(char lettre, char* seq_assoc) //Utilise par l'alorithme LostCause
>>>>>>> Stashed changes
{
    return seq_assoc[indice_lettre_doublesaut(lettre, seq_assoc) + 1];
}

void modifier_assoc(char lettre, char *seq, int lg_seq, char *seq_assoc) //Utilise par l'alorithme LostCause
{
    char lettre_pre = trouver_lettre_precedente(lettre, seq, lg_seq);
    char lettre_associee_a_lettre = trouver_lettre_assoc(lettre, seq_assoc);
    char lettre_associee_a_lettre_pre = trouver_lettre_assoc(lettre_pre, seq_assoc);
    seq_assoc[indice_lettre_doublesaut(lettre, seq_assoc) + 1] = lettre_associee_a_lettre_pre;
    seq_assoc[indice_lettre_doublesaut(lettre_pre, seq_assoc) + 1] = lettre_associee_a_lettre;
}

void crypter_txt_crypteAssoc(char *txt, char *txt_crypte) //Algorithme de l'exercise LostCause PAS COMPLETE
{

    char lettre;
    char lettre_cryptee;
    char seq[1000] = "";       // lettres déjà trouvée
    char seq_assoc[1000] = ""; // lettres déjà trouvée
    int lg_seq_assoc = 0;

    int lg_seq = 0; // longueur de seq

    int i;
    for (i = 0; txt[i] != '\0'; i++)
    {
        lettre = txt[i];
        int lg_txt_crypte = i;
        if (!dans(lettre, seq))
        {
            ajouter_lettre(lettre, seq, &lg_seq);
            ajouter_lettre(lettre, seq_assoc, &lg_seq_assoc);
            ajouter_lettre(lettre, seq_assoc, &lg_seq_assoc);
            ajouter_lettre(lettre, txt_crypte, &lg_txt_crypte);
        }
        else
        {
            modifier_assoc(lettre, seq, lg_seq, seq_assoc);

            lettre_cryptee = trouver_lettre_assoc(lettre, seq_assoc);
            ajouter_lettre(lettre_cryptee, txt_crypte, &lg_txt_crypte);
            deplacer_fin(lettre, seq, &lg_seq);
        }
    }
    txt_crypte[i + 1] = '\0';
}

void ajouter_lettre_debut(char lettre, char *txt, int *lg_txt)
{
    decalage_a_droite(txt, *lg_txt, 1); //Un decalage a droite est necesaire pour ajouter le nouveau caracter au debut
    txt[0] = lettre;
    *lg_txt = *lg_txt + 1; //On change aussie le longueure du texte comme on l'utilise sur des boucles
}

int trouver_seq(char *txt_crypte, int lg_txt_crypte, char *seq)
{
    seq[0] = '\0';
    int lg_seq = 0;
    for (int i = lg_txt_crypte - 1; i >= 0; i--)
    {
        if (!dans(txt_crypte[i], seq))
        {
            ajouter_lettre_debut(txt_crypte[i], seq, &lg_seq);
        }
    }
    return lg_seq;
}

void retirer_derniere_lettre(char *txt, int *lg_txt)
{
    txt[*lg_txt] = '\0'; //supprime le dernier lettre en replacant avec le fin \0
    *lg_txt = *lg_txt - 1; //On a besoin de diminuer par le longueur du texte  
}

char lettre_suivante(char lettre, char *seq)
{
    return seq[indice_lettre(lettre, seq) + 1]; //Retourne le 
}

char premier_char(char *seq)
{
    return seq[0];
}

void decrypter_txt_crypteSeq(char *txt_crypte, char *txt_decrypte) //Algorithme de decryptage de crypteSeq
{

    char lettre_crypte;
    char lettre_decrypte;
    char seq[1000] = ""; // lettres déjà trouvée
    int lg_seq = 0;      // longueur de seq
    int i;
    for (i = 0; txt_crypte[i] != '\0'; i++)
    {
        lettre_crypte = txt_crypte[i];
        int lg_txt_decrypte = i;
        if (!dans(lettre_crypte, seq))
        {
            ajouter_lettre(lettre_crypte, seq, &lg_seq); //On construit une sequence pour les lettres lu (seule occurence de chaque lettre sur la sequence)
            ajouter_lettre(lettre_crypte, txt_decrypte, &lg_txt_decrypte);
        }
        else
        {
            if (indice_lettre(lettre_crypte, seq) == lg_seq - 1)
            {
                lettre_decrypte = premier_char(seq); //Si c'est dernier charactere, on le met au debut
            }
            else
            {
                lettre_decrypte = lettre_suivante(lettre_crypte, seq); //Sinon on le met suivante
            }
            ajouter_lettre(lettre_decrypte, txt_decrypte, &lg_txt_decrypte);
            deplacer_fin(lettre_decrypte, seq, &lg_seq);
        }
    }
    txt_decrypte[i + 1] = '\0';
}

void recuperer_mdp(char *txt, char *mdp) 
{
    int nb_guillemets_simple = 0;
    for (int i = 0; txt[i] != '\0'; i++) 
    {
        if (txt[i] == '\'')
        {
            nb_guillemets_simple++;
        }
<<<<<<< Updated upstream
        if (nb_guillemets_simple == 3)
=======
        if (nb_guillemets_simple==3) //Nous avons compté 3 occurences de '. C'est pourquoi on a ici egale a trois
>>>>>>> Stashed changes
        {
            for (int j = 0; txt[j + i + 1] != '\''; j++)
            {
                mdp[j] = txt[j + i + 1];
            }
            break;
        }
    }
}