/****************************************************************************** 
  Impl�mentation du module image_pbm
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"

/* macro donnant l'indice d'un pixel de coordonn�es (_x,_y) de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).L*((_y)-1)

/* cr�ation d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H)
{
	Image I;
	UINT i;
	
	I.L = L;
	I.H = H;
	
	/* alloctaion dynamique d'un tableau de L*H Pixel*/
	I.tab = (Pixel *)malloc(sizeof(Pixel)*L*H);
	
	/* test si le tableau a ete correctement alloue */
	if (I.tab == (Pixel *)NULL)
	{
		ERREUR_FATALE("Impossible de creer une image");
	}
	
	/* remplir le tableau avec des pixels blancs */
	for (i=0; i<L*H; i++)
		I.tab[i] = BLANC;
		
	return I;
}

/* suppression de l'image I = *p_I*/
void supprimer_image(Image *p_I)
{
	free(p_I->tab);
	p_I->L = 0;
	p_I->H = 0;
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, int x, int y)
{
	if (x<1 || x>I.L || y<1 || y>I.H)
		return BLANC;
	return I.tab[INDICE_PIXEL(I,x,y)];
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, int x, int y, Pixel v)
{
	if (x<1 || x>I.L || y<1 || y>I.H)
		return;
	I.tab[INDICE_PIXEL(I,x,y)] = v;
}

/* renvoie la largeur de l'image I */
UINT largeur_image(Image I)
{
	return I.L;
}

/* renvoie la hauteur de l'image I */
UINT hauteur_image(Image I)
{
	return I.H;
}

/* teste si le fichier d'identificateur f debute par un en-tete
   valide pour un fichier PBM :
   - ligne 1 : P1
   - suivie de zero, une ou plusieurs lignes commen�ant toutes par #
   La fonction se termine correctement si le fichier est correct, 
   et le pointeur de fichier se trouve � la suite l'entete.
   Sinon, l'ex�cution du programme est arretee avec l'affichage d'un message
   d'erreur (appel � ERREUR_FATALE)
    */ 
void entete_fichier_pbm(FILE *f)
{
	char *ligne;
	size_t n;
	size_t l_ligne;

	/* se positionner en debut de fichier */
	fseek(f, 0, SEEK_SET);
	
	/* lecture et test de la ligne 1 */
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	
	/* la ligne est correcte si et ssi ligne = {'P','1',0} 
	  soit une chaine de 3 caracteres (le dernier est le caractere nul) */
	if (l_ligne != 3)
	{
		ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1'))
	{
		ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
	}
	free(ligne);
	
	/* lecture des �ventuelles lignes commen�ant par # */
	bool boucle_ligne_commentaire = true;
	do
	{
		/* tester d'abord la fin de fichier */
		if (feof(f))
		{
			ERREUR_FATALE("entete_fichier_pbm : fin fichier inattendue\n");
		}
		
		/* lire un caractere et tester par rapport � '#' */
		char c;
		fscanf(f, "%c", &c);
		if (c=='#')
		{
			/* lire le reste de la ligne */
			ligne = (char *)NULL;
			n = 0;
			l_ligne = getline(&ligne, &n, f);
			free(ligne);
		}
		else
		{
			/* reculer d'un caract�re dans f */
			fseek(f, -1, SEEK_CUR);
			boucle_ligne_commentaire = false;
		}
	} while (boucle_ligne_commentaire);
	
}
  
/* lire l'image dans le fichier nomm� nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message */
Image lire_fichier_image(char *nom_f)
{
	FILE *f;
	UINT L,H;
	Image I;
	
	/* ouverture du fichier nom_f en lecture */
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
	}
	
	/* traitement de l'en-tete et arret en cas d'erreur */
	entete_fichier_pbm(f);
	
	/* lecture des dimensions - lecture de 2 entiers */
    fscanf(f, "%d %d", &L, &H);
	
	/* cr�ation de l'image I de dimensions L x H */
	
	I = creer_image(L, H);
	
	
	/* lecture des pixels du fichier - lecture caract�re par caract�re
	   seuls les caracteres '0' (BLANC) ou '1' (NOIR) 
	   doivent etre pris en compte */
	char c;
    int x, y, a;
	for(y=1; y<=H; y++){
		for(x=1; x<=L; x++){
			fscanf(f, "%c", &c);
			if (c == '0' || c == '1'){
				a = atoi(&c);
				set_pixel_image(I,x,y,a);	
			} else {
				x--;
			}
		}
    }
	/* fermeture du fichier */
	fclose(f);
	
	return I;
}

Image lire_fichier_image_inverse(char *nom_f){
	FILE *f;
	UINT L,H;
	Image I;
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("lire_fichier_image_inverse : ouverture du fichier impossible\n");
	}
	
	entete_fichier_pbm(f);
    fscanf(f, "%d %d", &L, &H);
	I = creer_image(L, H);
	
	char c;
    int x, y, a;
	for(y=1; y<=H; y++){
		for(x=1; x<=L; x++){
			fscanf(f, "%c", &c);
			if (c == '0' || c == '1'){
				a = atoi(&c);
				set_pixel_image(I,x,H-y+1,a);	
			} else {
				x--;
			}
		}
    }
	fclose(f);	
	return I;
}

Image initialiser_image_blanche(Image I){
    Image Ib;
	Ib = creer_image(I.L, I.H);
	
    int x, y;
	for(y=1; y<=I.H; y++){
		for(x=1; x<=I.L; x++){
			set_pixel_image(Ib,x,y,BLANC);	
		}
    }
	return Ib;
}

Image creer_image_masque(Image I){
	Image Im = initialiser_image_blanche(I);

	int x, y;
	for(y=1; y<=I.H; y++){
		for(x=1; x<=I.L; x++){
			if (get_pixel_image(I, x, y)==NOIR 
			&& get_pixel_image(I, x, y-1)==BLANC){
				set_pixel_image(Im,x,y,NOIR);
			}
				
		}
    }
	return Im;
}

/* �crire l'image I � l'�cran */
void ecrire_image(Image I)
{
    for(int i=1; i<=I.H; i++){
        for(int j=1; j<=I.L; j++){
            if (get_pixel_image(I, j, i) == NOIR){
                putc('#', stdout);
            } else {
                putc('.', stdout);
            }
        }
        putc('\n', stdout);
    }
}

