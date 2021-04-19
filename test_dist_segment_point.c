#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom2d.h"

int main(int argc, char *argv[]) {
    if (argc != 7){
        printf("Usage : ./test_dist_segment_point <x, y Point A> <x, y Point B> <x, y Point C>\n");
        exit(1);
    }
    
    //Création de 3 points
    Point A = set_point(atoi(argv[1]), atoi(argv[2]));
    Point B = set_point(atoi(argv[3]), atoi(argv[4]));
    Point C = set_point(atoi(argv[5]), atoi(argv[6]));
    
    printf("=======\n");
    printf("Point A: (%.0f, %.0f)\n", A.x, A.y);
    printf("Point B: (%.0f, %.0f)\n", B.x, B.y);
    printf("Point C: (%.0f, %.0f)\n", C.x, C.y);
    printf("=======\n");

    //Calcul et affichage de la distance segment-point

    Segment segAB = init_segment(A, B);
    printf("Distance entre le segment AB et le point C : %.4f\n", distance_point_segment(C, segAB));
    return 0;
}