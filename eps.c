#include <stdio.h>
#include <stdlib.h>

#include <eps.h>
#include <image.h>
#include <geom2d.h>
#include <calcul_contour.h>

FILE* initialiser_fichier_entree(char *nom_f_entree, char *nom_f_sortie, int xmin, int ymin, int xmax, int ymax){
	FILE *f_entree = fopen(nom_f_entree, "w");
	if (f_entree == (FILE *)NULL){
		ERREUR_FATALE("initialiser_eps : ouverture du fichier entree impossible\n");
	}

	return f_entree;
}

FILE* initialiser_fichier_sortie(char *nom_f_sortie, int xmin, int ymin, int xmax, int ymax){
    FILE *f_sortie = fopen(nom_f_sortie, "w");
	if (f_sortie == (FILE *)NULL){
		ERREUR_FATALE("initialiser_eps : ouverture du fichier sortie impossible\n");
	}
	
    fprintf(f_sortie, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f_sortie, "%%%%BoundingBox: %d %d %d %d\n", xmin, ymin, xmax, ymax);
    fprintf(f_sortie, "0.1 setlinewidth\n");
	
	return f_sortie;
}

void point_courant(FILE* f_entree, FILE *f_sortie, Point A){
    fscanf(f_entree)
    fprintf(f_sortie, "%0.f %0.f moveto\n", A.x, A.y);
}

void tracer_segment(FILE* f_entree, FILE *f_sortie, Point B){
    fprintf(f_sortie, "%0.f %0.f lineto\n",B.x, B.y);
}

void fin_eps(FILE* f_entree, FILE *f_sortie){
	fprintf(f_sortie, "showpage");
    fclose(f_entree);
    fclose(f_sortie);
}

void ecrire_eps(char *f_entree, char *f_sortie, int m){
    Image I = lire_fichier_image_inverse(f_entree);
    Liste_Point L = contour_multiple(I);
    Tableau_Point T = sequence_points_liste_vers_tableau(L);
    

    FILE *f = initialiser_eps(f_sortie, 0, 0, I.L, I.H); 
    point_courant(f, T.tab[0]);
    
    if (m==1){
        tracer_segment(f, T.tab[0]);
        for (int i=0; i<T.taille; i++){
            tracer_segment(f, T.tab[i]);
        }
        tracer_segment(f, T.tab[0]);
        fprintf(f, "stroke\n");
    }

    if (m==2){  
        tracer_segment(f, T.tab[0]);
        for (int i=0; i<T.taille; i++){
            tracer_segment(f, T.tab[i]);
        }
        tracer_segment(f, T.tab[0]);
        fprintf(f, "stroke\n");

        tracer_point(f, T.tab[0], 0.2);
        for (int i=0; i<T.taille; i++){
            tracer_point(f, T.tab[i], 0.2);
        }
    }

    if (m==3){
        tracer_segment(f, T.tab[0]);
        for (int i=0; i<T.taille; i++){
            tracer_segment(f, T.tab[i]);
        }
        tracer_segment(f, T.tab[0]);
        fprintf(f, "fill\n");
    }

    fin_eps(f);
}