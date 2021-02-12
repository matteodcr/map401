#include <stdio.h>
#include <stdlib.h>

#include <eps.h>
#include <image.h>
#include <geom2d.h>
#include <calcul_contour.h>

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

void point_courant(FILE* f, Point A){
    fprintf(f, "%0.f %0.f moveto\n", A.x, A.y);
}

void tracer_segment(FILE *f, Point B){
    fprintf(f, "%0.f %0.f lineto\n",B.x, B.y);
}

void fin_eps(FILE* f){
    fprintf(f, "showpage");
    fclose(f);
}

void ecrire_eps(FILE *f, Tableau_Point T){
    point_courant(f, T.tab[0]);
    
    tracer_segment(f, T.tab[0]);
    for (int i=0; i<T.taille; i++){
        tracer_segment(f, T.tab[i]);
    }
    tracer_segment(f, T.tab[0]);
    fprintf(f, "fill\n");
}