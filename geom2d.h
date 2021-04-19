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

typedef struct Segment_{
    Point A,B;
} Segment;

typedef struct Bezier2_{
    Point C0;
    Point C1;
    Point C2;
} Bezier2;

typedef struct Bezier3_{
    Point C0;
    Point C1;
    Point C2;
    Point C3;
} Bezier3;

/* cree le point de coordonées (x,y) */ 
Point set_point(double x, double y);

/* somme P1 + P2 */
Point add_point(Point P1, Point P2);

Point sous_point(Point P1, Point P2);

Point mult_point(double n, Point P);

/* Vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B);

Vecteur somme_vect(Vecteur u, Vecteur v);

Vecteur produit_reel_vect(double a, Vecteur u);

Vecteur produit_point_vect(Point P, Vecteur u);;

double produit_scalaire(Vecteur u, Vecteur v);

double norme_vect(Vecteur u);

double dist_points(Point A, Point B);

double distance_point_segment(Point P, Segment V);

Segment init_segment(Point A, Point B);

double distance_point_bezier2(Point P, Bezier2 B, float t);

double distance_point_bezier3(Point P, Bezier3 B, float t);

Bezier3 Bezier2ToBezier3(Bezier2 B2);

Point point_bezier2(Bezier2 B, double t);

Point point_bezier3(Bezier3 B, double t);

#endif 