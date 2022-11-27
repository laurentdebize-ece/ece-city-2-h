#ifndef ECE_CITY_2_H_AFFICHAGE_H
#define ECE_CITY_2_H_AFFICHAGE_H

#include "jeu.h"

void dessinerBoutonEtage(Bouton bouton, int etage, int i, Plateau *plateau, ALLEGRO_FONT *font);

void dessinerBoutonBatiment(Bouton bouton_batiment, int choix_batiment, int i, Plateau *plateau);


/////////     afficher eau totale    ///////////
void afficher_rapport_sur_eau_total(Plateau *plateau, ALLEGRO_FONT *roboto);

/////////     afficher electricite totale    ///////////
void afficher_rapport_sur_electricite_total(Plateau *plateau, ALLEGRO_FONT *roboto);

/////////     afficher timer      ///////////
void afficher_timer(int timer, ALLEGRO_FONT *roboto);

/////////     afficher argent      ///////////
void afficher_compte_en_banque(Plateau *plateau, ALLEGRO_FONT *roboto);

/////////     afficher nb habitant      ///////////
void afficher_nb_habitant(Plateau *plateau, ALLEGRO_FONT *roboto);

#endif //ECE_CITY_2_H_AFFICHAGE_H
