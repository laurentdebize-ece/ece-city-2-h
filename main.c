#include "jeu.h"
#include "affichage.h"
#include "DebutDePartie/debutDePartie.h"


int main() {
    /// Partie Allegro
    srand(time(NULL));
    bool end = false;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;
    /// Police écriture
    ALLEGRO_FONT *roboto = NULL;
    ALLEGRO_FONT *roboto_extra = NULL;
    ALLEGRO_FONT *robotoLabelBouton = NULL;

    //DebutDePartie * debutDePartie;


    /// Déclaration des variables
    int caseDeLaSourisX = 0, caseDeLaSourisY = 0;
    int pos_sourisX, pos_sourisY;
    int sourisSurLePlateau = 0;
    int etage = 0;
    int pause = 0;
    int sauvegarde = 2;
    int choix_communiste = 2;
    int choix_batiment_a_construire = 0;
    int compteur_temps = 0;

    /// Bitmap début de partie
    // bitmapDebutDePartie(debutDePartie);

    Plateau *plateau;
    Bouton bouton_etage[3] = {0};
    Bouton bouton_choix_batiment[5] = {0};
    Bouton bouton_pause;


    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(al_install_keyboard());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_install_mouse());
    assert(al_install_audio());
    assert(al_init_acodec_addon());

    display = al_create_display(LARGEUR, HAUTEUR);
    assert(display != NULL);
    al_set_window_title(display, "ECE City");
    //al_set_window_position(display, 0, 0);

    // Timer
    timer = al_create_timer(1.0 / 10.0);
    if (timer == NULL) {
        al_destroy_display(display);
        exit(EXIT_FAILURE);
    }
    al_start_timer(timer);

    // Queue d'évènements
    queue = al_create_event_queue();
    if (queue == NULL) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(EXIT_FAILURE);
    }
    /// images ////
    ALLEGRO_BITMAP *map = al_load_bitmap("../image/fond/map.png");
    ALLEGRO_BITMAP *menu = al_load_bitmap("../image/DebutDePartie/affichage1.png");


    /// Ecriture
    roboto = al_load_ttf_font("../fonts/roboto/RobotoCondensed-Regular.ttf", 20, 0);
    robotoLabelBouton = al_load_ttf_font("../fonts/roboto/RobotoCondensed-Regular.ttf", 20, 0);
    roboto_extra = al_load_ttf_font("../fonts/roboto/RobotoCondensed-Regular.ttf", 50, 0);

    if (!roboto || !roboto_extra || !robotoLabelBouton) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(EXIT_FAILURE);
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());


    // al_draw_bitmap_region(debutDePartie->debut[0],1024,768,0,0,0,0,0);

    /// début du jeux

    while (!end && sauvegarde == 2) {
        al_wait_for_event(queue, &event);

        switch (event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                end = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if (event.mouse.x > 10 && event.mouse.x < 380) {
                    if (event.mouse.y > 400 && event.mouse.y < 470) {
                        sauvegarde = 0;
                    } else if (event.mouse.y > 510 && event.mouse.y < 580) {
                        sauvegarde = 1;
                    } else if (event.mouse.y > 620 && event.mouse.y < 690) {
                        end = true;
                    }
                }
            }
        }
        al_clear_to_color(al_map_rgb_f(0, 0, 0));
        al_draw_scaled_bitmap(menu, 0, 0, 400, 300, 0, 0, 1024, 768, 0);
        al_draw_rectangle(10, 400, 380, 470, al_map_rgb(255, 0, 0), 3);
        al_draw_rectangle(10, 510, 380, 580, al_map_rgb(255, 0, 0), 3);
        al_draw_rectangle(10, 620, 380, 690, al_map_rgb(255, 0, 0), 3);
        al_flip_display();
    }
    if (sauvegarde == 0) {
        while (!end && choix_communiste == 2) {
            al_wait_for_event(queue, &event);

            switch (event.type) {

                case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                    end = true;
                    break;
                }

                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                    if (event.mouse.x > (LARGEUR / 2 - 200) && event.mouse.x < (LARGEUR / 2 + 200)) {
                        if (event.mouse.y > (HAUTEUR / 2 - 150) && event.mouse.y < (HAUTEUR / 2 - 50)) {
                            choix_communiste = 1;

                        } else if (event.mouse.y > (HAUTEUR / 2 + 50) && event.mouse.y < (HAUTEUR / 2 + 150)) {
                            choix_communiste = 0;
                        }
                    }
                }
            }
            al_clear_to_color(al_map_rgb_f(0, 0, 0));
            al_draw_bitmap(map, 0, 0, 0);
            al_draw_rectangle(LARGEUR / 2 - 200, HAUTEUR / 2 - 150, LARGEUR / 2 + 200, HAUTEUR / 2 - 50,
                              al_map_rgb(255, 0, 0), 3);
            al_draw_textf(roboto_extra, al_map_rgb(0, 0, 0), LARGEUR / 2, HAUTEUR / 2 - 130, ALLEGRO_ALIGN_CENTER,
                          "Mode communiste");
            al_draw_rectangle(LARGEUR / 2 - 200, HAUTEUR / 2 + 50, LARGEUR / 2 + 200, HAUTEUR / 2 + 150,
                              al_map_rgb(255, 0, 0), 3);
            al_draw_textf(roboto_extra, al_map_rgb(0, 0, 0), LARGEUR / 2, HAUTEUR / 2 + 70, ALLEGRO_ALIGN_CENTER,
                          "Mode capitaliste");
            al_flip_display();
        }
    }

    if (sauvegarde != 2) {
        plateau = lire_plateau(sauvegarde);
        if (choix_communiste != 2) {
            plateau->communiste = choix_communiste;
        }
        compteur_temps = plateau->temps_en_seconde * 10;
        initialiser_plateau(plateau);
        initialisation_choix_etage(bouton_etage);
        initialisation_choix_batiment(bouton_choix_batiment);
        initialisation_bouton_pause(&bouton_pause);

        while (!end) {
            al_wait_for_event(queue, &event);

            switch (event.type) {

                case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                    end = true;
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_AXES : {

                    chercherCaseSouris(event.mouse.x, event.mouse.y, &caseDeLaSourisX, &caseDeLaSourisY, plateau,
                                       &sourisSurLePlateau);

                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                    choix_etage(bouton_etage, event.mouse.x, event.mouse.y, &etage);
                    choix_pause(&bouton_pause, event.mouse.x, event.mouse.y, &pause);
                    if (etage == 0) {
                        choix_batiment(bouton_choix_batiment, event.mouse.x, event.mouse.y,
                                       &choix_batiment_a_construire);
                        construire_batiment(plateau, choix_batiment_a_construire, sourisSurLePlateau, caseDeLaSourisX,
                                            caseDeLaSourisY);
                    } else {
                        choix_batiment_a_construire = 0;
                    }
                    break;
                }
                case ALLEGRO_EVENT_TIMER : {
                    if (pause != 1) {
                        if (plateau->temps_en_seconde * 10 == compteur_temps) {
                            evolution_maison(plateau);
                        }
                        gain_d_argent(plateau);
                        compteur_temps++;
                    }

                    break;
                }

            }
            plateau->temps_en_seconde = compteur_temps / 10;
            dessiner_tout(plateau, etage, pause, choix_batiment_a_construire, caseDeLaSourisX,
                          caseDeLaSourisY, sourisSurLePlateau, bouton_etage, bouton_choix_batiment, &bouton_pause,
                          roboto,
                          robotoLabelBouton, map);
        }
        sauvegarde_jeu(plateau);

        for (int i = 0; i < plateau->nb_ligne; i++) {
            free(plateau->map[i]);
        }
        free(plateau->map);

        free(plateau->tab_de_maison);

        for (int i = 0; i < plateau->nb_chateau_eau; i++) {
            free(plateau->tab_chateau_eau[i].tab_des_maisons_alimentee);
        }
        free(plateau->tab_chateau_eau);

        for (int i = 0; i < plateau->nb_centrale_elec; i++) {
            free(plateau->tab_centrale_elec[i].tab_des_maisons_alimentee);
        }
        free(plateau->tab_centrale_elec);

        for (int i = 0; i < plateau->nb_stade_different; i++) {
            al_destroy_bitmap(plateau->tab_des_different_stade_possible[i].image_du_stade_correspondant);
        }
        free(plateau->tab_des_different_stade_possible);

        for (int i = 0; i < 2; i++) {
            al_destroy_bitmap(plateau->tab_dessin_ressource[i].image_du_batiment);
        }
        free(plateau->tab_dessin_ressource);

        free(plateau->tab_des_prix);

        for (int i = 0; i < 12; i++) {
            al_destroy_bitmap(plateau->image_affichage[i]);
        }
        free(plateau);
    }


    al_destroy_bitmap(map);
    al_destroy_bitmap(menu);
    al_destroy_font(roboto);
    al_destroy_font(roboto_extra);
    al_destroy_font(robotoLabelBouton);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}


