#ifndef _SIMPLIFICATION_CONTOURS_H_
#define _SIMPLIFICATION_CONTOURS_H_

#include "structures.h"
#include "image.h"
#include "eps.h"

void PbmToEps_simplification_segment(char *nom_entree, char *nom_sortie, double d);

Liste_Point simplification_douglas_peucker(Tableau_Point T, int j1, int j2, double d);

#endif