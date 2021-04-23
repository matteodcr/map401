#!/bin/bash

cd Images/resultat-script && cd ../.. || mkdir Images/resultat-script

./test_eps Images/pbm/$1.pbm Images/resultat-script/[CONTOUR]$1.eps

./test_douglas_peucker_bezier1 Images/pbm/$1.pbm Images/resultat-script/[BEZIER1][1]$1.eps 1
./test_douglas_peucker_bezier1 Images/pbm/$1.pbm Images/resultat-script/[BEZIER1][3]$1.eps 3
./test_douglas_peucker_bezier1 Images/pbm/$1.pbm Images/resultat-script/[BEZIER1][10]$1.eps 10

./test_douglas_peucker_bezier2 Images/pbm/$1.pbm Images/resultat-script/[BEZIER2][1]$1.eps 1
./test_douglas_peucker_bezier2 Images/pbm/$1.pbm Images/resultat-script/[BEZIER2][3]$1.eps 3
./test_douglas_peucker_bezier2 Images/pbm/$1.pbm Images/resultat-script/[BEZIER2][10]$1.eps 10

./test_douglas_peucker_bezier3 Images/pbm/$1.pbm Images/resultat-script/[BEZIER3][1]$1.eps 1
./test_douglas_peucker_bezier3 Images/pbm/$1.pbm Images/resultat-script/[BEZIER3][3]$1.eps 3
./test_douglas_peucker_bezier3 Images/pbm/$1.pbm Images/resultat-script/[BEZIER3][10]$1.eps 10
