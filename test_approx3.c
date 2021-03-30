#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bezier.h"
#include "structures.h"

#include"eps.h"

int main(int argc, char *argv[]) {
    if (argc != 11 && argc != 9 && argc != 7 && argc != 3){
        printf("Usage : ./test_approx3 <j1> <j2> <P0x> <P0y> <P1x> <P1y> \n(possibilité de rajouter des points en augmentant l'écart j1 j2)\n");
        return 0;
    }

    int j1 = atoi(argv[1]);
    int j2 = atoi(argv[2]);
    int n = j2 - j1;

    printf("n = %d\n", n);
    Liste_Point listeP = creer_liste_Point_vide();

    if(n==0){
        ERREUR_FATALE("n=0");
    }

    if(n==1){
        Point P0 = set_point(atof(argv[3]), atof(argv[4]));
        Point P1 = set_point(atof(argv[5]), atof(argv[6]));
        printf("=======\n");
        printf("Point P0: (%.0f, %.0f)\n", P0.x, P0.y);
        printf("Point P1: (%.0f, %.0f)\n", P1.x, P1.y);
        printf("=======\n");
        ajouter_element_liste_Point(&listeP, P0);
        ajouter_element_liste_Point(&listeP, P1);
    }

    else if(n==2){
        Point P0 = set_point(atof(argv[3]), atof(argv[4]));
        Point P1 = set_point(atof(argv[5]), atof(argv[6]));
        Point P2 = set_point(atof(argv[7]), atof(argv[8]));
        printf("=======\n");
        printf("Point P0: (%.0f, %.0f)\n", P0.x, P0.y);
        printf("Point P1: (%.0f, %.0f)\n", P1.x, P1.y);
        printf("Point P2: (%.0f, %.0f)\n", P2.x, P2.y);
        printf("=======\n");
        ajouter_element_liste_Point(&listeP, P0);
        ajouter_element_liste_Point(&listeP, P1);
        ajouter_element_liste_Point(&listeP, P2);

    }

    else if (n == 8){ // exemple page 53
        Point P0 = set_point(0,0);
        ajouter_element_liste_Point(&listeP, P0);
        Point P1 = set_point(1,0);
        ajouter_element_liste_Point(&listeP, P1);
        Point P2 = set_point(1,1);
        ajouter_element_liste_Point(&listeP, P2);
        Point P3 = set_point(1,2);
        ajouter_element_liste_Point(&listeP, P3);
        Point P4 = set_point(2,2);
        ajouter_element_liste_Point(&listeP, P4);
        Point P5 = set_point(3,2);
        ajouter_element_liste_Point(&listeP, P5);
        Point P6 = set_point(3,3);
        ajouter_element_liste_Point(&listeP, P6);
        Point P7 = set_point(4,3);
        ajouter_element_liste_Point(&listeP, P7);
        Point P8 = set_point(5,3);
        ajouter_element_liste_Point(&listeP, P8);
        printf("Attendu : C1 = (1.737287, 0.929380)\n C2 = (1.844176, 3.489158)\n");
    }

    else if (n >= 3) {
        Point Q0 = set_point(atof(argv[3]), atof(argv[4]));
        Point Q1 = set_point(atof(argv[5]), atof(argv[6]));
        Point Q2 = set_point(atof(argv[7]), atof(argv[8]));
        Point Q3 = set_point(atof(argv[9]), atof(argv[10]));
   
        printf("=======\n");
        printf("Point Q0: (%.0f, %.0f)\n", Q0.x, Q0.y);
        printf("Point Q1: (%.0f, %.0f)\n", Q1.x, Q1.y);
        printf("Point Q2: (%.0f, %.0f)\n", Q2.x, Q2.y);
        printf("Point Q3: (%.0f, %.0f)\n", Q3.x, Q3.y);
        printf("=======\n");

        Bezier3 B3;
        B3.C0 = Q0;
        B3.C1 = Q1;
        B3.C2 = Q2;
        B3.C3 = Q3;
    
        for(float i=0; i<=n; i++){
            float t = i/n;
            Point Pi = point_bezier3(B3, t);
            ajouter_element_liste_Point(&listeP, Pi);
        }
    }

    Tableau_Point P = sequence_points_liste_vers_tableau(listeP);
    Bezier3 B = approx_bezier3(P, j1, j2);
    
    printf("=======\n");
    printf("Point C0: (%.6f, %.6f)\n", B.C0.x, B.C0.y);
    printf("Point C1: (%.6f, %.6f)\n", B.C1.x, B.C1.y);
    printf("Point C2: (%.6f, %.6f)\n", B.C2.x, B.C2.y);
    printf("Point C3: (%.6f, %.6f)\n", B.C3.x, B.C3.y);
    printf("=======\n");
}