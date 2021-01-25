#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"calcul_contour.h"
#include"image.h"

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("Usage : ./test_calcul_contour <nom du fichier de test>");
    }
    ecrire_contour_fichier(contour(lire_fichier_image(argv[1])));
    return 0;
}