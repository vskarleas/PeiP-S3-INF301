struct cellule
{
    struct cellule *precedent;
    char valeur;
    struct cellule *suivant;
} cel;

struct liste_chainee
{
    struct cellule *tete;
    int longueur;
    struct cellule *queue;
} liste;
