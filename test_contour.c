#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"contour.h"
#include"image.h"

int main(int argc, char *argv[]) {
    if (argc != 3){
        printf("Usage : ./test_contour <nom du fichier pbm> <nom du fichier .contours");
        return 0;
    }

    PbmToFile(argv[1], argv[2]);
    return 0;
}