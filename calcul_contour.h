#ifndef _CALCUL_CONTOUR_H_
#define _CALCUL_CONTOUR_H_
#include "types_macros.h"
#include "geom2d.h"
#include "image.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;

typedef struct Cellule_Liste_Point_{
    Point data;
    struct Cellule_Liste_Point_ *suiv;
} Cellule_Liste_Point;

typedef struct Liste_Point_{
    unsigned int taille;
    Cellule_Liste_Point *first;
    Cellule_Liste_Point *last;
} Liste_Point;

typedef struct Tableau_Point_{
    unsigned int taille;
    Point *tab;
} Tableau_Point;

void PbmToEps(char *nom_entree, char *nom_sortie);

#endif