struct noeud_s;

typedef struct noeud_s noeud;

typedef noeud* arbre;

struct noeud_s {
    int valeur;
    arbre gauche;
    arbre droit;
};