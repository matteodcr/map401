#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "contour.h"
#include "image.h"
#include "geom2d.h"

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

void initialiser_fichier(){
    remove("tmp1.txt");
}

void ecrire_contour_fichier(Liste_Point L){
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    
    int k;
    int nP = TP.taille;

    FILE *f = fopen("tmp1.txt", "a");

    fprintf(f, "%d\n", nP);
    for (k = 0; k < nP; k++){
        Point P = TP.tab[k];
        fprintf(f, "%.1f %.1f\n", P.x, P.y);
    }
    fprintf(f, "\n");

    free(TP.tab);
    fclose(f);
}

void init_nb_contour(int nb_contours){
    FILE *f = fopen("tmp2.txt", "w");
    fprintf(f, "%d\n\n", nb_contours);
    fclose(f);
}

void formater_fichier_sortie(char *nom_sortie){
   FILE *f1 = fopen("tmp1.txt", "r"); 
   FILE *f2 = fopen("tmp2.txt", "r");
  
   FILE *f3 = fopen(nom_sortie, "w"); 
   char c; 
  
   if (f1 == NULL || f2 == NULL || f3 == NULL) { 
         puts("Impossible d'ouvrir les fichiers"); 
         exit(1);
   } 

   while ((c = fgetc(f2)) != EOF) 
      fputc(c, f3); 

   while ((c = fgetc(f1)) != EOF) 
      fputc(c, f3); 
  
   fclose(f1); 
   fclose(f2); 
   fclose(f3); 
}

int trouver_pixel_depart(Image I, Point *P){
    for (int y=1; y<=I.H; y++){
        for (int x=1; x<=I.L; x++){
            if(get_pixel_image(I, x, y)==NOIR){
                P->x = x;
                P->y = y;
                return 1;
            }
        }
    }
    return 0;
}

Liste_Point contour(Image I, Image *Im, int x, int y){
    Point P0;
    P0.x = x-1;
    P0.y = y-1;

    printf("Point initial : (%.1f, %.1f)\n", P0.x, P0.y);

    Liste_Point Liste = creer_liste_Point_vide();
    Point P = P0;
    Orientation Or = Est;

    
    while(true){
        ajouter_element_liste_Point(&Liste, P);

        if (Or == Est){
            set_pixel_image(*Im, P.x+1, P.y+1, BLANC);
        }

        avance(&P, Or);
        Or = nouvelle_orientation(I, P, Or);

        if (P.x==P0.x && P.y == P0.y && Or==Est){
            ajouter_element_liste_Point(&Liste, P);
            return Liste;
        }
    }
    return Liste;
}

void PbmToFile(char *nom_entree, char* nom_sortie){
    Image I = lire_fichier_image_inverse(nom_entree);
    Image Im = creer_image_masque(I);
    Point P;

    initialiser_fichier();

    int i = 0;

    while(trouver_pixel_depart(Im, &P)){
        i++;
        Liste_Point L = creer_liste_Point_vide();
        L = contour(I, &Im, P.x, P.y);
        ecrire_contour_fichier(L);
        printf("%i\n", i);
    }
    init_nb_contour(i);
    formater_fichier_sortie(nom_sortie);
}





