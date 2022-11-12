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
typedef struct Bouton {
    int nb_bouton;
    int x, y;
    float largeur, hauteur;
} Bouton;


typedef struct {
    int x;
    int y;
    int largeur;
    int etat;
} Case;

typedef  struct Maison {
    ALLEGRO_BITMAP *image_satde_batiment[6];
    int largeur,hauteur;
    int date_creation;
    int caseX, caseY;
    int stade;
    int viable;
}Maison;

typedef struct Plateau {
    int largeur_case;
    int nb_ligne;
    int nb_colonne;
    Case **map;
    int nb_maison;
    Maison* tab_de_maison;
} Plateau;



/////////      plateau        ///////////
Plateau *creer_plateau(int nb_ligne, int nb_colonne);
Plateau *lire_plateau();
void initialiser_plateau(Plateau *plateau);
void dessiner_plateau(Plateau *plateau);


/////////      choix etage        ///////////
void initialisation_choix_etage(Bouton *bouton);
void choix_etage(Bouton bouton[], int x, int y, int *etage);

/////////      choix batiment        ///////////
void initialisation_choix_batiment(Bouton *bouton);
void choix_batiment(Bouton bouton[], int x, int y, int *batiment);

/////////      construire batiment       ///////////
void construire_batiment(Plateau* plateau,int choix_batiment,int souris_sur_le_plateau,int caseX,int caseY,int timer);
void construire_route(Plateau* plateau,int caseX,int caseY);
void construire_maison(Plateau* plateau,int caseX,int caseY,int timer);
void crer_une_maison(Plateau* plateau,int caseX,int caseY,int timer);
void construire_chateau_eau(Plateau* plateau,int caseX,int caseY);
void construire_centrale_elec(Plateau* plateau,int caseX,int caseY);

/////////      viabilté maison       ///////////
void verifier_viabilite_pour_les_maison_non_viable(Plateau* plateau);
int verifier_viabilite_maison(Plateau* plateau,int caseX,int caseY);
void chercher_eau_et_electicite(Plateau* plateau,int caseX,int caseY,int* connecte_a_eau,int* connecte_a_elec);

/////////      emplacement souris       ///////////
void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY,int*souris_sur_le_plateaux,Plateau* plateau);

/////////     timer      ///////////
void afficher_timer(int timer, ALLEGRO_FONT *roboto);

/////////     dessiner batiment      ///////////
void dessiner_batiment(Plateau *plateau, int etage);
void dessiner_etage_0(Plateau *plateau);
void dessiner_etage_1(Plateau *plateau);
void dessiner_etage_2(Plateau *plateau);

/////////     dessiner tout     ///////////
void dessiner_tout(Plateau *plateau, int etage,int choix_batiment, int caseDeLaSourieX,
                   int caseDeLaSourieY,int souris_sur_le_plateaux,Bouton bouton[],Bouton bouton_batiment[],ALLEGRO_FONT *roboto,int compteur);

/////////     sauvegarde jeu     ///////////
void sauvegarde_jeu(Plateau *plateau);

#endif //ECE_CITY_2_H_JEU_H
