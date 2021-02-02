// geom2d.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"geom2d.h"


double distance_point_segment(Point P, Vecteur V){
    Vecteur AP = vect_bipoint(V.x, P);
    lambda = produit_scalaire(AP, V)/produit_scalaire(V, V);