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
    printf("Point A: (%f, %f)\n", A.x, A.y);
    printf("Point B: (%f, %f)\n", B.x, B.y);
    printf("Point C: (%f, %f)\n", C.x, C.y);
    printf("Point D: (%f, %f)\n", D.x, D.y);
    printf("=======\n");

    //Calculs

    
    printf("Addition des points A et B : (%f, %f)\n", add_point(A, B).x, add_point(A, B).y);
    printf("Distance entre A et B : %d\n", dist_points(A, B));
    printf("======\n");

    Vecteur AB = vect_bipoint(A, B);
    Vecteur CD = vect_bipoint(C, D);
    printf("Vecteur AB : (%f, %f)\n", AB.x, AB.y);
    printf("Vecteur CD : (%f, %f)\n", CD.x, CD.y);
    printf("Somme des vecteurs AB et CD : (%f, %f)\n", somme_vect(AB, CD).x, somme_vect(AB, CD).y);
    printf("Produit de AB par 3 : (%f, %f)\n", produit_reel_vect(5, AB).x, produit_reel_vect(5, AB).y);
    printf("Produit de AB par C : (%f, %f)\n", produit_point_vect(C, AB).x, produit_point_vect(C, AB).y);
    printf("Produit scalaire de AB et CD : %d\n", produit_scalaire(AB, CD));
    printf("Norme du vecteur AB : %d\n", norme_vect(AB));
    
    
    return 0;
}