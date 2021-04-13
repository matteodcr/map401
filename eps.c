#include <stdio.h>
#include <stdlib.h>

#include "eps.h"
#include "structures.h"
#include "image.h"
#include "contour.h"
#include "bezier.h"

void point_courant(FILE* f, Point A){
    fprintf(f, "\n%f %f moveto\n", A.x, A.y);
}

void tracer_segment(FILE *f, Point B){
    fprintf(f, "%f %f lineto\n",B.x, B.y);
}

void tracer_courbe(FILE *f, Bezier3 B){
    fprintf(f, "%f %f %f %f %f %f curveto\n",B.C1.x, B.C1.y, B.C2.x, B.C2.y, B.C3.x, B.C3.y);
}

FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax){ 
    FILE *f = fopen(nom_f, "w");
    if (f == (FILE *)NULL){
        ERREUR_FATALE("initialiser_eps : ouverture du fichier sortie impossible\n");
    }
    
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", xmin, ymin, xmax, ymax);
    fprintf(f, "0.1 setlinewidth\n");
    
    return f;
}

void ecrire_eps_point(FILE *f, Tableau_Point T){
    point_courant(f, T.tab[0]);
    for (int i=1; i<T.taille-1; i++){
        tracer_segment(f, T.tab[i]);
    }
}

void ecrire_eps_Bezier(FILE *f, Tableau_Bezier3 T){
    point_courant(f, T.tab[0].C0);
    for (int i=0; i<T.taille; i++){
        tracer_courbe(f, T.tab[i]);
    }
}

void fin_eps(FILE* f){
    fprintf(f, "fill\n");
    fprintf(f, "showpage");
    fclose(f);
}

void PbmToEps(char *nom_entree, char *nom_sortie){
    
    Image I = lire_fichier_image_inverse(nom_entree);
    Image Im = creer_image_masque(I);
    FILE *f = initialiser_eps(nom_sortie, 0, 0, I.L, I.H );

    Point P;
    while(trouver_pixel_depart(Im, &P)){
        Liste_Point L = creer_liste_Point_vide();
        L = contour(I, &Im, P.x, P.y);
        Tableau_Point T = sequence_points_liste_vers_tableau(L);
        ecrire_eps_point(f, T);
    }
    fin_eps(f);
}

void PbmToEps_Bezier2(char *nom_entree, char *nom_sortie, double d){
    
    Image I = lire_fichier_image_inverse(nom_entree);
    Image Im = creer_image_masque(I);
    FILE *f = initialiser_eps(nom_sortie, 0, 0, I.L, I.H );

    int nb_bezier = 0;
    int nb_contour = 0;

    Point P;
    while(trouver_pixel_depart(Im, &P)){
        Liste_Point L = creer_liste_Point_vide();
        L = contour(I, &Im, P.x, P.y);
        Tableau_Point T = sequence_points_liste_vers_tableau(L);
        Liste_Bezier3 LB = simplification_douglas_peucker_bezier2(T, 0, T.taille-1, d);
        Tableau_Bezier3 TB = sequence_bezier3_liste_vers_tableau(LB);
        nb_bezier = nb_bezier + TB.taille;
        ecrire_eps_Bezier(f, TB);
        nb_contour++;
    }
    printf("Nombre de bézier2 : %d\n", nb_bezier);
    printf("Nombre de contours : %d\n", nb_contour);
    fin_eps(f);
}