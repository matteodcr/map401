#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geom2d test_calcul_contour test_creation_eps


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geom2d.o : geom2d.c geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_geom2d.o : test_geom2d.c geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

eps.o : eps.c calcul_contour.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

calcul_contour.o : calcul_contour.c calcul_contour.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_calcul_contour.o : test_calcul_contour.c calcul_contour.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_calcul_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_creation_eps.o : test_creation_eps.c calcul_contour.h image.h eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_creation_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
		
########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable" $@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geom2d : test_geom2d.o geom2d.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable" $@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_calcul_contour : test_calcul_contour.o calcul_contour.o image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable" $@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_creation_eps : test_creation_eps.o calcul_contour.o image.o eps.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable" $@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@



# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
