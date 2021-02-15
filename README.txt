@Mathis Grange & @Mattéo Decorsaire
Sauf mention contraire les paquetages sont de notre conception. (LICENSE-MIT)
(Nous contacter si oubli important)

===============
= LES PAQUETS =
===============

IMAGE : gère le type IMAGE (Une partie des fonctions du début du fichier appartiennent aux enseignants)
GEOM2D : opérations sur des points et des vecteurs
STRUCTURES : gère les structures Liste_Point et Tableau_Point (entièrement recopié du livret du projet)
CONTOUR : algorithme qui determine des contours d'une images
EPS : transforme des listes de point en fichier eps

Les images et contours sont dans le dossier `Images`


===============
= UTILISATION =
===============
pour compiler `make`

Pour écrire une image pbm sur la sortie standard :
./test_image <fichier pbm>

Pour tester toutes les fonctions geom2d sur 4 points :
./test_geom2d ./test_geom2d <x, y Point A> <x, y Point B> <x, y Point C> <x, y Point D>

Pour écrire un fichier contours :
./test_contour <nom fichier pbm> <nom fichier .contours>

Pour écrire un fichier eps :
./test_eps <nom fichier pbm> <nom fichier eps>