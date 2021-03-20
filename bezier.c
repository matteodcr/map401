#include "types_macros.h"
#include "structures.h"
#include "geom2d.h"
#include "image.h"
#include "image.h"
#include "bezier.h"

Bezier2 approx_bezier2(Tableau_Point P, int j1, int j2){
    int n = j2-j1;
    Bezier2 B;

    B.C0 = P.tab[j1];
    B.C2 = P.tab[j2];

    if (n == 1){
        B.C1 = add_point(B.C0, B.C2);
        B.C1 = mult_point(0.5, B.C1);
        return B;

    } else if (n >= 2){
        float n_reel = (float)n;
        float alpha = (3*n_reel)/(n_reel*n_reel -1);
        float beta = (1- 2*(n_reel))/(2*(n_reel+1));

        Point Cx = set_point(0, 0);

        for(int i=1; i<n; i++){
            Cx = add_point(Cx, P.tab[i+j1]);
        }

        B.C1 = add_point(mult_point(alpha, Cx), mult_point(beta, add_point(B.C0, B.C2)));
        return B;
    }
    ERREUR_FATALE("n=0")
}

Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point T, int j1, int j2, double d){
    Bezier2 B = approx_bezier2(T, j1, j2);
    
    int n = j2-j1;
    double dmax = 0;
    int k = j1;

    Liste_Point Liste = creer_liste_Point_vide();
    
    for (int j=j1+1; j<=j2; j++){
        int i = j-j1;
        float ti = (float)i/(float)n;
        double dj = distance_point_bezier2(T.tab[j], B, ti);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }
    
    if (dmax <= d){
        ajouter_element_liste_Point(&Liste, B.C0);
        ajouter_element_liste_Point(&Liste, B.C1);
        ajouter_element_liste_Point(&Liste, B.C2);
    }
    else{
        Liste = concatener_liste_Point(simplification_douglas_peucker_bezier2(T, j1, k, d), simplification_douglas_peucker_bezier2(T, k, j2, d));
    }
    return Liste;
}
