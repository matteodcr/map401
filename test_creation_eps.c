#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"calcul_contour.h"
#include"image.h"
#include"eps.h"


int main(int argc, char *argv[]) {
    if (argc != 4){
        printf("Usage : ./test_creation_eps <nom du fichier de test> <nom du fichier résultat> <mode>");
    }
    if(strcmp(argv[1], argv[2])==0){
        printf("Les deux fichiers doivent etre différents");
        return 1;
    }
    ecrire_eps(argv[1], argv[2], atoi(argv[3]));
    return 0;
}