#ifndef _CALCUL_CONTOUR_H_
#define _CALCUL_CONTOUR_H_
#include "types_macros.h"
#include "structures.h"
#include "geom2d.h"
#include "image.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;

/* Renvoie un contour (liste de points) ayant pour pixel de départ (x,y) */
Liste_Point contour(Image I, Image *Im, int x, int y);

/* Si il y a encore un pixel noir dans l'image => renvoie 1 
et met ses coordonnées dans P, sinon renvoie 0 */
int trouver_pixel_depart(Image I, Point *P);

/* Ecrit un fichier qui contient plusieurs contorus d'après l'image entrée */
void PbmToFile(char *nom_entree, char *nom_sortie);

#endif