#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "simplification_contours.h"


int main(int argc, char *argv[]) {
    if (argc != 4){
        printf("Usage : ./test_douglas_peucker <Fichier PBM> <Fichier résultat> <seuil>\n");
    }

    double d = strtod(argv[3],NULL);
    PbmToEps_simplification_segment(argv[1], argv[2], d);

    return 0;
}