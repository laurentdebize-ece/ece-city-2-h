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


/////structures
typedef struct Bouton {
    int nb_bouton;
    int x, y, largeur, hauteur;
    char *label;
    int hover;
} Bouton;


typedef struct {
    int x;
    int y;
    int etat;
} Case;
typedef struct Stade {
    int nb_habitant;
    ALLEGRO_BITMAP *image_du_stade_correspondant;
    int largeur_du_batiment, hauteur_du_batiment;
} Stade;

typedef struct Maison {
    ALLEGRO_BITMAP *image_batiment;
    int largeur, hauteur;
    int date_creation;
    int caseX, caseY;
    int nb_habitant;
    int eau_utilise;
    int elec_utilise;
    int stade;
    int viable;
} Maison;

typedef struct Maison_alimentee {
    int numero_maison;
    int quantite;
} Maison_alimentee;

typedef struct Batiment_pour_ressource_dessin {
    ALLEGRO_BITMAP *image_du_batiment;
    int largeur_du_batiment, hauteur_du_batiment;
} Batiment_pour_ressource_dessin;

typedef struct Ressource {
    ALLEGRO_BITMAP *image_batiment;
    int largeur, hauteur;
    int caseX, caseY;
    int caseX_haut_gauche, caseY_haut_gauche;
    int caseX_droite_bas, caseY_droite_bas;
    int capacite_max;
    int capacite_utilisee;
    int nb_maison_alimentee;
    Maison_alimentee *tab_des_maisons_alimentee;
} Ressource;

typedef struct Plateau {
    ALLEGRO_BITMAP *image_affichage[12];
    ALLEGRO_BITMAP *image_routes[16];
    int largeur_case;
    int nb_ligne;
    int nb_colonne;
    int communiste;
    int temps_en_seconde;
    int compte_en_banque;
    int *tab_des_prix;
    Case **map;
    int nb_stade_different;
    Stade *tab_des_different_stade_possible;
    int nb_maison;
    Maison *tab_de_maison;
    Batiment_pour_ressource_dessin *tab_dessin_ressource;
    int nb_chateau_eau;
    Ressource *tab_chateau_eau;
    int nb_centrale_elec;
    Ressource *tab_centrale_elec;
} Plateau;

typedef struct DebutDePartie {
    ALLEGRO_BITMAP *debut[5];
    int spriteX, spriteY, spriteHauteur, spriteLargeur;
} DebutDePartie;

/////////      plateau        ///////////
Plateau *creer_plateau(int nb_ligne, int nb_colonne);

Plateau *lire_plateau(int charger_sauvegarde);

void lire_prix_et_stade(Plateau *plateau);

void initialiser_plateau(Plateau *plateau);


/////////      choix etage        ///////////
void initialisation_choix_etage(Bouton *bouton);

void choix_etage(Bouton bouton[], int x, int y, int *etage);

/////////      choix batiment        ///////////
void initialisation_choix_batiment(Bouton *bouton);

void choix_batiment(Bouton bouton[], int x, int y, int *batiment);

/////////      construire batiment       ///////////
void construire_batiment(Plateau *plateau, int choix_batiment, int souris_sur_le_plateau, int caseX, int caseY);

void construire_route(Plateau *plateau, int caseX, int caseY);

void construire_maison(Plateau *plateau, int caseX, int caseY);

void crer_une_maison(Plateau *plateau, int caseX, int caseY);

void construire_chateau_eau(Plateau *plateau, int caseX, int caseY);

void crer_un_chateau_eau(Plateau *plateau, int caseX, int caseY);

void construire_centrale_elec(Plateau *plateau, int caseX, int caseY);

void crer_une_centrale_elec(Plateau *plateau, int caseX, int caseY);

/////////      detruire      ///////////
void detruire(Plateau *plateau, int caseX, int caseY);

void detruire_une_route(Plateau *plateau, int caseX, int caseY);

void detruire_une_maison(Plateau *plateau, int caseX, int caseY);

void detruire_un_chateau_d_eau(Plateau *plateau, int caseX, int caseY);

void detruire_une_centrale_electrique(Plateau *plateau, int caseX, int caseY);

/////////      evolution maison       ///////////
void evolution_maison(Plateau *plateau);

/////////      viabilté maison       ///////////
void verifier_viabilite_pour_les_maison_non_viable(Plateau *plateau);

int verifier_viabilite_maison(Plateau *plateau, int caseX, int caseY);

void chercher_eau_et_electicite(Plateau *plateau, int caseX, int caseY, int *connecte_a_eau, int *connecte_a_elec);

/////////      alimentation en eau       ///////////
int verifier_si_assez_d_eau_disponible(Plateau *plateau, int numero_de_la_maison, int quantite_eau_necesaire);

void
chercher_une_maison_en_particulier(Plateau *plateau, int caseX, int caseY, int numero_de_la_maison, int *maison_trouve);

void alimentation_en_eau(Plateau *plateau);

void
chercher_maison_la_plus_proche_qui_a_besoin_d_eau(Plateau *plateau, int caseX, int caseY, int *numero_maison_numero,
                                                  int *plus_petite_distance, int distance);

/////////      alimentation en elec       ///////////
int verifier_si_assez_d_elec_disponible_dans_une_centrale(Plateau *plateau, int numero_de_la_maison,
                                                          int quantite_elec_necesaire);

void alimentation_en_elec(Plateau *plateau);

void chercher_maison_qui_a_besoin_d_elec(Plateau *plateau, int caseX, int caseY, int *numero_maison_trouve,
                                         int num_centrale_elec);

/////////      gain d'argent      ///////////
void gain_d_argent(Plateau *plateau);

/////////      emplacement souris       ///////////
void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, int *souris_sur_le_plateaux, Plateau *plateau);

void chercherCaseSouris(int x, int y, int *caseX, int *caseY, Plateau *plateau, int *sourisSurLePlateau);

/////////      menu pause         ///////////
void initialisation_bouton_pause(Bouton *bouton);

void choix_pause(Bouton bouton[], int x, int y, int *pause);


/////////     sauvegarde jeu     ///////////
void sauvegarde_jeu(Plateau *plateau);

void charger_la_sauvegarde(Plateau *plateau);


#endif //ECE_CITY_2_H_JEU_H
