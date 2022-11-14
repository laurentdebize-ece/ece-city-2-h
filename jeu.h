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
#define HAUTEUR 600

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
    int etat;
} Case;

typedef  struct Maison {
    ALLEGRO_BITMAP *image_stade_batiment[6];
    int largeur,hauteur;
    int date_creation;
    int caseX, caseY;
    int nb_habitant;
    int eau_utilise;
    int elec_utilise;
    int stade;
    int viable;
}Maison;

typedef  struct Maison_alimentee {
    int numero_maison;
    int quantite;
}Maison_alimentee;

typedef  struct Ressource {
    ALLEGRO_BITMAP *image_batiment[2];
    int type;
    int largeur,hauteur;
    int caseX, caseY;
    int capacite_max;
    int capacite_utilisee;
    int nb_maison_alimentee;
    Maison_alimentee* tab_des_maisons_alimentee;
}Ressource;

typedef struct Plateau {
    int largeur_case;
    int nb_ligne;
    int nb_colonne;
    Case **map;
    int nb_stade_different;
    int* tab_nb_habitant_pour_chaque_stade_de_maison;
    int nb_maison;
    Maison* tab_de_maison;
    int nb_chateau_eau;
    Ressource *tab_chateau_eau;
    int nb_centrale_elec;
    Ressource* tab_centrale_elec;
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
void crer_un_chateau_eau(Plateau* plateau,int caseX,int caseY);
void construire_centrale_elec(Plateau* plateau,int caseX,int caseY);
void crer_une_centrale_elec(Plateau *plateau, int caseX, int caseY);

/////////      evolution maison       ///////////
void evolution_maison(Plateau* plateau,int timer);

/////////      viabilté maison       ///////////
void verifier_viabilite_pour_les_maison_non_viable(Plateau* plateau);
int verifier_viabilite_maison(Plateau* plateau,int caseX,int caseY);
void chercher_eau_et_electicite(Plateau* plateau,int caseX,int caseY,int* connecte_a_eau,int* connecte_a_elec);

/////////      alimentation en eau       ///////////
int verifier_si_assez_d_eau_disponible(Plateau *plateau, int numero_de_la_maison, int quantite_eau_necesaire);
void chercher_une_maison_en_particulier(Plateau* plateau,int caseX,int caseY, int numero_de_la_maison,int*maison_trouve);
void alimentation_en_eau(Plateau *plateau);
void chercher_maison_la_plus_proche_qui_a_besoin_d_eau(Plateau *plateau, int caseX, int caseY, int *numero_maison_numero,
                                    int *plus_petite_distance, int distance);

/////////      alimentation en elec       ///////////
int verifier_si_assez_d_elec_disponible_dans_une_centrale(Plateau *plateau, int numero_de_la_maison, int quantite_elec_necesaire);
void alimentation_en_elec(Plateau *plateau);
void chercher_maison_qui_a_besoin_d_elec(Plateau *plateau, int caseX, int caseY, int *numero_maison_trouve,int num_centrale_elec);

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
