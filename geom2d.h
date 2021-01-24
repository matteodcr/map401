#ifndef _GEOM2D_H_
#define _GEOM2D_H_

#include "types_macros.h"
#include <math.h>

typedef struct Vecteur_{
    double x,y;
} Vecteur;

typedef struct Point_ {
    double x,y;
} Point;

/* cree le point de coordonées (x,y) */ 
Point set_point(double x, double y);

/* somme P1 + P2 */
Point add_point(Point P1, Point P2);

/* Vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B);

Vecteur somme_vect(Vecteur u, Vecteur v);

Vecteur produit_reel_vect(int a, Vecteur u);

Vecteur produit_point_vect(Point P, Vecteur u);;

int produit_scalaire(Vecteur u, Vecteur v);

double norme_vect(Vecteur u);

double dist_points(Point A, Point B);


#endif 