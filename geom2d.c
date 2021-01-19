#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"geom2d.h"

Point set_point(double x, double y){
    Point P;
    P.x = x;
    P.y = y;
    
    return P;
}

Point add_point(Point P1, Point P2){
    Point P = {P1.x + P2.x, P1.y + P2.y};
    return P;
}
Vecteur vect_bipoint(Point A, Point B){
    Vecteur w = {B.x - A.x, B.y - A.y};
    return w;
}

Vecteur somme_vect(Vecteur u, Vecteur v){
    Vecteur w = {u.x + v.x, u.y + v.y};
    return w;
}

Vecteur produit_reel_vect(int a, Vecteur u){
    Vecteur w = {a*u.x, a*u.y};
    return w;
}

Vecteur produit_point_vect(Point P, Vecteur u){
    Vecteur w = {P.x*u.x, P.y*u.y};
    return w;
}

int produit_scalaire(Vecteur u, Vecteur v){
    return (u.x*v.x + u.y*v.y);
}

int norme_vect(Vecteur u){
    return sqrt(u.x*u.x + u.y*u.y);
}

int dist_points(Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}