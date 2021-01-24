#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types_macros.h"
#include "geom2d.h"

int main(int argc, char *argv[]) {
    if (argc != 9){
        printf("Usage : ./test_image <x, y Point A> <x, y Point B> <x, y Point C> <x, y Point D>");
    }
    
    //Création de 4 points
    Point A = set_point(atoi(argv[1]), atoi(argv[2]));
    Point B = set_point(atoi(argv[3]), atoi(argv[4]));
    Point C = set_point(atoi(argv[5]), atoi(argv[6]));
    Point D = set_point(atoi(argv[7]), atoi(argv[8]));
    
    printf("=======\n");
    printf("Point A: (%.0f, %.0f)\n", A.x, A.y);
    printf("Point B: (%.0f, %.0f)\n", B.x, B.y);
    printf("Point C: (%.0f, %.0f)\n", C.x, C.y);
    printf("Point D: (%.0f, %.0f)\n", D.x, D.y);
    printf("=======\n");

    //Calculs

    
    printf("Addition des points A et B : (%.0f, %.0f)\n", add_point(A, B).x, add_point(A, B).y);
    printf("Distance entre A et B : %f\n", dist_points(A, B));
    printf("======\n");

    Vecteur AB = vect_bipoint(A, B);
    Vecteur CD = vect_bipoint(C, D);
    printf("Vecteur AB : (%.0f, %.0f)\n", AB.x, AB.y);
    printf("Vecteur CD : (%.0f, %.0f)\n", CD.x, CD.y);
    printf("Somme des vecteurs AB et CD : (%.0f, %.0f)\n", somme_vect(AB, CD).x, somme_vect(AB, CD).y);
    printf("Produit de AB par 3 : (%.0f, %.0f)\n", produit_reel_vect(3, AB).x, produit_reel_vect(3, AB).y);
    printf("Produit de AB par C : (%.0f, %.0f)\n", produit_point_vect(C, AB).x, produit_point_vect(C, AB).y);
    printf("Produit scalaire de AB et CD : %d\n", produit_scalaire(AB, CD));
    printf("Norme du vecteur AB : %f\n", norme_vect(AB));
    
    
    return 0;
}