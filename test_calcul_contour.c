#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"calcul_contour.h"
#include"image.h"

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("Usage : ./test_image <nom du fichier de test>");
    }
    ecrire_contour(contour(lire_fichier_image(argv[1])));
    return 0;
}