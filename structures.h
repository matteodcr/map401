#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include "types_macros.h"
#include "geom2d.h"
#include "image.h"

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

Cellule_Liste_Point* creer_element_liste_Point(Point v);

Liste_Point creer_liste_Point_vide();

void ajouter_element_liste_Point(Liste_Point *L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

#endif