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

/* Création d'une cellule de liste avec l'élément n */
int trouver_pixel_depart(Image I, Point *P);

Cellule_Liste_Point* creer_element_liste_Point(Point v);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

Liste_Point creer_liste_Point_vide();

/* ajout de l'element e à la fin de L et renvoie un pointeur vers la liste modifiée */
void ajouter_element_liste_Point(Liste_Point *L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Orientation tourner_gauche(Orientation O);

Orientation tourner_droite(Orientation O);

Orientation nouvelle_orientation(Image I, Point P, Orientation O);

void avance(Point *P, Orientation O);

void ecrire_contour(Liste_Point L);

void initialiser_fichier();

void ecrire_contour_fichier(Liste_Point L);

int trouver_pixel_depart(Image I, Point *P);

void contour_multiple(Image I, char *nom_f);

/* fait le contour a partir du point de coordonée(x, y) */
Liste_Point contour(Image I, Image *Im, int x, int y, int *i);

#endif