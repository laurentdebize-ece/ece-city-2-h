#include "jeu.h"


int main() {
    /// Partie Allegro
    srand(time(NULL));
    bool end = FALSE;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;
    /// Police écriture
    ALLEGRO_FONT *roboto = NULL;


    /// Déclaration des variables
    int caseDeLaSourisX = 0, caseDeLaSourisY = 0;
    int sourisSurLePlateau = 0;
    int etage = 0;
    int choix_batiment_a_construire = 0;
    int compteur_temps = 0;


    Plateau *plateau;
    Bouton bouton_etage[3] = {0};
    Bouton bouton_choix_batiment[4] = {0};


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
    al_set_window_position(display, 0, 0);

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

    /// Ecriture
    roboto = al_load_ttf_font("../fonts/roboto/RobotoCondensed-Regular.ttf", 30, 0);
    if (!roboto) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(EXIT_FAILURE);
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    /// début du jeux
    plateau = lire_plateau(0);
    compteur_temps = plateau->temps_en_seconde * 10;
    initialiser_plateau(plateau);
    initialisation_choix_etage(bouton_etage);
    initialisation_choix_batiment(bouton_choix_batiment);

    while (!end) {
        al_wait_for_event(queue, &event);

        switch (event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                end = TRUE;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES : {

                chercherCaseDeLaSourie(event.mouse.x, event.mouse.y, &caseDeLaSourisX,
                                       &caseDeLaSourisY, &sourisSurLePlateau, plateau);

                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                choix_etage(bouton_etage, event.mouse.x, event.mouse.y, &etage);
                if (etage==0){
                    choix_batiment(bouton_choix_batiment, event.mouse.x, event.mouse.y, &choix_batiment_a_construire);
                    construire_batiment(plateau,choix_batiment_a_construire,souris_sur_le_plateau,caseDeLaSourieX,caseDeLaSourieY);
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER : {
                if (plateau->temps_en_seconde * 10 == compteur_temps) {
                    evolution_maison(plateau);
                }
                gain_d_argent(plateau);
                compteur_temps++;

                break;
            }

        }
        plateau->temps_en_seconde = compteur_temps / 10;
        dessiner_tout(plateau, etage, choix_batiment_a_construire, caseDeLaSourisX,
                      caseDeLaSourisY, sourisSurLePlateau, bouton_etage, bouton_choix_batiment, roboto);
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
    free(plateau->tab_nb_habitant_pour_chaque_stade_de_maison);
    free(plateau->tab_des_prix);
    free(plateau);

    al_destroy_font(roboto);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}


