#include "jeu.h"


int main() {
    /// PARTE ALLEGRO
    srand(time(NULL));
    bool end = FALSE;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;
    /// ecriture
    ALLEGRO_FONT *roboto = NULL;


    /// declaration des variables
    int caseDeLaSourieX = 0, caseDeLaSourieY = 0;
    int souris_sur_le_plateaux=0;
    int etage=0;
    int choix_batiment_a_construire=0;
    int compteur_temps=0;

    Plateau * plateau;
    Bouton bouton_etage[3] = {0};
    Bouton bouton_choix_batiment[2]={0};


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
    al_set_window_title(display, "ECE-city");
    al_set_window_position(display, 0, 0);
    timer = al_create_timer(1.0/10.0);
    if (timer == NULL) {
        al_destroy_display(display);
        exit(EXIT_FAILURE);
    }
    al_start_timer(timer);
    queue = al_create_event_queue();
    if (queue == NULL) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(EXIT_FAILURE);
    }

    /// ecriture
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

    /// debut du jeux

    plateau = lire_plateau();
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
                /*
                if((((event.mouse.x<=plateau->map[caseDeLaSourieY][caseDeLaSourieX].x || event.mouse.x>=(plateau->map[caseDeLaSourieY][caseDeLaSourieX].x+plateau->largeur_case))) || ((event.mouse.y<=plateau->map[caseDeLaSourieY][caseDeLaSourieX].y || event.mouse.y>=(plateau->map[caseDeLaSourieY][caseDeLaSourieX].y+plateau->largeur_case)))) || souris_sur_le_plateaux==0){
                    chercherCaseDeLaSourie(event.mouse.x, event.mouse.y, &caseDeLaSourieX,
                                            &caseDeLaSourieY,&souris_sur_le_plateaux,plateau);
                }*/

                 chercherCaseDeLaSourie(event.mouse.x, event.mouse.y, &caseDeLaSourieX,
                                       &caseDeLaSourieY,&souris_sur_le_plateaux,plateau);

                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                choix_etage(bouton_etage, event.mouse.x, event.mouse.y, &etage);
                choix_batiment(bouton_choix_batiment, event.mouse.x, event.mouse.y, &choix_batiment_a_construire);
                break;
            }
            case ALLEGRO_EVENT_TIMER : {
                compteur_temps++;
                break;
            }

        }
        dessiner_tout(plateau,etage,choix_batiment_a_construire, caseDeLaSourieX,
                      caseDeLaSourieY,souris_sur_le_plateaux,bouton_etage,bouton_choix_batiment,roboto,compteur_temps);

    }
    sauvegarde_jeu(plateau);
    for(int i=0; i<plateau->nb_ligne;i++){
        free(plateau->map[i]);
    }
    free(plateau->map);

    al_destroy_font(roboto);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}


