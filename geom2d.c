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

Point sous_point(Point P1, Point P2){
    Point P = {P1.x - P2.x, P1.y - P2.y};
    return P;
}

Point mult_point(double n, Point P){
    Point R = {n*P.x, n*P.y};
    return R;
}

Vecteur vect_bipoint(Point A, Point B){
    Vecteur w = {B.x - A.x, B.y - A.y};
    return w;
}

Vecteur somme_vect(Vecteur u, Vecteur v){
    Vecteur w = {u.x + v.x, u.y + v.y};
    return w;
}

Vecteur produit_reel_vect(double a, Vecteur u){
    Vecteur w = {a*u.x, a*u.y};
    return w;
}

Vecteur produit_point_vect(Point P, Vecteur u){
    Vecteur w = {P.x*u.x, P.y*u.y};
    return w;
}

double produit_scalaire(Vecteur u, Vecteur v){
    return (u.x*v.x + u.y*v.y);
}

double norme_vect(Vecteur u){
    return sqrt(u.x*u.x + u.y*u.y);
}

double dist_points(Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

Segment init_segment(Point A, Point B){
    Segment S;
    S.A.x = A.x;
    S.B.x = B.x;
    S.A.y = A.y;
    S.B.y = B.y;
    return S;
}

double distance_point_segment(Point P, Segment S){
    if (S.A.x == S.B.x && S.A.y == S.B.y){
        return dist_points(P, S.A);
    }
    Vecteur AP = vect_bipoint(S.A, P);
    Vecteur AB = vect_bipoint(S.A, S.B);
    double lambda = produit_scalaire(AP, AB)/produit_scalaire(AB, AB);
    if (lambda < 0){
        return dist_points(S.A, P);
    }
    else if (lambda >=0 && lambda <= 1){
        Point Q = add_point(S.A, mult_point(lambda, sous_point(S.B, S.A)));
        return dist_points(Q, P);
    }
    else {
        return dist_points(S.B, P);
    }
}