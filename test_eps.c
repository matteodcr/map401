#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"eps.h"

int main(int argc, char *argv[]) {
    if (argc != 3){
        printf("Usage : ./eps <nom du fichier pbm> <nom du fichier eps>");
        return 0;
    }

    PbmToEps(argv[1], argv[2]);
}
   