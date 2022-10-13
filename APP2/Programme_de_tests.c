#include "listes.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char texte[] = "AAGD321A+D6-";
    sequence_t * seq = malloc(sizeof(sequence_t));
    conversion(texte, seq);
    afficher(seq);
    empiler_int(seq, 'a');
    afficher(seq);
    printf("%c\n", depiler_int(seq));
    afficher(seq);
}