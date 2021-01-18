#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"

void main(int argc, char *argv[]) {
    if (argc != 2){
        printf("Usage : ./test_image <nom du fichier de test>");
    }
    ecrire_image(lire_fichier_image(argv[1]));
}