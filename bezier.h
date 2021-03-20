#ifndef _BEZIER_H_
#define _BEZIER_H_
#include "types_macros.h"
#include "structures.h"
#include "geom2d.h"
#include "image.h"

Point point_bezier2(Bezier2 B, double t);

Bezier2 approx_bezier2(Tableau_Point P, int j1, int j2);

#endif