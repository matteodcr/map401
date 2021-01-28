#include <stdio.h>
#include <stdlib.h>
#include <calcul_contour.h>
#include <image.h>

Point set_point(double x, double y){
    Point P = {x,y}; return P;
}

Cellule_Liste_Point* creer_element_liste_Point(Point v){
    Cellule_Liste_Point *el;
    el = (Cellule_Liste_Point*)malloc(sizeof(Cellule_Liste_Point));
    if (el == NULL){
        fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
        exit(-1);
    }

    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Point creer_liste_Point_vide(){
    Liste_Point L = {0, NULL, NULL};
    return L;
}

void ajouter_element_liste_Point(Liste_Point *L, Point e){
    Cellule_Liste_Point *el;
    el = creer_element_liste_Point(e);

    if(L->taille == 0){
        L->first = L->last = el;
    }
    else{
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
}

Liste_Point supprimer_liste_Point(Liste_Point L){
    Cellule_Liste_Point *el = L.first;

    while (el){
        Cellule_Liste_Point *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2){
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;

    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L){
    Tableau_Point T;

    T.taille = L.taille;
    T.tab = malloc(sizeof(Point)*T.taille);

    if (T.tab == NULL){
        fprintf(stderr, "sequence_points_liste_vers_tableau : allocation impossible");
        exit(-1);
    }

    int k = 0;
    Cellule_Liste_Point *el = L.first;
    while(el){
        T.tab[k] = el->data;
        k++;
        el = el->suiv;
    }

    return T;
}

void ecrire_contour(Liste_Point L){
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;

    printf("\nNombre de segments composant le contour : %d\n", nP-1);
    printf("%d points : [", nP);
    for (k = 0; k < nP; k++){
        Point P = TP.tab[k];
        printf(" (%5.1f, %5.1f)", P.x, P.y);
    }
    printf("]\n");
    free(TP.tab);
}

void ecrire_contour_fichier(Liste_Point L){
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;
    int nC = 1;

    FILE *f = fopen("resultat.contours", "w");

    fprintf(f, "%d\n", nC);
    fprintf(f, "%d\n", nP);
    for (k = 0; k < nP; k++){
        Point P = TP.tab[k];
        fprintf(f, "%.1f %.1f\n", P.x, P.y);
    }
    free(TP.tab);
}

FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax){
	FILE *f;
	
	/* ouverture du fichier nom_f en lecture */
	f = fopen(nom_f, "w");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("initialiser_eps : ouverture du fichier impossible\n");
	}
	
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", xmin, ymin, xmax, ymax);
    fprintf(f, "0.1 setlinewidth\n");
	
	return f;
}

void point_courant(FILE *f, Point A){
    fprintf(f, "%0.f %0.f moveto\n", A.x, A.y);
}

void tracer_segment(FILE *f,Point B){
    fprintf(f, "%0.f %0.f lineto\n",B.x, B.y);
}

void tracer_point(FILE *f, Point C, float rayon){
    fprintf(f, "newpath\n");
    fprintf(f, "%0.f %0.f %f 0 360 arc\n", C.x, C.y, rayon);
    fprintf(f, "fill\n");
    fprintf(f, "closepath\n");
}

void fin_eps(FILE* f){
	fprintf(f, "showpage");
    fclose(f);
}

void ecrire_eps(char *f_entree, char *f_sortie, int m){
    Image I = lire_fichier_image_inverse(f_entree);
    Liste_Point L = contour(I);
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

int rechercher_pixel_noir(Image I, int *xp, int *yp){
    int x, y;
	for(y=1; y<=I.H; y++){
		for(x=1; x<=I.L; x++){
			if (get_pixel_image(I, x, y)==NOIR ){
                xp = &x;
                yp = &y;
				return 1;
			}	
		}
    }
    return 0;
}

void contour_multiple(Image I, Image Im){
    int *xp;
    int *yp;

    while(rechercher_pixel_noir(Im, xp, yp)==1){
        Liste_Point L = creer_liste_Point_vide();
        L = contour(I);
        ecrire_contour(L);
    }
}

Point trouver_pixel_depart(Image I){
    for (int y=0; y<I.H; y++){
        for (int x=0; x<I.L; x++){
            if(get_pixel_image(I, x, y)==NOIR 
            && get_pixel_image(I, x, y-1)==BLANC){
                Point P = {x, y};
                return P;
            }
        }
    }
    ERREUR_FATALE("PAS DE POINT NOIR");
}



void avance(Point *P, Orientation O){
    switch (O)
    {
    case Est:
        P->x +=1;
        break;
    
    case Ouest:
        P->x -=1;
        break;
    
    case Nord:
        P->y -=1;
        break;

    case Sud:
        P->y += 1;
        break;
    
    default:
        break;
    }
}

Orientation tourner_droite(Orientation O){
    switch (O)
    {
    case Est:
        O = Sud;
        break;
    
    case Ouest:
        O = Nord;
        break;
    
    case Nord:
        O = Est;
        break;

    case Sud:
        O = Ouest;
        break;
    }

    return O;
}

Orientation tourner_gauche(Orientation O){
    switch (O)
    {
    case Est:
        return Nord;
        break;
    
    case Ouest:
        return Sud;
        break;
    
    case Nord:
        return Ouest;
        break;

    case Sud:
        return Est;
        break;
    }
    return O;
}

Orientation nouvelle_orientation(Image I, Point P, Orientation O){
    Pixel gauche;
    Pixel droit;

    switch (O)
    {
    case Nord:
        gauche = get_pixel_image(I, P.x, P.y);
        droit = get_pixel_image(I, P.x+1, P.y);
        break;
    
    case Est:
        gauche = get_pixel_image(I, P.x+1, P.y);
        droit = get_pixel_image(I, P.x+1, P.y+1);
        break;
    
    case Sud:
        gauche = get_pixel_image(I, P.x+1, P.y+1);
        droit = get_pixel_image(I, P.x, P.y+1);
        break;

    case Ouest:
        gauche = get_pixel_image(I, P.x, P.y+1);
        droit = get_pixel_image(I, P.x, P.y);
        break;
    
    default:
        break;
    }

    if(gauche==NOIR){return tourner_gauche(O);}
    if(droit==BLANC){return tourner_droite(O);}
    return O;
}



Liste_Point contour(Image I){
    int n = 0;

    Point P0 = trouver_pixel_depart(I);
    P0.x = P0.x-1;
    P0.y = P0.y-1;

    printf("Point initial : (%.1f, %.1f)\n", P0.x, P0.y);

    Liste_Point Liste = creer_liste_Point_vide();

    Point P = P0;
    Orientation Or = Est;
    
    while(true){
        n++;
        ajouter_element_liste_Point(&Liste, P);
        avance(&P, Or);
        Or = nouvelle_orientation(I, P, Or);
        if (P.x==P0.x && P.y == P0.y && Or==Est){
            printf("\nNombre de segments composant le contour : %d\n", n);
            return Liste;
        }
    }
    return Liste;
}