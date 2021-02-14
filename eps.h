#ifndef _EPS_H_
#define _EPS_H_

#include "image.h"
#include "contour.h"

FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax);

/* Ecrit un contour dans un fichier. */
void ecrire_eps(FILE *f, Tableau_Point T);

void fin_eps(FILE* f);

void PbmToEps(char *nom_entree, char *nom_sortie);

#endif