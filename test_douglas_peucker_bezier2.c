#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "eps.h"


int main(int argc, char *argv[]) {
    if (argc != 4){
        printf("Usage : ./test_douglas_peucker_bezier2 <Fichier PBM> <Fichier résultat> <seuil>\n");
        exit(1);
    }

    double d = strtod(argv[3],NULL);
    PbmToEps_Bezier2(argv[1], argv[2], d);

    return 0;
}