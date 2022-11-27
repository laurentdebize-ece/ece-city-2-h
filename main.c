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
    ALLEGRO_MOUSE_STATE mouse;
    //DebutDePartie * debutDePartie;


    /// Déclaration des variables
    int caseDeLaSourisX = 0, caseDeLaSourisY = 0;
    int sourisSurLePlateau = 0;
    int etage = 0;
    int pause = 0;
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


    /// Ecriture
    roboto = al_load_ttf_font("../fonts/roboto/RobotoCondensed-Regular.ttf", 20, 0);
    ALLEGRO_FONT *robotoLabelBouton = al_load_ttf_font("../fonts/roboto/RobotoCondensed-Regular.ttf", 20, 0);
    if (!roboto) {
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
    plateau = lire_plateau(0);
    plateau->communiste = 1;
    compteur_temps = plateau->temps_en_seconde * 10;
    initialiser_plateau(plateau);
    initialisation_choix_etage(bouton_etage);
    initialisation_choix_batiment(bouton_choix_batiment);
    initialisation_bouton_pause(&bouton_pause);
    /*
    while (!end) {
        al_wait_for_event(queue, &event);

        switch (event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                end = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES : {
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:{
                al_get_mouse_state(&mouse);
                printf("x : %d\ny : %d\n", mouse.x, mouse.y);
            }
        }
    }*/


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
                    choix_batiment(bouton_choix_batiment, event.mouse.x, event.mouse.y, &choix_batiment_a_construire);
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
                      caseDeLaSourisY, sourisSurLePlateau, bouton_etage, bouton_choix_batiment, &bouton_pause, roboto,
                      robotoLabelBouton, map);
    }
    //sauvegarde_jeu(plateau);


    for (int i = 0; i < plateau->nb_ligne; i++) {
        free(plateau->map[i]);
    }
    free(plateau->map);
    free(plateau->tab_de_maison);
    for (int i = 0; i < plateau->nb_chateau_eau; i++) {
        free(plateau->tab_chateau_eau[i].tab_des_maisons_alimentee);
        al_destroy_bitmap(plateau->tab_chateau_eau[i].image_batiment);
    }
    free(plateau->tab_chateau_eau);
    for (int i = 0; i < plateau->nb_centrale_elec; i++) {
        free(plateau->tab_centrale_elec[i].tab_des_maisons_alimentee);
        al_destroy_bitmap(plateau->tab_centrale_elec[i].image_batiment);
    }

    free(plateau->tab_centrale_elec);
    free(plateau->tab_des_different_stade_possible);
    free(plateau->tab_dessin_ressource);
    free(plateau->tab_des_prix);
    for (int i = 0; i < 12; i++) {
        al_destroy_bitmap(plateau->image_affichage[i]);
    }
    free(plateau);

    al_destroy_bitmap(map);
    al_destroy_font(roboto);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}


