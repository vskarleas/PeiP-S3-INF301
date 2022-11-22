#include "arbres.h"
#include <stdbool.h>
#include <stdio.h>

//Examining if an element is part of the binary tree
bool present(arbre a, int n) {
    //As long as the binary tree isn't empty
    if (a != NULL)
    {
        //if node equals to searchign element return true
        if (n == a->valeur)
        {
            return true;
        }
        //Otherwise continue searching on both sides of every children
        else 
        {
            if (present(a->gauche, n))
            {
                return true;
            }
            else if (present(a->droit, n))
            {
                return true;
            }
            
        }
    }
    //If it faisl to return true any of the above searching mechanisms,
    //this means that we have searched the whole binary tree
    //So, we are returng false if it's not found
    return false;
}

/* Given a non-empty binary search 
   tree, return the node
   with minimum key value found in
   that tree. */
arbre valeurNode(arbre a)
{
    noeud *current = (a);
    
    // loop down to find the leftmost leaf
    while (current && current->gauche != NULL)
    {
        current = current->gauche;
    }
    return current;
}

arbre deleteNoeud(arbre a, int n)
{
    //not the deletion case
    if ((a) == NULL)
    {
        return (a);
    }
    
    //case for element smaller than node (searching on left side of the node)
    if (n < (a)->valeur)
    {
        (a)->gauche = deleteNoeud((a)->gauche, n);
    }
    //case for element bigger than node (searching on right side of the node)
    else if (n > (a)->valeur)
    {
        (a)->droit = deleteNoeud((a)->droit, n);
    }
    //verification of deletion
    else
    {
    //Treating the case of a node with only one child left or right
        //Examinig for the left side
        if ((a)->gauche == NULL)
        {
            noeud *tmp = (a)->droit;
            free((a));
            return tmp;
        }
        //Examinig for the right side
        else if ((a)->droit == NULL)
        {
            noeud *tmp = (a)->gauche;
            free((a));
            return tmp; 
        }
        //If it's not the case, we have a node with two children:
        //We are taking the inorder succesor
        noeud *tmp = valeurNode((a)->droit);
        
        //coppying inorder succesor to node where we stopped    
        (a)->valeur = tmp->valeur;
        
        //Deletion of the inorder sucessor (The succesor functions works on the left side)
        (a)->droit = deleteNoeud((a)->droit, tmp->valeur);
    }
    //sending the final binary tree as a response
    return (a);
}
 
bool supprimer_abr(arbre *a, int n) { //false valeur absente
    //If it's not present the element, we won't execute the deletion algorithm
    if (!(present((*a), n))){
        return false;
    }
    //If the element exists,
    //we execute the deltion algorith
    else 
    {
    //Saving the new-constructed binary tree back to memory
    (*a) = deleteNoeud((*a),n);
    //return true to indicate that a deletion has been done to the binary tree 
    //given in arguments
    return true;
    }
}