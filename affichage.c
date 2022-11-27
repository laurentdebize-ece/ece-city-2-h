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
