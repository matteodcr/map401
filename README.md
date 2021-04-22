# Vectorisation et simplification d'une image bitmap

## Les paquetages

 - `IMAGE` : gère le type `Image` (Une partie des fonctions du début du fichier appartiennent aux enseignants)
 - `GEOM2D` : opérations sur des points et des vecteurs
 - `STRUCTURES` : gère les structures `Liste_Point`, `Tableau_Point`, `Liste_Bezier3`, `Tableau_Bezier3`
 - `CONTOUR` : algorithme qui determine des contours d'une images
 - `BEZIER` : simplifie le contours avec des courbes de Bezier en fonction d'une valeur seuil
  - `EPS` : transforme des listes de point en fichier eps

Les images et contours sont dans le dossier `Images`.

## Tests

 - Pour compiler tout : `make`
 - Pour 'nettoyer' : `make clean`

 - Pour écrire une image pbm sur la sortie standard :
```
./test_image <fichier pbm>
```

 - Pour tester toutes les fonctions geom2d sur 4 points :
```
./test_geom2d <x,y A> <x,y B> <x,y C> <x,y D>
```

 - Pour écrire un fichier contours :
```
./test_contour <nom fichier pbm> <nom fichier .contours>
```
 - Pour écrire un fichier eps :
```
./test_eps <nom fichier pbm> <nom fichier eps>
```
 - Pour simplifier avec des courbes de bézier 1 :
```
./test_douglas_peucker_bezier1 <PBM> <EPS> <seuil>
```
 - Pour simplifier avec des courbes de bézier 2 :
```
./test_douglas_peucker_bezier2 <PBM> <EPS> <seuil>
```
 - Pour simplifier avec des courbes de bézier 3 :
```
./test_douglas_peucker_bezier3 <PBM> <EPS> <seuil>
```

## Tests annexes

- Pour tester la distance entre les points
```
./test_dist_segment_point <x,y A> <x,y B> <x,y C>
```
- Pour tester l'approximation des beziers 2

```
//Si n = 1

./test_approx2 <1> <P0x> <P0y> <P1x> <P1y>

//Si n >= 2 

./test_approx2 <j1> <j2> <Q0x> <Q0y> <Q1x> <Q1y> <Q2x> <Q2y>   

 //Si n = 8 alors un exemple précis est rempli
```

- Pour tester l'approximation des beziers 3
```
./test_approx3 (memes arguments avec +1 car bezier3)
```
## Crédits

> @Mathis Grange & @Mattéo Decorsaire  : Sauf mention contraire les paquetages sont de notre conception. (LICENSE-MIT)
(Nous contacter si oubli important)
