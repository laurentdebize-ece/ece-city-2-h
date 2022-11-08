#ifndef ECE_CITY_2_H_JEU_H
#define ECE_CITY_2_H_JEU_H


/////  bibliothèque
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/////   macro
#define LARGEUR 1024
#define HAUTEUR 768

#define NB_COLONNES 45
#define NB_LIGNES 35
#define LARGEUR_CASE 20

/////structures
typedef struct {
    int x;
    int y;
    int largeur;
    int etat;
} Case;

typedef struct Graphe {
    int largeur_case;
    int nb_ligne;
    int nb_colonne;
    Case **map;
} Plateau;

/////fonction

/////plateau
Plateau *creer_plateau(int nb_ligne, int nb_colonne);
Plateau *lire_plateau();
void initialiser_plateau(Plateau *plateau);
void dessiner_plateau(Plateau *plateau);


/////dessiner tout
void dessiner_tout(Plateau *plateau);


#endif //ECE_CITY_2_H_JEU_H