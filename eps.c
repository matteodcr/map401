#include <stdio.h>
#include <stdlib.h>

#include "eps.h"
#include "structures.h"
#include "image.h"
#include "contour.h"

void point_courant(FILE* f, Point A){
    fprintf(f, "\n%0.f %0.f moveto\n", A.x, A.y);
}

void tracer_segment(FILE *f, Point B){
    fprintf(f, "%0.f %0.f lineto\n",B.x, B.y);
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

void ecrire_eps(FILE *f, Tableau_Point T){
    point_courant(f, T.tab[0]);
    for (int i=1; i<T.taille-1; i++){
        tracer_segment(f, T.tab[i]);
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
        ecrire_eps(f, T);
    }
    fin_eps(f);
}