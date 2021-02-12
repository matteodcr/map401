#ifndef _EPS_H_
#define _EPS_H_

#include "geom2d.h"
#include "image.h"
#include "calcul_contour.h"

FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax);

void point_courant(FILE *f, Point A);

void tracer_segment(FILE *f,Point B);

void tracer_point(FILE *f, Point C, float rayon);

void ecrire_eps(FILE *f, Tableau_Point T);

void fin_eps(FILE* f);

#endif