#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"calcul_contour.h"
#include"image.h"

int main(int argc, char *argv[]) {
    if (argc != 3){
        printf("Usage : ./test_calcul_contour <nom du fichier de test>");
    }

    contour_multiple(lire_fichier_image_inverse(argv[1]), argv[2]);
    return 0;
}