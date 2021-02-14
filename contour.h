#ifndef _CALCUL_CONTOUR_H_
#define _CALCUL_CONTOUR_H_
#include "types_macros.h"
#include "structures.h"
#include "geom2d.h"
#include "image.h"


typedef enum {Nord, Est, Sud, Ouest} Orientation;

Liste_Point contour(Image I, Image *Im, int x, int y);
int trouver_pixel_depart(Image I, Point *P);

void PbmToFile(char *nom_entree, char *nom_sortie);

#endif