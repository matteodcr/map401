#include "types_macros.h"
#include "structures.h"
#include "geom2d.h"
#include "image.h"
#include "image.h"
#include "bezier.h"

Liste_Point simplification_douglas_peucker_bezier1(Tableau_Point T, int j1, int j2, double d){
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
        Liste = concatener_liste_Point(simplification_douglas_peucker_bezier1(T, j1, k, d), simplification_douglas_peucker_bezier1(T, k, j2, d));
    }
    return Liste;
}


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
        float alpha = (3.*n_reel)/(n_reel*n_reel -1.);
        float beta = (1.- (2.*n_reel))/(2.*(n_reel+1.));

        Point Cx = set_point(0, 0);

        for(int i=1; i<n; i++){
            Cx = add_point(Cx, P.tab[i+j1]);
        }

        B.C1 = add_point(mult_point(alpha, Cx), mult_point(beta, add_point(B.C0, B.C2)));
        return B;
    }
    ERREUR_FATALE("n=0")
}

Liste_Bezier3 simplification_douglas_peucker_bezier2(Tableau_Point T, int j1, int j2, double d){
    Bezier2 B2 = approx_bezier2(T, j1, j2);
    
    int n = j2-j1;
    double dmax = 0;
    int k = j1;

    Liste_Bezier3 Liste = creer_liste_Bezier3_vide();
    
    for (int j=j1+1; j<=j2; j++){
        int i = j-j1;
        float ti = (float)i/(float)n;
        double dj = distance_point_bezier2(T.tab[j], B2, ti);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }
    
    if (dmax <= d){
        Bezier3 B3 = Bezier2ToBezier3(B2);
        ajouter_element_liste_Bezier3(&Liste, B3);
    }
    else{
        Liste = concatener_liste_Bezier3(simplification_douglas_peucker_bezier2(T, j1, k, d), simplification_douglas_peucker_bezier2(T, k, j2, d));
    }
    return Liste;
}

float fonction_gamma(float k, float n){
    return ((6.*k*k*k*k)-(8.*n*k*k*k)+(6.*k*k)-(4.*n*k)+(n*n*n*n)-(n*n));
}

Bezier3 approx_bezier3(Tableau_Point P, int j1, int j2){
    int n = j2-j1;

    if (n < 3 && n != 0){
        Bezier2 B2 = approx_bezier2(P, j1, j2);
        return Bezier2ToBezier3(B2);

    } else if (n >= 3){
        Bezier3 B3;

        B3.C0 = P.tab[j1];
        B3.C3 = P.tab[j2];

        float n_r = (float)n;
        float alpha = ((-15.*n_r*n_r*n_r)+(5.*n_r*n_r)+(2.*n_r)+4.)/(3.*(n_r+2.)*((3.*n_r*n_r)+1.));
        float beta = ((10.*n_r*n_r*n_r)-(15.*n_r*n_r)+n_r+2.)/(3.*(n_r+2.)*((3.*n_r*n_r)+1.));
        float lambda = (70.*n_r)/(3.*((n_r*n_r)-1.)*((n_r*n_r)- 4.)*((3.*n_r*n_r)+1.));


        Point C1tmp = set_point(0, 0);
        Point C2tmp = set_point(0, 0);

        for(int i=1; i<n; i++){
            C1tmp = add_point(C1tmp, mult_point(fonction_gamma(i, n_r), P.tab[i+j1]));
            C2tmp = add_point(C2tmp, mult_point(fonction_gamma(n_r-i, n_r), P.tab[i+j1]));
        }
        C1tmp = mult_point(lambda, C1tmp);
        C2tmp = mult_point(lambda, C2tmp);

        B3.C1 = add_point(mult_point(alpha, P.tab[j1]), add_point(mult_point(beta, P.tab[j2]), C1tmp));
        B3.C2 = add_point(mult_point(beta, P.tab[j1]), add_point(mult_point(alpha, P.tab[j2]), C2tmp));

        return B3; 
    }
    ERREUR_FATALE("n=0")
}


Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point T, int j1, int j2, double d){
    Bezier3 B3 = approx_bezier3(T, j1, j2);
    
    int n = j2-j1;
    double dmax = 0;
    int k = j1;

    Liste_Bezier3 Liste = creer_liste_Bezier3_vide(); 
    
    for (int j=j1+1; j<=j2; j++){
        int i = j-j1;
        float ti = (float)i/(float)n;
        double dj = distance_point_bezier3(T.tab[j], B3, ti);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }
    
    if (dmax <= d){
        ajouter_element_liste_Bezier3(&Liste, B3);
    }
    else{
        Liste = concatener_liste_Bezier3(simplification_douglas_peucker_bezier2(T, j1, k, d), simplification_douglas_peucker_bezier2(T, k, j2, d));
    }
    return Liste;
}
