#include "jeu.h"


int main() {
    /// PARTE ALLEGRO
    srand(time(NULL));
    bool end = FALSE;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;


    /// declaration des variables

    Plateau * plateau;


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
    al_set_window_position(display, 0, 10);
    timer = al_create_timer(1.0 / 10.0);
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

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    /// debut du jeux

    plateau = lire_plateau();
    initialiser_plateau(plateau);

    while (!end) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                end = TRUE;
                break;
            }
            case ALLEGRO_EVENT_TIMER : {

                break;
            }

        }
        dessiner_tout(plateau);

    }
    for(int i=0; i<plateau->nb_ligne;i++){
        free(plateau->map[i]);
    }
    free(plateau->map);

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}


