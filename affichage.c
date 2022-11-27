#include "affichage.h"


void dessiner_plateau(Plateau *plateau) {

    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 0) {
                al_draw_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                  plateau->map[i][j].x + plateau->largeur_case,
                                  plateau->map[i][j].y + plateau->largeur_case, al_map_rgba(255, 255, 255, 1), 1);

            }
        }
    }
}

/////////     dessiner batiment      ///////////
void dessiner_batiment(Plateau *plateau, int etage, int caseDeLaSourieX, int caseDeLaSourieY, ALLEGRO_FONT *roboto) {
    if (etage == 0) {
        dessiner_etage_0(plateau);
    } else if (etage == 1) {
        dessiner_etage_1(plateau, caseDeLaSourieX, caseDeLaSourieY, roboto);
    } else if (etage == 2) {
        dessiner_etage_2(plateau, caseDeLaSourieX, caseDeLaSourieY, roboto);
    }
}

void dessiner_etage_0(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(0, 0, 255));

            }
        }
    }
    for (int k = 0; k < plateau->nb_maison; k++) {
        al_draw_bitmap(plateau->tab_de_maison[k].image_batiment,
                       (plateau->tab_de_maison[k].caseX + 2) * plateau->largeur_case +
                       (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_de_maison[k].largeur,
                       (plateau->tab_de_maison[k].caseY + 2) * plateau->largeur_case +
                       (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_de_maison[k].hauteur, 0);

        if (plateau->tab_de_maison[k].viable == 0) {
            al_draw_filled_rectangle((plateau->tab_de_maison[k].caseX - 1) * plateau->largeur_case +
                                     (LARGEUR - plateau->largeur_case * plateau->nb_colonne),
                                     (plateau->tab_de_maison[k].caseY - 1) * plateau->largeur_case +
                                     (HAUTEUR - plateau->largeur_case * plateau->nb_ligne),
                                     (plateau->tab_de_maison[k].caseX - 1) * plateau->largeur_case +
                                     (LARGEUR - plateau->largeur_case * plateau->nb_colonne) +
                                     plateau->tab_de_maison[k].largeur,
                                     (plateau->tab_de_maison[k].caseY - 1) * plateau->largeur_case +
                                     (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) +
                                     plateau->tab_de_maison[k].hauteur,
                                     al_map_rgba(100, 0, 0, 30));

        }
    }
    for (int k = 0; k < plateau->nb_chateau_eau; k++) {
        al_draw_bitmap(plateau->tab_chateau_eau[k].image_batiment,
                       (plateau->tab_chateau_eau[k].caseX + 3) * plateau->largeur_case +
                       (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_chateau_eau[k].largeur,
                       (plateau->tab_chateau_eau[k].caseY + 4) * plateau->largeur_case +
                       (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_chateau_eau[k].hauteur, 0);


    }
    for (int k = 0; k < plateau->nb_centrale_elec; k++) {
        al_draw_bitmap(plateau->tab_centrale_elec[k].image_batiment,
                       (plateau->tab_centrale_elec[k].caseX + 4) * plateau->largeur_case +
                       (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_centrale_elec[k].largeur,
                       (plateau->tab_centrale_elec[k].caseY + 3) * plateau->largeur_case +
                       (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_centrale_elec[k].hauteur,
                       0);


    }
}

void dessiner_etage_1(Plateau *plateau, int caseDeLaSourieX, int caseDeLaSourieY, ALLEGRO_FONT *roboto) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 0, 0));

            }
        }
    }
    for (int k = 0; k < plateau->nb_chateau_eau; k++) {
        al_draw_bitmap(plateau->tab_chateau_eau[k].image_batiment,
                       (plateau->tab_chateau_eau[k].caseX + 3) * plateau->largeur_case +
                       (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_chateau_eau[k].largeur,
                       (plateau->tab_chateau_eau[k].caseY + 4) * plateau->largeur_case +
                       (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_chateau_eau[k].hauteur, 0);


    }
    for (int k = 0; k < plateau->nb_maison; k++) {
        if (plateau->tab_de_maison[k].viable == 1 && plateau->tab_de_maison[k].stade < 5 &&
            plateau->tab_de_maison[k].stade > 0) {
            al_draw_bitmap(plateau->tab_de_maison[k].image_batiment,
                           (plateau->tab_de_maison[k].caseX + 2) * plateau->largeur_case +
                           (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_de_maison[k].largeur,
                           (plateau->tab_de_maison[k].caseY + 2) * plateau->largeur_case +
                           (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_de_maison[k].hauteur,
                           0);

        }
    }


    affiche_capacite_eau_de_chaque_batiment(plateau, caseDeLaSourieX, caseDeLaSourieY, roboto);
}


void affiche_capacite_eau_de_chaque_batiment(Plateau *plateau, int caseDeLaSourieX, int caseDeLaSourieY,
                                             ALLEGRO_FONT *roboto) {
    if (caseDeLaSourieX < plateau->nb_colonne / 2) {
        if (caseDeLaSourieY < plateau->nb_ligne / 2) {
            for (int k = 0; k < plateau->nb_chateau_eau; k++) {
                if (caseDeLaSourieX >= plateau->tab_chateau_eau[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_chateau_eau[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_chateau_eau[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_chateau_eau[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(0, 0, 255), (caseDeLaSourieX + 1) * plateau->largeur_case +
                                                                 (LARGEUR -
                                                                  plateau->largeur_case * plateau->nb_colonne),
                                  (caseDeLaSourieY + 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_LEFT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_chateau_eau[k].capacite_utilisee,
                                  plateau->tab_chateau_eau[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    int a = 0;
                    for (int i = 0; i < plateau->nb_chateau_eau; i++) {
                        for (int j = 0; j < plateau->tab_chateau_eau[i].nb_maison_alimentee; j++) {
                            if (plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(0, 0, 255),
                                              (caseDeLaSourieX + 1) * plateau->largeur_case +
                                              (LARGEUR - plateau->largeur_case * plateau->nb_colonne),
                                              (caseDeLaSourieY + 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) + 30 * a,
                                              ALLEGRO_ALIGN_LEFT, "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].eau_utilise);
                                a++;
                            }
                        }
                    }
                }
            }
        } else {
            for (int k = 0; k < plateau->nb_chateau_eau; k++) {
                if (caseDeLaSourieX >= plateau->tab_chateau_eau[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_chateau_eau[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_chateau_eau[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_chateau_eau[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(0, 0, 255), (caseDeLaSourieX + 1) * plateau->largeur_case +
                                                                 (LARGEUR -
                                                                  plateau->largeur_case * plateau->nb_colonne),
                                  (caseDeLaSourieY - 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_LEFT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_chateau_eau[k].capacite_utilisee,
                                  plateau->tab_chateau_eau[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    int a = 0;
                    for (int i = 0; i < plateau->nb_chateau_eau; i++) {
                        for (int j = plateau->tab_chateau_eau[i].nb_maison_alimentee; j >= 0; j--) {
                            if (plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(0, 0, 255),
                                              (caseDeLaSourieX + 1) * plateau->largeur_case +
                                              (LARGEUR - plateau->largeur_case * plateau->nb_colonne),
                                              (caseDeLaSourieY - 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - 30 * a,
                                              ALLEGRO_ALIGN_LEFT, "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].eau_utilise);
                                a++;
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (caseDeLaSourieY < plateau->nb_ligne / 2) {
            for (int k = 0; k < plateau->nb_chateau_eau; k++) {
                if (caseDeLaSourieX >= plateau->tab_chateau_eau[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_chateau_eau[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_chateau_eau[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_chateau_eau[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(0, 0, 255), (caseDeLaSourieX) * plateau->largeur_case + (LARGEUR -
                                                                                                              plateau->largeur_case *
                                                                                                              plateau->nb_colonne),
                                  (caseDeLaSourieY + 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_RIGHT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_chateau_eau[k].capacite_utilisee,
                                  plateau->tab_chateau_eau[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    int a = 0;
                    for (int i = 0; i < plateau->nb_chateau_eau; i++) {
                        for (int j = 0; j < plateau->tab_chateau_eau[i].nb_maison_alimentee; j++) {
                            if (plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(0, 0, 255), (caseDeLaSourieX) * plateau->largeur_case +
                                                                             (LARGEUR - plateau->largeur_case *
                                                                                        plateau->nb_colonne),
                                              (caseDeLaSourieY + 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) + 30 * a,
                                              ALLEGRO_ALIGN_RIGHT, "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].eau_utilise);
                                a++;
                            }
                        }
                    }
                }
            }
        } else {
            for (int k = 0; k < plateau->nb_chateau_eau; k++) {
                if (caseDeLaSourieX >= plateau->tab_chateau_eau[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_chateau_eau[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_chateau_eau[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_chateau_eau[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(0, 0, 255), (caseDeLaSourieX) * plateau->largeur_case + (LARGEUR -
                                                                                                              plateau->largeur_case *
                                                                                                              plateau->nb_colonne),
                                  (caseDeLaSourieY - 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_RIGHT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_chateau_eau[k].capacite_utilisee,
                                  plateau->tab_chateau_eau[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    int a = 0;
                    for (int i = 0; i < plateau->nb_chateau_eau; i++) {
                        for (int j = plateau->tab_chateau_eau[i].nb_maison_alimentee; j >= 0; j--) {
                            if (plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(0, 0, 255), (caseDeLaSourieX) * plateau->largeur_case +
                                                                             (LARGEUR - plateau->largeur_case *
                                                                                        plateau->nb_colonne),
                                              (caseDeLaSourieY - 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - 30 * a,
                                              ALLEGRO_ALIGN_RIGHT, "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_chateau_eau[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].eau_utilise);
                                a++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void dessiner_etage_2(Plateau *plateau, int caseDeLaSourieX, int caseDeLaSourieY, ALLEGRO_FONT *roboto) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 0, 255));

            }
        }
    }
    for (int k = 0; k < plateau->nb_centrale_elec; k++) {
        al_draw_bitmap(plateau->tab_centrale_elec[k].image_batiment,
                       (plateau->tab_centrale_elec[k].caseX + 4) * plateau->largeur_case +
                       (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_centrale_elec[k].largeur,
                       (plateau->tab_centrale_elec[k].caseY + 3) * plateau->largeur_case +
                       (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_centrale_elec[k].hauteur,
                       0);


    }
    for (int k = 0; k < plateau->nb_maison; k++) {
        if (plateau->tab_de_maison[k].viable == 1 && plateau->tab_de_maison[k].stade < 5 &&
            plateau->tab_de_maison[k].stade > 0) {
            al_draw_bitmap(plateau->tab_de_maison[k].image_batiment,
                           (plateau->tab_de_maison[k].caseX + 2) * plateau->largeur_case +
                           (LARGEUR - plateau->largeur_case * plateau->nb_colonne) - plateau->tab_de_maison[k].largeur,
                           (plateau->tab_de_maison[k].caseY + 2) * plateau->largeur_case +
                           (HAUTEUR - plateau->largeur_case * plateau->nb_ligne) - plateau->tab_de_maison[k].hauteur,
                           0);

        }
    }
    affiche_capacite_elec_de_chaque_batiment(plateau, caseDeLaSourieX, caseDeLaSourieY, roboto);
}

void affiche_capacite_elec_de_chaque_batiment(Plateau *plateau, int caseDeLaSourieX, int caseDeLaSourieY,
                                              ALLEGRO_FONT *roboto) {
    if (caseDeLaSourieX < plateau->nb_colonne / 2) {
        if (caseDeLaSourieY < plateau->nb_ligne / 2) {
            for (int k = 0; k < plateau->nb_centrale_elec; k++) {
                if (caseDeLaSourieX >= plateau->tab_centrale_elec[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_centrale_elec[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_centrale_elec[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_centrale_elec[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(255, 213, 79), (caseDeLaSourieX + 1) * plateau->largeur_case +
                                                                 (LARGEUR -
                                                                  plateau->largeur_case * plateau->nb_colonne),
                                  (caseDeLaSourieY + 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_LEFT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_centrale_elec[k].capacite_utilisee,
                                  plateau->tab_centrale_elec[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    for (int i = 0; i < plateau->nb_centrale_elec; i++) {
                        for (int j = 0; j < plateau->tab_centrale_elec[i].nb_maison_alimentee; j++) {
                            if (plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(255, 213, 79),
                                              (caseDeLaSourieX + 1) * plateau->largeur_case +
                                              (LARGEUR - plateau->largeur_case * plateau->nb_colonne),
                                              (caseDeLaSourieY + 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_LEFT,
                                              "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].elec_utilise);
                            }
                        }
                    }
                }
            }
        } else {
            for (int k = 0; k < plateau->nb_centrale_elec; k++) {
                if (caseDeLaSourieX >= plateau->tab_centrale_elec[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_centrale_elec[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_centrale_elec[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_centrale_elec[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(255, 213, 79), (caseDeLaSourieX + 1) * plateau->largeur_case +
                                                                 (LARGEUR -
                                                                  plateau->largeur_case * plateau->nb_colonne),
                                  (caseDeLaSourieY - 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_LEFT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_centrale_elec[k].capacite_utilisee,
                                  plateau->tab_centrale_elec[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    for (int i = 0; i < plateau->nb_centrale_elec; i++) {
                        for (int j = plateau->tab_centrale_elec[i].nb_maison_alimentee; j >= 0; j--) {
                            if (plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(255, 213, 79),
                                              (caseDeLaSourieX + 1) * plateau->largeur_case +
                                              (LARGEUR - plateau->largeur_case * plateau->nb_colonne),
                                              (caseDeLaSourieY - 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_LEFT,
                                              "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].elec_utilise);
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (caseDeLaSourieY < plateau->nb_ligne / 2) {
            for (int k = 0; k < plateau->nb_centrale_elec; k++) {
                if (caseDeLaSourieX >= plateau->tab_centrale_elec[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_centrale_elec[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_centrale_elec[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_centrale_elec[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(255, 213, 79), (caseDeLaSourieX) * plateau->largeur_case + (LARGEUR -
                                                                                                              plateau->largeur_case *
                                                                                                              plateau->nb_colonne),
                                  (caseDeLaSourieY + 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_RIGHT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_centrale_elec[k].capacite_utilisee,
                                  plateau->tab_centrale_elec[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    for (int i = 0; i < plateau->nb_centrale_elec; i++) {
                        for (int j = 0; j < plateau->tab_centrale_elec[i].nb_maison_alimentee; j++) {
                            if (plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(255, 213, 79), (caseDeLaSourieX) * plateau->largeur_case +
                                                                             (LARGEUR - plateau->largeur_case *
                                                                                        plateau->nb_colonne),
                                              (caseDeLaSourieY + 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne),
                                              ALLEGRO_ALIGN_RIGHT, "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].elec_utilise);
                            }
                        }
                    }
                }
            }
        } else {
            for (int k = 0; k < plateau->nb_centrale_elec; k++) {
                if (caseDeLaSourieX >= plateau->tab_centrale_elec[k].caseX_haut_gauche &&
                    caseDeLaSourieX <= plateau->tab_centrale_elec[k].caseX_droite_bas &&
                    caseDeLaSourieY >= plateau->tab_centrale_elec[k].caseY_haut_gauche &&
                    caseDeLaSourieY <= plateau->tab_centrale_elec[k].caseY_droite_bas) {
                    al_draw_textf(roboto, al_map_rgb(255, 213, 79), (caseDeLaSourieX) * plateau->largeur_case + (LARGEUR -
                                                                                                              plateau->largeur_case *
                                                                                                              plateau->nb_colonne),
                                  (caseDeLaSourieY - 1) * plateau->largeur_case +
                                  (HAUTEUR - plateau->largeur_case * plateau->nb_ligne), ALLEGRO_ALIGN_RIGHT,
                                  "Chateau %d : %d / %d", k + 1, plateau->tab_centrale_elec[k].capacite_utilisee,
                                  plateau->tab_centrale_elec[k].capacite_max);
                }
            }
            for (int k = 0; k < plateau->nb_maison; k++) {
                if (caseDeLaSourieX >= (plateau->tab_de_maison[k].caseX - 1) &&
                    caseDeLaSourieX <= (plateau->tab_de_maison[k].caseX + 1) &&
                    caseDeLaSourieY >= (plateau->tab_de_maison[k].caseY - 1) &&
                    caseDeLaSourieY <= (plateau->tab_de_maison[k].caseY + 1)) {
                    for (int i = 0; i < plateau->nb_centrale_elec; i++) {
                        for (int j = plateau->tab_centrale_elec[i].nb_maison_alimentee; j >= 0; j--) {
                            if (plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].numero_maison == k + 1) {
                                al_draw_textf(roboto, al_map_rgb(255, 213, 79), (caseDeLaSourieX) * plateau->largeur_case +
                                                                             (LARGEUR - plateau->largeur_case *
                                                                                        plateau->nb_colonne),
                                              (caseDeLaSourieY - 1) * plateau->largeur_case +
                                              (HAUTEUR - plateau->largeur_case * plateau->nb_ligne),
                                              ALLEGRO_ALIGN_RIGHT, "Chateau %d : %d / %d", i + 1,
                                              plateau->tab_centrale_elec[i].tab_des_maisons_alimentee[j].quantite,
                                              plateau->tab_de_maison[k].elec_utilise);
                            }
                        }
                    }
                }
            }
        }
    }
}


/////////     afficher interface      ///////////
void afficher_interface(Plateau *plateau, ALLEGRO_FONT *roboto) {
    afficher_timer(plateau->temps_en_seconde, roboto);
    afficher_compte_en_banque(plateau, roboto);
    afficher_nb_habitant(plateau, roboto);
    afficher_rapport_sur_eau_total(plateau, roboto);
    afficher_rapport_sur_electricite_total(plateau, roboto);
}

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


void dessinerCaseSouris(int sourisSurPlateau, int choixBatiment, int caseX, int caseY, Plateau *plateau) {

    if (sourisSurPlateau) {
        // maison
        if (choixBatiment == 2 && caseX >= 1 && caseY >= 1 && caseX <= 43 && caseY <= 33) {
            al_draw_bitmap(plateau->tab_des_different_stade_possible[0].image_du_stade_correspondant,
                           plateau->map[caseY - 1][caseX - 1].x, plateau->map[caseY - 1][caseX - 1].y, 0);

            // chateau
        } else if (choixBatiment == 3 && caseX >= 1 && caseY >= 2 && caseX <= 42 && caseY <= 31) {
            al_draw_bitmap(plateau->tab_dessin_ressource[0].image_du_batiment,
                           plateau->map[caseY - 2][caseX - 1].x,
                           plateau->map[caseY - 2][caseX - 1].y, 0);

        } else if (choixBatiment == 4 && caseX >= 2 && caseY >= 1 && caseX <= 41 && caseY <= 31) {
            al_draw_bitmap(plateau->tab_dessin_ressource[1].image_du_batiment,
                           plateau->map[caseY - 1][caseX - 2].x,
                           plateau->map[caseY - 1][caseX - 2].y, 0);


        } else {
            al_draw_filled_rectangle(plateau->map[caseY][caseX].x,
                                     plateau->map[caseY][caseX].y,
                                     plateau->map[caseY][caseX].x + plateau->largeur_case,
                                     plateau->map[caseY][caseX].y + plateau->largeur_case,
                                     al_map_rgb(0, 255, 0));
        }
    }
}

void dessinerBoutonPause(Bouton *boutonPause, int pause, ALLEGRO_FONT *roboto) {

    ALLEGRO_COLOR buttonBackgroundColor = al_map_rgb(180, 180, 180);
    ALLEGRO_COLOR buttonBackgroundColorDark = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR buttonClickedColor = al_map_rgb(179, 0, 134);
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR fontColor;

    al_draw_filled_rounded_rectangle(boutonPause->x - 5, boutonPause->y + 5,
                                     boutonPause->x + boutonPause->largeur - 5,
                                     boutonPause->y + boutonPause->hauteur + 5,
                                     10, 10, buttonBackgroundColorDark);

    // si le bouton est cliqué
    if (pause == 1) {
        color = buttonClickedColor;
        fontColor = al_map_rgb(255, 255, 255);
    } else {
        color = buttonBackgroundColor;
        fontColor = al_map_rgb(0, 0, 0);
    }

    al_draw_filled_rounded_rectangle(boutonPause->x, boutonPause->y,
                                     boutonPause->x + boutonPause->largeur,
                                     boutonPause->y + boutonPause->hauteur,
                                     10, 10, color);

    al_draw_textf(roboto, fontColor, boutonPause->x + 15, boutonPause->y + 6, ALLEGRO_ALIGN_LEFT, "%s",
                  boutonPause->label);
}

/////////     dessiner tout     ///////////
void dessiner_tout(Plateau *plateau, int etage, int pause, int choix_batiment, int caseDeLaSourieX,
                   int caseDeLaSourieY, int souris_sur_le_plateaux, Bouton bouton_etage[], Bouton bouton_batiment[],
                   Bouton *bouton_pause,
                   ALLEGRO_FONT *roboto, ALLEGRO_FONT *robotoLabelBoutton, ALLEGRO_BITMAP *map) {
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    al_draw_bitmap(map, 0, 0, 0);
    dessiner_plateau(plateau);
    dessiner_batiment(plateau, etage, caseDeLaSourieX, caseDeLaSourieY, roboto);
    ///dessine les boutons pour les etages
    for (int i = 0; i < bouton_etage->nb_bouton; i++) {
        dessinerBoutonEtage(bouton_etage[i], etage, i, plateau, robotoLabelBoutton);
    }
    ///dessine les boutons pour choisir les batiments
    if (etage == 0) {
        ///dessine la case ou est la souris
        dessinerCaseSouris(souris_sur_le_plateaux, choix_batiment, caseDeLaSourieX, caseDeLaSourieY, plateau);


        for (int i = 0; i < bouton_batiment->nb_bouton; i++) {
            dessinerBoutonBatiment(bouton_batiment[i], choix_batiment, i, plateau);
        }
    }
    ///dessine le bouton pour mettre en pause
    dessinerBoutonPause(bouton_pause, pause, roboto);


    afficher_interface(plateau, roboto);
    al_flip_display();
}
