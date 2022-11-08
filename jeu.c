#include "jeu.h"


Plateau* creer_plateau(int nb_ligne,int nb_colonne){
    Plateau *Newplateau = (Plateau *) malloc(sizeof(Plateau));

    Newplateau->map = (Case **) malloc( nb_ligne* sizeof(Case *));

    for (int i = 0; i < nb_ligne; ++i) {
        Newplateau->map[i] = (Case *) malloc(nb_colonne * sizeof(Case));
    }

    return Newplateau;
}
Plateau *lire_plateau() {
    FILE *ifs = fopen("../map", "r");
    Plateau *plateau;

    int largeur_case, nb_colonne, nb_ligne;
    int etat;


    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &nb_colonne);
    fscanf(ifs, "%d", &nb_ligne);
    fscanf(ifs, "%d", &largeur_case);

    plateau = creer_plateau(nb_ligne,nb_colonne);

    plateau->nb_colonne=nb_colonne;
    plateau->nb_ligne=nb_ligne;
    plateau->largeur_case=largeur_case;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            fscanf(ifs, "%d", &etat);
            plateau->map[i][j].etat=etat;
        }
    }

    return plateau;
}
void initialiser_plateau(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne ; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (i == 0 && j == 0) {
                plateau->map[i][j].x = LARGEUR-(plateau->nb_colonne*plateau->largeur_case); //valeur a changer pour changer la largeur du plateau
                plateau->map[i][j].y = HAUTEUR-(plateau->nb_ligne*plateau->largeur_case); //valeur a changer pour changer la hauteur du plateau
            } else if (i == 0) {
                plateau->map[i][j].x = plateau->map[i][j - 1].x + plateau->largeur_case;
                plateau->map[i][j].y = plateau->map[i][j - 1].y;
            } else {
                plateau->map[i][j].x = plateau->map[i - 1][j].x;
                plateau->map[i][j].y = plateau->map[i - 1][j].y + plateau->largeur_case;
            }
        }
    }
}
void dessiner_plateau(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne ; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 0) {
                al_draw_rectangle(plateau->map[i][j].x, plateau->map[i][j].y, plateau->map[i][j].x + plateau->largeur_case,
                                  plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255,255,255), 1);
            }
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y, plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(0,0,255));
            }
        }
    }
}



void dessiner_tout(Plateau *plateau) {
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    dessiner_plateau(plateau);
    al_flip_display();
}