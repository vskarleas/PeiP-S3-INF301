/*#ifdef _FILE_H_
#define _FILE_H_
*/
typedef struct
{
    cellule *tete;
    cellule *queue;
} file;

typedef struct
{
    char* val;
    struct cellule *suivant;
}cellule;

cellule *nvelle_cellule();



void ajouter_fin(file *f, char *s);

void supprimer_tete(file *f);

char *valeur_tete(file *f);

//#endif