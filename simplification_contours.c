#include <stdio.h>
#include <stdlib.h>

#include "simplification_contours.h"
#include "structures.h"
#include "image.h"
#include "eps.h"

Liste_Point simplification_douglas_peucker(Tableau_Point T, int j1, int j2, double d){
    double dmax = 0;
    double dj;
    int k = j1;
    Liste_Point Liste = creer_liste_Point_vide();
    Liste_Point *L = &Liste;

    Segment Pj1j2 = init_segment(T.tab[j1], T.tab[j2]);

    for (int j=j1+1; j<=j2; j++){
        dj = distance_point_segment(T.tab[j], Pj1j2);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d){
        ajouter_element_liste_Point(L, T.tab[j1]);
        ajouter_element_liste_Point(L, T.tab[j2]);
    }
    else{
        Liste = concatener_liste_Point(simplification_douglas_peucker(T, j1, k, d), simplification_douglas_peucker(T, k, j2, d));
    }
    return Liste;
}

void PbmToEps_simplification_segment(char *nom_entree, char *nom_sortie, double d){ 
    Image I = lire_fichier_image_inverse(nom_entree);
    Image Im = creer_image_masque(I);
    FILE *f = initialiser_eps(nom_sortie, 0, 0, I.L, I.H );
    Point P;
    while(trouver_pixel_depart(Im, &P)){
        Liste_Point L = creer_liste_Point_vide();
        L = contour(I, &Im, P.x, P.y);
        Tableau_Point T = sequence_points_liste_vers_tableau(L);
        L = simplification_douglas_peucker(T, 0, T.taille-1, d);
        T = sequence_points_liste_vers_tableau(L);
        ecrire_eps_point(f, T);
    }
    fin_eps(f);
}