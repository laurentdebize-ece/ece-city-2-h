#include "affichage.h"

// affichage boutons étages
void dessinerBoutonEtage(Bouton bouton, int etage, int i, Plateau *plateau, ALLEGRO_FONT *font) {

    ALLEGRO_COLOR buttonBackgroundColor = al_map_rgb(180, 180, 180);
    ALLEGRO_COLOR buttonBackgroundColorDark = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR buttonClickedColor = al_map_rgb(140, 120, 20);
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR color;

    al_draw_filled_rounded_rectangle(bouton.x - 5, bouton.y + 5,
                                     bouton.x + bouton.largeur - 5,
                                     bouton.y + bouton.hauteur + 5,
                                     10, 10, buttonBackgroundColorDark);

    // si le bouton est cliqué
    if (i == etage) {
        color = buttonClickedColor;
    } else {
        color = buttonBackgroundColor;
    }

    al_draw_filled_rounded_rectangle(bouton.x, bouton.y,
                                     bouton.x + bouton.largeur,
                                     bouton.y + bouton.hauteur,
                                     10, 10, color);

    al_draw_bitmap(plateau->image_affichage[i + 9], bouton.x + 4, bouton.y + 4, 0);

    al_draw_textf(font, black, bouton.x + 60, bouton.y + 8, ALLEGRO_ALIGN_CENTER, "%s", bouton.label);

}

// affichage des boutons de la boite a outil
void dessinerBoutonBatiment(Bouton bouton_batiment, int choix_batiment, int i, Plateau *plateau) {

    ALLEGRO_COLOR buttonBackgroundColor = al_map_rgb(180, 180, 180);
    ALLEGRO_COLOR buttonBackgroundColorDark = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR buttonClickedColor = al_map_rgb(179, 0, 134);
    ALLEGRO_COLOR color;

    al_draw_filled_rounded_rectangle(bouton_batiment.x - 5, bouton_batiment.y + 5,
                                     bouton_batiment.x + bouton_batiment.largeur - 5,
                                     bouton_batiment.y + bouton_batiment.hauteur + 5,
                                     10, 10, buttonBackgroundColorDark);
    // si le bouton est cliqué
    if (i == choix_batiment - 1) {
        color = buttonClickedColor;
    } else {
        color = buttonBackgroundColor;
    }

    al_draw_filled_rounded_rectangle(bouton_batiment.x, bouton_batiment.y,
                                     bouton_batiment.x + bouton_batiment.largeur,
                                     bouton_batiment.y + bouton_batiment.hauteur,
                                     10, 10, color);

    al_draw_bitmap(plateau->image_affichage[i + 4], bouton_batiment.x + 4, bouton_batiment.y + 4, 0);
}


/////////     afficher eau totale    ///////////
void afficher_rapport_sur_eau_total(Plateau *plateau, ALLEGRO_FONT *roboto) {
    float capacite_totale_en_eau = 0;
    float capacite_utilise_en_eau = 0;
    for (int i = 0; i < plateau->nb_chateau_eau; i++) {
        capacite_totale_en_eau += plateau->tab_chateau_eau[i].capacite_max;
        capacite_utilise_en_eau += plateau->tab_chateau_eau[i].capacite_utilisee;
    }

    al_draw_bitmap(plateau->image_affichage[0], 500, 8, 0);


    if (capacite_totale_en_eau != 0) {
        al_draw_filled_rectangle(530, 10, 530 + 240 * (capacite_utilise_en_eau / capacite_totale_en_eau), 10 + 20,
                                 al_map_rgb(97, 167, 216));
    }
    al_draw_rectangle(530, 10, 530 + 240, 10 + 20, al_map_rgb(0, 0, 0), 2);
    al_draw_textf(roboto, al_map_rgb(0, 0, 0), 530 + 240 / 2, 10 - 2, ALLEGRO_ALIGN_CENTER, "%.0f/%.0f",
                  capacite_utilise_en_eau, capacite_totale_en_eau);
}

/////////     afficher electricite totale    ///////////
void afficher_rapport_sur_electricite_total(Plateau *plateau, ALLEGRO_FONT *roboto) {
    float capacite_totale_en_elec = 0;
    float capacite_utilise_en_elec = 0;
    for (int i = 0; i < plateau->nb_centrale_elec; i++) {
        capacite_totale_en_elec += plateau->tab_centrale_elec[i].capacite_max;
        capacite_utilise_en_elec += plateau->tab_centrale_elec[i].capacite_utilisee;
    }

    al_draw_bitmap(plateau->image_affichage[1], 500, 38, 0);

    if (capacite_totale_en_elec != 0) {
        al_draw_filled_rectangle(530, 40, 530 + 240 * (capacite_utilise_en_elec / capacite_totale_en_elec), 20 + 40,
                                 al_map_rgb(255, 213, 79));
    }
    al_draw_rectangle(530, 40, 530 + 240, 20 + 40, al_map_rgb(0, 0, 0), 2);
    al_draw_textf(roboto, al_map_rgb(0, 0, 0), 530 + 240 / 2, 40 - 2, ALLEGRO_ALIGN_CENTER, "%.0f/%.0f",
                  capacite_utilise_en_elec, capacite_totale_en_elec);
}

/////////     afficher timer      ///////////
void afficher_timer(int timer, ALLEGRO_FONT *roboto) {

    //al_draw_filled_rectangle();
    al_draw_textf(roboto, al_map_rgb(0, 0, 0), 50, 10, ALLEGRO_ALIGN_RIGHT, "%ds", timer);
}

/////////     afficher argent      ///////////
void afficher_compte_en_banque(Plateau *plateau, ALLEGRO_FONT *roboto) {
    al_draw_bitmap(plateau->image_affichage[3], LARGEUR - 130, 8, 0);

    al_draw_textf(roboto, al_map_rgb(0, 0, 0), LARGEUR - 100, 10 - 2, ALLEGRO_ALIGN_LEFT, "%d",
                  plateau->compte_en_banque);
}

/////////     afficher nb habitant     ///////////
void afficher_nb_habitant(Plateau *plateau, ALLEGRO_FONT *roboto) {
    int nb_habitant = 0;
    for (int i = 0; i < plateau->nb_maison; i++) {
        nb_habitant += plateau->tab_de_maison[i].nb_habitant;
    }

    al_draw_bitmap(plateau->image_affichage[2], LARGEUR - 130, 38, 0);

    al_draw_textf(roboto, al_map_rgb(0, 0, 0), LARGEUR - 100, 40 - 2, ALLEGRO_ALIGN_LEFT, "%d",
                  nb_habitant);
}
