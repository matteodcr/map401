#ifndef _EPS_H_
#define _EPS_H_

#include "image.h"
#include "contour.h"

FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax);

/* Ecrit un contour dans un fichier. */

void ecrire_eps_point(FILE *f, Tableau_Point T);

void ecrire_eps_Bezier(FILE *f, Tableau_Bezier3 T);

void fin_eps(FILE* f);

/* Vectorise un fichier .pbm en .eps */
void PbmToEps(char *nom_entree, char *nom_sortie);

void PbmToEps_Bezier1(char *nom_entree, char *nom_sortie, double d);

void PbmToEps_Bezier2(char *nom_entree, char *nom_sortie, double d);

void PbmToEps_Bezier3(char *nom_entree, char *nom_sortie, double d);

#endif