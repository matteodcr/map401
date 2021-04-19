#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include "types_macros.h"
#include "geom2d.h"
#include "image.h"

// Points

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

// Courbes de Bezier de degré 3

typedef struct Cellule_Liste_Bezier3_{
    Bezier3 data;
    struct Cellule_Liste_Bezier3_ *suiv;
} Cellule_Liste_Bezier3;

typedef struct Liste_Bezier3_{
    unsigned int taille;
    Cellule_Liste_Bezier3 *first;
    Cellule_Liste_Bezier3 *last;
} Liste_Bezier3;

typedef struct Tableau_Bezier3_{
    unsigned int taille;
    Bezier3 *tab;
} Tableau_Bezier3;

Cellule_Liste_Point* creer_element_liste_Point(Point v);

Liste_Point creer_liste_Point_vide();

void ajouter_element_liste_Point(Liste_Point *L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

Liste_Bezier3 creer_liste_Bezier3_vide();

void ajouter_element_liste_Bezier3(Liste_Bezier3 *L, Bezier3 e);

Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L);

Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2);

Tableau_Bezier3 sequence_bezier3_liste_vers_tableau(Liste_Bezier3 L);

#endif