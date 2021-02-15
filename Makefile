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
EXECUTABLES = test_image test_geom2d test_contour test_eps test_dist_segment_point


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
	@echo "\033[96m Compilation du module \033[0m"$*
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h

test_image.o : test_image.c image.h 
	@echo ""
	@echo "\033[96m Compilation du module \033[0m"$*
	$(CC) -c $(COMPILOPTS) $<

geom2d.o : geom2d.c geom2d.h

test_geom2d.o : test_geom2d.c geom2d.h
	@echo ""
	@echo "\033[96m Compilation du module \033[0m"$*
	$(CC) -c $(COMPILOPTS) $<

structures.o : structures.c structures.h

contour.o : contour.c contour.h image.h eps.h structures.h

test_contour.o : test_contour.c image.h
	@echo ""
	@echo "\033[96m Compilation du module \033[0m"$*
	$(CC) -c $(COMPILOPTS) $<

eps.o : eps.c eps.h contour.h image.h

test_eps.o : test_eps.c eps.h
	@echo ""
	@echo "\033[96m Compilation du module \033[0m"$*
	$(CC) -c $(COMPILOPTS) $<

test_dist_segment_point.o : test_dist_segment_point.c geom2d.h
	@echo ""
	@echo "\033[96m Compilation du module \033[0m"$*
	$(CC) -c $(COMPILOPTS) $<
		
########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "\033[92m Creation de l'executable \033[0m" $@
	$(CC) $^ $(LDOPTS) -o $@

test_geom2d : test_geom2d.o geom2d.o 
	@echo ""
	@echo "\033[92m Creation de l'executable \033[0m" $@
	$(CC) $^ $(LDOPTS) -o $@

test_contour : test_contour.o contour.o image.o eps.o structures.o
	@echo ""
	@echo "\033[92m Creation de l'executable \033[0m" $@
	$(CC) $^ $(LDOPTS) -o $@

test_eps : test_eps.o eps.o contour.o image.o eps.o structures.o
	@echo ""
	@echo "\033[92m Creation de l'executable \033[0m" $@
	$(CC) $^ $(LDOPTS) -o $@

test_dist_segment_point : test_dist_segment_point.o geom2d.o 
	@echo ""
	@echo "\033[92m Creation de l'executable \033[0m" $@
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
