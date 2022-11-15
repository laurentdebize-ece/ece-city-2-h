#include "jeu.h"

/////////      plateau        ///////////

Plateau *creer_plateau(int nb_ligne, int nb_colonne) {
    Plateau *Newplateau = (Plateau *) malloc(sizeof(Plateau));

    Newplateau->map = (Case **) malloc(nb_ligne * sizeof(Case *));

    for (int i = 0; i < nb_ligne; ++i) {
        Newplateau->map[i] = (Case *) malloc(nb_colonne * sizeof(Case));
    }
    Newplateau->tab_des_prix = (int *) malloc(4 * sizeof(int));
    Newplateau->tab_nb_habitant_pour_chaque_stade_de_maison = (int *) malloc(6 * sizeof(int));
    Newplateau->tab_de_maison = (Maison *) malloc(100 * sizeof(Maison));
    Newplateau->tab_chateau_eau = (Ressource *) malloc(20 * sizeof(Ressource));
    Newplateau->tab_centrale_elec = (Ressource *) malloc(20 * sizeof(Ressource));
    return Newplateau;
}

Plateau *lire_plateau() {
    FILE *ifs = fopen("../map", "r");
    Plateau *plateau;

    int largeur_case, nb_colonne, nb_ligne;
    int etat;
    int nb_stade, nb_habitant_necesaire;
    int banque_initial, prix;


    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &nb_colonne);
    fscanf(ifs, "%d", &nb_ligne);
    fscanf(ifs, "%d", &largeur_case);

    plateau = creer_plateau(nb_ligne, nb_colonne);

    plateau->nb_colonne = nb_colonne;
    plateau->nb_ligne = nb_ligne;
    plateau->largeur_case = largeur_case;

    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            fscanf(ifs, "%d", &etat);
            plateau->map[i][j].etat = etat;
        }
    }

    fscanf(ifs, "%d", &nb_stade);
    plateau->nb_stade_different = nb_stade;
    for (int i = 0; i < plateau->nb_stade_different; i++) {
        fscanf(ifs, "%d", &nb_habitant_necesaire);
        plateau->tab_nb_habitant_pour_chaque_stade_de_maison[i] = nb_habitant_necesaire;
    }

    fscanf(ifs, "%d", &banque_initial);
    plateau->compte_en_banque = banque_initial;
    for (int i = 0; i < 4; i++) {
        fscanf(ifs, "%d", &prix);
        plateau->tab_des_prix[i] = prix;
    }

    plateau->nb_maison = 0;
    plateau->nb_chateau_eau = 0;
    plateau->nb_centrale_elec = 0;

    return plateau;
}

void initialiser_plateau(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (i == 0 && j == 0) {
                plateau->map[i][j].x = LARGEUR - (plateau->nb_colonne *
                                                  plateau->largeur_case); //valeur a changer pour changer la largeur du plateau
                plateau->map[i][j].y = HAUTEUR - (plateau->nb_ligne *
                                                  plateau->largeur_case); //valeur a changer pour changer la hauteur du plateau
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
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            al_draw_rectangle(plateau->map[i][j].x, plateau->map[i][j].y, plateau->map[i][j].x + plateau->largeur_case,
                              plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 255, 255), 1);

        }
    }
}

/////////      choix etage        ///////////

void initialisation_choix_etage(Bouton *bouton) {
    for (int i = 0; i < 3; i++) {
        bouton[i].largeur = 100;
        bouton[i].hauteur = 50;

    }
    bouton->nb_bouton = 3;
    bouton[0].x = 10;
    bouton[0].y = 40;

    for (int i = 1; i < 3; i++) {
        bouton[i].x = bouton[i - 1].x;
        bouton[i].y = bouton[i - 1].y + bouton[i - 1].hauteur + 10;
    }
}

void choix_etage(Bouton bouton[], int x, int y, int *etage) {

    for (int i = 0; i < bouton->nb_bouton; i++) {
        if (x >= bouton[i].x && x <= bouton[i].x + bouton[i].largeur && y >= bouton[i].y &&
            y <= bouton[i].y + bouton[i].hauteur) {
            *etage = i;
        }
    }
}

/////////      choix batiment        ///////////

void initialisation_choix_batiment(Bouton *bouton) {

    bouton->nb_bouton = 4;
    bouton[0].largeur = 60;
    bouton[0].hauteur = 60;
    bouton[0].x = 10;
    bouton[0].y = 300;
    bouton[1].largeur = 60;
    bouton[1].hauteur = 60;
    bouton[1].x = 10;
    bouton[1].y = 370;
    bouton[2].largeur = 60;
    bouton[2].hauteur = 60;
    bouton[2].x = 10;
    bouton[2].y = 440;
    bouton[3].largeur = 60;
    bouton[3].hauteur = 60;
    bouton[3].x = 10;
    bouton[3].y = 510;

}

void choix_batiment(Bouton bouton[], int x, int y, int *batiment) {

    for (int i = 0; i < bouton->nb_bouton; i++) {
        if (x >= bouton[i].x && x <= bouton[i].x + bouton[i].largeur && y >= bouton[i].y &&
            y <= bouton[i].y + bouton[i].hauteur) {
            if (*batiment == i + 1) {
                *batiment = 0;
            } else {
                *batiment = i + 1;
            }
        }
    }
}


/////////      construire batiment       ///////////

void
construire_batiment(Plateau *plateau, int choix_batiment, int souris_sur_le_plateau, int caseX, int caseY, int timer) {
    if (souris_sur_le_plateau == 1) {
        switch (choix_batiment) {
            case 1: {
                construire_route(plateau, caseX, caseY, timer);
                break;
            }
            case 2: {
                construire_maison(plateau, caseX, caseY, timer);
                break;
            }
            case 3: {
                construire_chateau_eau(plateau, caseX, caseY, timer);
                break;
            }
            case 4: {
                construire_centrale_elec(plateau, caseX, caseY, timer);
                break;
            }
        }
    }
}

void construire_route(Plateau *plateau, int caseX, int caseY, int timer) {
    if (plateau->map[caseY][caseX].etat == 0 && ((plateau->compte_en_banque - plateau->tab_des_prix[1 - 1]) >= 0)) {
        plateau->compte_en_banque -= plateau->tab_des_prix[1 - 1];
        plateau->map[caseY][caseX].etat = 1;
        verifier_viabilite_pour_les_maison_non_viable(plateau, timer);
    }
}

void construire_maison(Plateau *plateau, int caseX, int caseY, int timer) {
    int nb_case_vide = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (plateau->map[caseY + i][caseX + j].etat == 0) {
                nb_case_vide++;
            }
        }
    }
    if (nb_case_vide == 3 * 3 && ((plateau->compte_en_banque - plateau->tab_des_prix[2 - 1]) >= 0)) {
        plateau->compte_en_banque -= plateau->tab_des_prix[2 - 1];
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    crer_une_maison(plateau, caseX, caseY, timer);
                    plateau->nb_maison++;
                    plateau->map[caseY + i][caseX + j].etat = 2000 + plateau->nb_maison * 10;

                } else {
                    plateau->map[caseY + i][caseX + j].etat = 2;

                }
            }
        }
    }
}

void crer_une_maison(Plateau *plateau, int caseX, int caseY, int timer) {
    plateau->tab_de_maison[plateau->nb_maison].date_creation = timer;
    plateau->tab_de_maison[plateau->nb_maison].caseY = caseY;
    plateau->tab_de_maison[plateau->nb_maison].caseX = caseX;
    plateau->tab_de_maison[plateau->nb_maison].stade = 0;
    plateau->tab_de_maison[plateau->nb_maison].nb_habitant = 0;
    plateau->tab_de_maison[plateau->nb_maison].eau_utilise = 0;
    plateau->tab_de_maison[plateau->nb_maison].elec_utilise = 0;
    plateau->tab_de_maison[plateau->nb_maison].viable = verifier_viabilite_maison(plateau, caseX, caseY);
}

void construire_chateau_eau(Plateau *plateau, int caseX, int caseY, int timer) {
    int nb_case_vide = 0;
    for (int i = -2; i <= 3; i++) {
        for (int j = -1; j <= 2; j++) {
            if (plateau->map[caseY + i][caseX + j].etat == 0) {
                nb_case_vide++;
            }
        }
    }
    if (nb_case_vide == 4 * 6 && ((plateau->compte_en_banque - plateau->tab_des_prix[3 - 1]) >= 0)) {
        plateau->compte_en_banque -= plateau->tab_des_prix[3 - 1];
        for (int i = -2; i <= 3; i++) {
            for (int j = -1; j <= 2; j++) {
                if (i == 0 && j == 0) {
                    crer_un_chateau_eau(plateau, caseX, caseY);
                    plateau->nb_chateau_eau++;
                    plateau->map[caseY + i][caseX + j].etat = 30;

                } else {
                    plateau->map[caseY + i][caseX + j].etat = 3;

                }
            }
        }
        verifier_viabilite_pour_les_maison_non_viable(plateau, timer);
    }
}

void crer_un_chateau_eau(Plateau *plateau, int caseX, int caseY) {
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].type = 1;
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].caseY = caseY;
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].caseX = caseX;
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].capacite_max = 5000;
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].capacite_utilisee = 0;
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].nb_maison_alimentee = 0;
    plateau->tab_chateau_eau[plateau->nb_chateau_eau].tab_des_maisons_alimentee = (Maison_alimentee *) malloc(
            20 * sizeof(Maison_alimentee));

}

void construire_centrale_elec(Plateau *plateau, int caseX, int caseY, int timer) {
    int nb_case_vide = 0;
    for (int i = -1; i <= 2; i++) {
        for (int j = -2; j <= 3; j++) {
            if (plateau->map[caseY + i][caseX + j].etat == 0) {
                nb_case_vide++;
            }
        }
    }
    if (nb_case_vide == 4 * 6 && ((plateau->compte_en_banque - plateau->tab_des_prix[4 - 1]) >= 0)) {
        plateau->compte_en_banque -= plateau->tab_des_prix[4 - 1];
        for (int i = -1; i <= 2; i++) {
            for (int j = -2; j <= 3; j++) {
                if (i == 0 && j == 0) {
                    crer_une_centrale_elec(plateau, caseX, caseY);
                    plateau->nb_centrale_elec++;
                    plateau->map[caseY + i][caseX + j].etat = 40;

                } else {
                    plateau->map[caseY + i][caseX + j].etat = 4;

                }
            }
        }
        verifier_viabilite_pour_les_maison_non_viable(plateau, timer);
    }
}

void crer_une_centrale_elec(Plateau *plateau, int caseX, int caseY) {
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].type = 2;
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].caseY = caseY;
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].caseX = caseX;
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].capacite_max = 5000;
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].capacite_utilisee = 0;
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].nb_maison_alimentee = 0;
    plateau->tab_centrale_elec[plateau->nb_centrale_elec].tab_des_maisons_alimentee = (Maison_alimentee *) malloc(
            20 * sizeof(Maison_alimentee));

}

/////////      evolution maison       ///////////
void evolution_maison(Plateau *plateau, int timer) {
    for (int i = 0; i < plateau->nb_maison; i++) {
        int verification_eau_dispo = 0;
        int verification_elec_dispo = 0;
        if (plateau->tab_de_maison[i].viable) {
            if (plateau->tab_de_maison[i].stade < 4 &&
                ((timer - plateau->tab_de_maison[i].date_creation) - 15 * (plateau->tab_de_maison[i].stade + 1)) >= 0) {
                verification_eau_dispo = verifier_si_assez_d_eau_disponible(plateau, i + 1,
                                                                            plateau->tab_nb_habitant_pour_chaque_stade_de_maison[
                                                                                    plateau->tab_de_maison[i].stade +
                                                                                    1] -
                                                                            plateau->tab_de_maison[i].nb_habitant);
                verification_elec_dispo = verifier_si_assez_d_elec_disponible_dans_une_centrale(plateau, i + 1,
                                                                                                plateau->tab_nb_habitant_pour_chaque_stade_de_maison[
                                                                                                        plateau->tab_de_maison[i].stade +
                                                                                                        1]);
                if (verification_eau_dispo == 1 && verification_elec_dispo == 1) {
                    plateau->tab_de_maison[i].stade++;
                    plateau->tab_de_maison[i].nb_habitant = plateau->tab_nb_habitant_pour_chaque_stade_de_maison[plateau->tab_de_maison[i].stade];
                    plateau->map[plateau->tab_de_maison[i].caseY][plateau->tab_de_maison[i].caseX].etat++;
                    alimentation_en_eau(plateau);
                    alimentation_en_elec(plateau);
                }
            }
        }
    }
}


/////////      viabilté maison       ///////////
void verifier_viabilite_pour_les_maison_non_viable(Plateau *plateau, int timer) {
    for (int i = 0; i < plateau->nb_maison; i++) {
        if (plateau->tab_de_maison[i].viable == 0) {
            plateau->tab_de_maison[i].viable = verifier_viabilite_maison(plateau, plateau->tab_de_maison[i].caseX,
                                                                         plateau->tab_de_maison[i].caseY);
            /*if (plateau->tab_de_maison[i].viable == 1) {
                plateau->tab_de_maison[plateau->nb_maison].date_creation = timer;
            }*/
        }
    }
}

int verifier_viabilite_maison(Plateau *plateau, int caseX, int caseY) {
    int connecte_a_eau = 0;
    int connecte_a_elec = 0;
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            if ((i == 2 || j == 2 || i == -2 || j == -2) && i != j && i != -j) {
                if (plateau->map[caseY + i][caseX + j].etat == 1) {
                    chercher_eau_et_electicite(plateau, caseX + j, caseY + i, &connecte_a_eau, &connecte_a_elec);
                }
            }
        }
    }

    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 11) {
                plateau->map[i][j].etat = 1;
            }
        }
    }
    if (connecte_a_eau == 1 && connecte_a_elec == 1) {
        return 1;
    } else {
        return 0;
    }
}

void chercher_eau_et_electicite(Plateau *plateau, int caseX, int caseY, int *connecte_a_eau, int *connecte_a_elec) {
    if (*connecte_a_eau == 0 || *connecte_a_elec == 0) {
        for (int i = 4; i > 0; i--) {
            if (plateau->map[caseY - 1][caseX].etat == i) {
                if (i == 4 && *connecte_a_elec != 1) {
                    *connecte_a_elec = 1;
                }
                if (i == 3 && *connecte_a_eau != 1) {
                    *connecte_a_eau = 1;
                }
                if (i == 1) {
                    plateau->map[caseY - 1][caseX].etat = 11;
                    chercher_eau_et_electicite(plateau, caseX, caseY - 1, connecte_a_eau, connecte_a_elec);
                }

            }
            if (plateau->map[caseY + 1][caseX].etat == i) {
                if (i == 4 && *connecte_a_elec != 1) {
                    *connecte_a_elec = 1;
                }
                if (i == 3 && *connecte_a_eau != 1) {
                    *connecte_a_eau = 1;
                }
                if (i == 1) {
                    plateau->map[caseY + 1][caseX].etat = 11;
                    chercher_eau_et_electicite(plateau, caseX, caseY + 1, connecte_a_eau, connecte_a_elec);
                }
            }
            if (plateau->map[caseY][caseX - 1].etat == i) {
                if (i == 4 && *connecte_a_elec != 1) {
                    *connecte_a_elec = 1;
                }
                if (i == 3 && *connecte_a_eau != 1) {
                    *connecte_a_eau = 1;
                }
                if (i == 1) {
                    plateau->map[caseY][caseX - 1].etat = 11;
                    chercher_eau_et_electicite(plateau, caseX - 1, caseY, connecte_a_eau, connecte_a_elec);
                }

            }
            if (plateau->map[caseY][caseX + 1].etat == i) {
                if (i == 4 && *connecte_a_elec != 1) {
                    *connecte_a_elec = 1;
                }
                if (i == 3 && *connecte_a_eau != 1) {
                    *connecte_a_eau = 1;
                }
                if (i == 1) {
                    plateau->map[caseY][caseX + 1].etat = 11;
                    chercher_eau_et_electicite(plateau, caseX + 1, caseY, connecte_a_eau, connecte_a_elec);
                }
            }
        }
    }
}

/////////      alimentation en eau       ///////////
int verifier_si_assez_d_eau_disponible(Plateau *plateau, int numero_de_la_maison, int quantite_eau_necesaire) {
    int quantite_eau_disponible = 0;
    for (int k = 0; k < plateau->nb_chateau_eau; k++) {
        int a = 0;
        int maison_trouve = 0;
        for (int i = -3; i <= 4; i++) {
            for (int j = -2; j <= 3; j++) {
                a++;
                if ((i == -3 || i == 4 || j == -2 || j == 3) && a != 1 && a != 6 && a != 7 * 6 + 1 && a != 8 * 6) {
                    if (plateau->map[plateau->tab_chateau_eau[k].caseY + i][plateau->tab_chateau_eau[k].caseX +
                                                                            j].etat == 1) {
                        chercher_une_maison_en_particulier(plateau, plateau->tab_chateau_eau[k].caseX + j,
                                                           plateau->tab_chateau_eau[k].caseY + i, numero_de_la_maison,
                                                           &maison_trouve);

                    }
                }
            }
        }
        if (maison_trouve == 1) {
            quantite_eau_disponible += (plateau->tab_chateau_eau[k].capacite_max -
                                        plateau->tab_chateau_eau[k].capacite_utilisee);
        }

        for (int i = 0; i < plateau->nb_ligne; i++) {
            for (int j = 0; j < plateau->nb_colonne; j++) {
                if (plateau->map[i][j].etat == 11) {
                    plateau->map[i][j].etat = 1;
                }
            }
        }
    }

    if (quantite_eau_disponible >= quantite_eau_necesaire) {
        return 1;
    } else {
        return 0;
    }
}

void chercher_une_maison_en_particulier(Plateau *plateau, int caseX, int caseY, int numero_de_la_maison,
                                        int *maison_trouve) {
    if (*maison_trouve != 1) {
        for (int i = 2; i > 0; i--) {
            if (plateau->map[caseY - 1][caseX].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY - 2][caseX].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY - 2][caseX - 1].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY - 2][caseX + 1].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY - 1][caseX].etat = 11;
                    chercher_une_maison_en_particulier(plateau, caseX, caseY - 1, numero_de_la_maison, maison_trouve);
                }

            }
            if (plateau->map[caseY + 1][caseX].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY + 2][caseX].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY + 2][caseX - 1].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY + 2][caseX + 1].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY + 1][caseX].etat = 11;
                    chercher_une_maison_en_particulier(plateau, caseX, caseY + 1, numero_de_la_maison, maison_trouve);
                }
            }
            if (plateau->map[caseY][caseX - 1].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY][caseX - 2].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY - 1][caseX - 2].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY + 1][caseX - 2].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY][caseX - 1].etat = 11;
                    chercher_une_maison_en_particulier(plateau, caseX - 1, caseY, numero_de_la_maison, maison_trouve);

                }

            }
            if (plateau->map[caseY][caseX + 1].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY][caseX + 2].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY - 1][caseX + 2].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    } else if (plateau->map[caseY + 1][caseX + 2].etat / 10 - 200 == numero_de_la_maison) {
                        *maison_trouve = 1;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY][caseX + 1].etat = 11;
                    chercher_une_maison_en_particulier(plateau, caseX + 1, caseY, numero_de_la_maison, maison_trouve);

                }
            }
        }
    }
}

void alimentation_en_eau(Plateau *plateau) {
    for (int k = 0; k < plateau->nb_chateau_eau; k++) {
        for (int i = 0; i < plateau->tab_chateau_eau->nb_maison_alimentee; i++) {
            plateau->tab_chateau_eau[k].tab_des_maisons_alimentee[i].quantite = 0;
            plateau->tab_chateau_eau[k].tab_des_maisons_alimentee[i].numero_maison = 0;
        }
        plateau->tab_chateau_eau[k].nb_maison_alimentee = 0;
        plateau->tab_chateau_eau[k].capacite_utilisee = 0;
        for (int i = 0; i < plateau->nb_maison; i++) {
            plateau->tab_de_maison[i].eau_utilise = 0;
        }
    }

    for (int k = 0; k < plateau->nb_chateau_eau; k++) {

        int numero_maison_trouve = 1;
        while (plateau->tab_chateau_eau[k].capacite_utilisee != plateau->tab_chateau_eau[k].capacite_max &&
               numero_maison_trouve != 0) {
            int a = 0;
            int plus_petie_distance = 32767;
            numero_maison_trouve = 0;
            for (int i = -3; i <= 4; i++) {
                for (int j = -2; j <= 3; j++) {
                    a++;
                    if ((i == -3 || i == 4 || j == -2 || j == 3) && a != 1 && a != 6 && a != 7 * 6 + 1 && a != 8 * 6) {
                        if (plateau->map[plateau->tab_chateau_eau[k].caseY + i][plateau->tab_chateau_eau[k].caseX +
                                                                                j].etat == 1) {
                            chercher_maison_la_plus_proche_qui_a_besoin_d_eau(plateau,
                                                                              plateau->tab_chateau_eau[k].caseX + j,
                                                                              plateau->tab_chateau_eau[k].caseY + i,
                                                                              &numero_maison_trouve,
                                                                              &plus_petie_distance, 1);
                            for (int i = 0; i < plateau->nb_ligne; i++) {
                                for (int j = 0; j < plateau->nb_colonne; j++) {
                                    if (plateau->map[i][j].etat == 11) {
                                        plateau->map[i][j].etat = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (numero_maison_trouve != 0) {
                plateau->tab_chateau_eau[k].tab_des_maisons_alimentee[plateau->tab_chateau_eau[k].nb_maison_alimentee].numero_maison = numero_maison_trouve;
                plateau->tab_chateau_eau[k].tab_des_maisons_alimentee[plateau->tab_chateau_eau[k].nb_maison_alimentee].quantite =
                        (plateau->tab_de_maison[numero_maison_trouve - 1].nb_habitant -
                         plateau->tab_de_maison[numero_maison_trouve - 1].eau_utilise);
                plateau->tab_de_maison[numero_maison_trouve -
                                       1].eau_utilise += plateau->tab_chateau_eau[k].tab_des_maisons_alimentee[plateau->tab_chateau_eau[k].nb_maison_alimentee].quantite;
                plateau->tab_chateau_eau[k].capacite_utilisee += plateau->tab_chateau_eau[k].tab_des_maisons_alimentee[plateau->tab_chateau_eau[k].nb_maison_alimentee].quantite;
                plateau->tab_chateau_eau[k].nb_maison_alimentee++;

            }
        }

    }
}

void
chercher_maison_la_plus_proche_qui_a_besoin_d_eau(Plateau *plateau, int caseX, int caseY, int *numero_maison_trouve,
                                                  int *plus_petite_distance, int distance) {

    if (*plus_petite_distance > distance) {
        for (int i = 2; i > 0; i--) {
            if (plateau->map[caseY - 1][caseX].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY - 2][caseX].etat > 2000 &&
                        plateau->tab_de_maison[plateau->map[caseY - 2][caseX].etat / 10 - 200 - 1].eau_utilise <
                        plateau->tab_de_maison[plateau->map[caseY - 2][caseX].etat / 10 - 200 - 1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY - 2][caseX].etat / 10 - 200;
                    } else if (plateau->map[caseY - 2][caseX - 1].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY - 2][caseX - 1].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY - 2][caseX - 1].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY - 2][caseX - 1].etat / 10 - 200;
                    } else if (plateau->map[caseY - 2][caseX + 1].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY - 2][caseX + 1].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY - 2][caseX + 1].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY - 2][caseX + 1].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY - 1][caseX].etat = 11;
                    chercher_maison_la_plus_proche_qui_a_besoin_d_eau(plateau, caseX, caseY - 1, numero_maison_trouve,
                                                                      plus_petite_distance, distance + 1);
                }

            }
            if (plateau->map[caseY + 1][caseX].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY + 2][caseX].etat > 2000 &&
                        plateau->tab_de_maison[plateau->map[caseY + 2][caseX].etat / 10 - 200 - 1].eau_utilise <
                        plateau->tab_de_maison[plateau->map[caseY + 2][caseX].etat / 10 - 200 - 1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY + 2][caseX].etat / 10 - 200;
                    } else if (plateau->map[caseY + 2][caseX - 1].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY + 2][caseX - 1].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY + 2][caseX - 1].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *numero_maison_trouve = plateau->map[caseY + 2][caseX - 1].etat / 10 - 200;
                    } else if (plateau->map[caseY + 2][caseX + 1].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY + 2][caseX + 1].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY + 2][caseX + 1].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY + 2][caseX + 1].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY + 1][caseX].etat = 11;
                    chercher_maison_la_plus_proche_qui_a_besoin_d_eau(plateau, caseX, caseY + 1, numero_maison_trouve,
                                                                      plus_petite_distance, distance + 1);
                }
            }
            if (plateau->map[caseY][caseX - 1].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY][caseX - 2].etat > 2000 &&
                        plateau->tab_de_maison[plateau->map[caseY][caseX - 2].etat / 10 - 200 - 1].eau_utilise <
                        plateau->tab_de_maison[plateau->map[caseY][caseX - 2].etat / 10 - 200 - 1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY][caseX - 2].etat / 10 - 200;
                    } else if (plateau->map[caseY - 1][caseX - 2].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY - 1][caseX - 2].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY - 1][caseX - 2].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY - 1][caseX - 2].etat / 10 - 200;
                    } else if (plateau->map[caseY + 1][caseX - 2].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY + 1][caseX - 2].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY + 1][caseX - 2].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY + 1][caseX - 2].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY][caseX - 1].etat = 11;
                    chercher_maison_la_plus_proche_qui_a_besoin_d_eau(plateau, caseX - 1, caseY, numero_maison_trouve,
                                                                      plus_petite_distance, distance + 1);
                }

            }
            if (plateau->map[caseY][caseX + 1].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY][caseX + 2].etat > 2000 &&
                        plateau->tab_de_maison[plateau->map[caseY][caseX + 2].etat / 10 - 200 - 1].eau_utilise <
                        plateau->tab_de_maison[plateau->map[caseY][caseX + 2].etat / 10 - 200 - 1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY][caseX + 2].etat / 10 - 200;
                    } else if (plateau->map[caseY - 1][caseX + 2].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY - 1][caseX + 2].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY - 1][caseX + 2].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY - 1][caseX + 2].etat / 10 - 200;
                    } else if (plateau->map[caseY + 1][caseX + 2].etat > 2000 &&
                               plateau->tab_de_maison[plateau->map[caseY + 1][caseX + 2].etat / 10 - 200 -
                                                      1].eau_utilise <
                               plateau->tab_de_maison[plateau->map[caseY + 1][caseX + 2].etat / 10 - 200 -
                                                      1].nb_habitant) {
                        *plus_petite_distance = distance;
                        *numero_maison_trouve = plateau->map[caseY + 1][caseX + 2].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY][caseX + 1].etat = 11;
                    chercher_maison_la_plus_proche_qui_a_besoin_d_eau(plateau, caseX + 1, caseY, numero_maison_trouve,
                                                                      plus_petite_distance, distance + 1);
                }
            }
        }
    }
}

/////////      alimentation en elec       ///////////
int verifier_si_assez_d_elec_disponible_dans_une_centrale(Plateau *plateau, int numero_de_la_maison,
                                                          int quantite_elec_necesaire) {
    int quantite_elec_disponible = 0;
    for (int k = 0; k < plateau->nb_centrale_elec; k++) {
        int a = 0;
        int maison_trouve = 0;
        for (int i = -2; i <= 3; i++) {
            for (int j = -3; j <= 4; j++) {
                a++;
                if ((i == -2 || i == 3 || j == -3 || j == 4) && a != 1 && a != 8 && a != 5 * 8 + 1 && a != 6 * 8) {
                    if (plateau->map[plateau->tab_centrale_elec[k].caseY + i][plateau->tab_centrale_elec[k].caseX +
                                                                              j].etat == 1) {
                        chercher_une_maison_en_particulier(plateau, plateau->tab_centrale_elec[k].caseX + j,
                                                           plateau->tab_centrale_elec[k].caseY + i, numero_de_la_maison,
                                                           &maison_trouve);

                    }
                }
            }
        }
        for (int i = 0; i < plateau->nb_ligne; i++) {
            for (int j = 0; j < plateau->nb_colonne; j++) {
                if (plateau->map[i][j].etat == 11) {
                    plateau->map[i][j].etat = 1;
                }
            }
        }
        if (maison_trouve == 1) {
            for (int q = 0; q < plateau->tab_centrale_elec[k].nb_maison_alimentee; q++) {
                if (plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[q].numero_maison == numero_de_la_maison) {
                    quantite_elec_disponible += plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[q].quantite;
                }

            }
            quantite_elec_disponible += (plateau->tab_centrale_elec[k].capacite_max -
                                         plateau->tab_centrale_elec[k].capacite_utilisee);
        }
        if (quantite_elec_disponible >= quantite_elec_necesaire) {
            return 1;
        } else {
            quantite_elec_disponible = 0;
        }
    }
    return 0;
}

void alimentation_en_elec(Plateau *plateau) {

    for (int k = 0; k < plateau->nb_centrale_elec; k++) {
        for (int i = 0; i < plateau->tab_centrale_elec->nb_maison_alimentee; i++) {
            plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[i].quantite = 0;
            plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[i].numero_maison = 0;
        }
        plateau->tab_centrale_elec[k].nb_maison_alimentee = 0;
        plateau->tab_centrale_elec[k].capacite_utilisee = 0;
        for (int i = 0; i < plateau->nb_maison; i++) {
            plateau->tab_de_maison[i].elec_utilise = 0;
        }
    }


    for (int k = 0; k < plateau->nb_centrale_elec; k++) {

        int numero_maison_trouve = 1;
        while (plateau->tab_centrale_elec[k].capacite_utilisee != plateau->tab_centrale_elec[k].capacite_max &&
               numero_maison_trouve != 0) {
            int a = 0;
            numero_maison_trouve = 0;
            for (int i = -2; i <= 3; i++) {
                for (int j = -3; j <= 4; j++) {
                    a++;
                    if ((i == -2 || i == 3 || j == -3 || j == 4) && a != 1 && a != 8 && a != 5 * 8 + 1 && a != 6 * 8) {
                        if (plateau->map[plateau->tab_centrale_elec[k].caseY + i][plateau->tab_centrale_elec[k].caseX +
                                                                                  j].etat == 1) {
                            chercher_maison_qui_a_besoin_d_elec(plateau, plateau->tab_centrale_elec[k].caseX + j,
                                                                plateau->tab_centrale_elec[k].caseY + i,
                                                                &numero_maison_trouve,(plateau->tab_centrale_elec[k].capacite_max-plateau->tab_centrale_elec[k].capacite_utilisee) );

                        }
                    }
                }
            }
            for (int i = 0; i < plateau->nb_ligne; i++) {
                for (int j = 0; j < plateau->nb_colonne; j++) {
                    if (plateau->map[i][j].etat == 11) {
                        plateau->map[i][j].etat = 1;
                    }
                }
            }
            if (numero_maison_trouve != 0) {
                plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[plateau->tab_centrale_elec[k].nb_maison_alimentee].numero_maison = numero_maison_trouve;
                plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[plateau->tab_centrale_elec[k].nb_maison_alimentee].quantite = plateau->tab_de_maison[
                        numero_maison_trouve - 1].nb_habitant;
                plateau->tab_de_maison[numero_maison_trouve -
                                       1].elec_utilise += plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[plateau->tab_centrale_elec[k].nb_maison_alimentee].quantite;
                plateau->tab_centrale_elec[k].capacite_utilisee += plateau->tab_centrale_elec[k].tab_des_maisons_alimentee[plateau->tab_centrale_elec[k].nb_maison_alimentee].quantite;
                plateau->tab_centrale_elec[k].nb_maison_alimentee++;

            }
        }

    }
}

void chercher_maison_qui_a_besoin_d_elec(Plateau *plateau, int caseX, int caseY, int *numero_maison_trouve,
                                         int capacite_restante_de_la_centrale) {

    if (*numero_maison_trouve == 0) {
        for (int i = 2; i > 0; i--) {
            if (plateau->map[caseY - 1][caseX].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY - 2][caseX].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY - 2][caseX].etat /10 - 200 - 1].nb_habitant > plateau->tab_de_maison[plateau->map[caseY - 2][caseX].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                       plateau->tab_de_maison[
                                                                               plateau->map[caseY - 2][caseX].etat /
                                                                               10 - 200 - 1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY - 2][caseX].etat / 10 - 200;
                    } else if (plateau->map[caseY - 2][caseX - 1].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY - 2][caseX-1].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY - 2][caseX-1].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY - 2][
                                                                                                  caseX -
                                                                                                  1].etat /
                                                                                          10 - 200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY - 2][caseX - 1].etat / 10 - 200;
                    } else if (plateau->map[caseY - 2][caseX + 1].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY - 2][caseX+1].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY - 2][caseX+1].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY - 2][
                                                                                                  caseX + 1].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY - 2][caseX + 1].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY - 1][caseX].etat = 11;
                    chercher_maison_qui_a_besoin_d_elec(plateau, caseX, caseY - 1, numero_maison_trouve,
                                                        capacite_restante_de_la_centrale);
                }

            }
            if (plateau->map[caseY + 1][caseX].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY + 2][caseX].etat > 2000 &&(plateau->tab_de_maison[plateau->map[caseY + 2][caseX].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY + 2][caseX].etat /10 - 200 - 1].elec_utilise)&& (capacite_restante_de_la_centrale >=
                                                                       plateau->tab_de_maison[
                                                                               plateau->map[caseY + 2][caseX].etat /
                                                                               10 - 200 - 1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY + 2][caseX].etat / 10 - 200;
                    } else if (plateau->map[caseY + 2][caseX - 1].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY + 2][caseX-1].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY + 2][caseX-1].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY + 2][
                                                                                                  caseX - 1].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY + 2][caseX - 1].etat / 10 - 200;
                    } else if (plateau->map[caseY + 2][caseX + 1].etat > 2000 &&(plateau->tab_de_maison[plateau->map[caseY + 2][caseX+1].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY + 2][caseX+1].etat /10 - 200 - 1].elec_utilise)&& (capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY + 2][
                                                                                                  caseX + 1].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY + 2][caseX + 1].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY + 1][caseX].etat = 11;
                    chercher_maison_qui_a_besoin_d_elec(plateau, caseX, caseY + 1, numero_maison_trouve,
                                                        capacite_restante_de_la_centrale);
                }
            }
            if (plateau->map[caseY][caseX - 1].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY][caseX - 2].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY][caseX-2].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY][caseX-2].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                       plateau->tab_de_maison[
                                                                               plateau->map[caseY][caseX - 2].etat /
                                                                               10 - 200 - 1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY][caseX - 2].etat / 10 - 200;
                    } else if (plateau->map[caseY - 1][caseX - 2].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY-1][caseX-2].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY-1][caseX-2].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY - 1][
                                                                                                  caseX - 2].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY - 1][caseX - 2].etat / 10 - 200;
                    } else if (plateau->map[caseY + 1][caseX - 2].etat > 2000 &&(plateau->tab_de_maison[plateau->map[caseY+1][caseX-2].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY+1][caseX-2].etat /10 - 200 - 1].elec_utilise)&& (capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY + 1][
                                                                                                  caseX - 2].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY + 1][caseX - 2].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY][caseX - 1].etat = 11;
                    chercher_maison_qui_a_besoin_d_elec(plateau, caseX - 1, caseY, numero_maison_trouve,
                                                        capacite_restante_de_la_centrale);
                }

            }
            if (plateau->map[caseY][caseX + 1].etat == i) {
                if (i == 2) {
                    if (plateau->map[caseY][caseX + 2].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY][caseX+2].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY][caseX+2].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                       plateau->tab_de_maison[
                                                                               plateau->map[caseY][caseX + 2].etat /
                                                                               10 - 200 - 1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY][caseX + 2].etat / 10 - 200;
                    } else if (plateau->map[caseY - 1][caseX + 2].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY-1][caseX+2].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY-1][caseX+2].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY - 1][
                                                                                                  caseX + 2].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY - 1][caseX + 2].etat / 10 - 200;
                    } else if (plateau->map[caseY + 1][caseX + 2].etat > 2000 && (plateau->tab_de_maison[plateau->map[caseY+1][caseX+2].etat /10 - 200 - 1].nb_habitant>plateau->tab_de_maison[plateau->map[caseY+1][caseX+2].etat /10 - 200 - 1].elec_utilise)&&(capacite_restante_de_la_centrale >=
                                                                                  plateau->tab_de_maison[
                                                                                          plateau->map[caseY + 1][
                                                                                                  caseX + 2].etat / 10 -
                                                                                          200 -
                                                                                          1].nb_habitant)) {
                        *numero_maison_trouve = plateau->map[caseY + 1][caseX + 2].etat / 10 - 200;
                    }

                }
                if (i == 1) {
                    plateau->map[caseY][caseX + 1].etat = 11;
                    chercher_maison_qui_a_besoin_d_elec(plateau, caseX + 1, caseY, numero_maison_trouve,
                                                        capacite_restante_de_la_centrale);
                }
            }
        }
    }
}


/////////      emplacement souris       ///////////
void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, int *souris_sur_le_plateau, Plateau *plateau) {
    // ne pas oublie de bien commencer à l'origine du tableau
    int a = 0;
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (((x - plateau->map[0][0].x) >= j * plateau->largeur_case &&
                 (x - plateau->map[0][0].x) <= (j + 1) * plateau->largeur_case) &&
                ((y - plateau->map[0][0].y) >= i * plateau->largeur_case &&
                 (y - plateau->map[0][0].y) < (i + 1) * plateau->largeur_case)) {
                *caseX = j;
                *caseY = i;
            } else {
                a++;
            }
        }
    }
    if (a == plateau->nb_ligne * plateau->nb_colonne) {
        *souris_sur_le_plateau = 0;
    } else {
        *souris_sur_le_plateau = 1;
    }

}


/////////     dessiner batiment      ///////////
void dessiner_batiment(Plateau *plateau, int etage) {
    if (etage == 0) {
        dessiner_etage_0(plateau);
    } else if (etage == 1) {
        dessiner_etage_1(plateau);
    } else if (etage == 2) {
        dessiner_etage_2(plateau);
    }
}

void dessiner_etage_0(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 0) {
                al_draw_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                  plateau->map[i][j].x + plateau->largeur_case,
                                  plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 255, 255), 1);
            }
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(0, 0, 255));

            }
            if (plateau->map[i][j].etat / 1000 == 2) {
                if (plateau->tab_de_maison[(plateau->map[i][j].etat / 10 - 200) - 1].viable == 1) {
                    for (int stade = 0; stade < 5; stade++) {
                        if (plateau->tab_de_maison[(plateau->map[i][j].etat / 10 - 200) - 1].stade == stade) {
                            al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                                     plateau->map[i][j].x + plateau->largeur_case,
                                                     plateau->map[i][j].y + plateau->largeur_case,
                                                     al_map_rgb(0, 50 * stade, 0));
                        }

                    }

                } else {
                    al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                             plateau->map[i][j].x + plateau->largeur_case,
                                             plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(100, 0, 255));
                }

            }
            if (plateau->map[i][j].etat == 2) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(0, 255, 255));

            }
            if (plateau->map[i][j].etat == 3) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 255, 0));

            }
            if (plateau->map[i][j].etat == 4) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 255, 0));

            }
        }
    }
}

void dessiner_etage_1(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 0) {
                al_draw_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                  plateau->map[i][j].x + plateau->largeur_case,
                                  plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 255, 255), 1);
            }
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 0, 0));

            }
        }
    }
}

void dessiner_etage_2(Plateau *plateau) {
    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (plateau->map[i][j].etat == 0) {
                al_draw_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                  plateau->map[i][j].x + plateau->largeur_case,
                                  plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 255, 255), 1);
            }
            if (plateau->map[i][j].etat == 1) {
                al_draw_filled_rectangle(plateau->map[i][j].x, plateau->map[i][j].y,
                                         plateau->map[i][j].x + plateau->largeur_case,
                                         plateau->map[i][j].y + plateau->largeur_case, al_map_rgb(255, 0, 255));

            }
        }
    }
}

/////////     afficher timer      ///////////
void afficher_timer(int timer, ALLEGRO_FONT *roboto) {

    al_draw_textf(roboto, al_map_rgb(255, 255, 255), 50, 10, ALLEGRO_ALIGN_RIGHT, "%ds", timer);
}

/////////     efficher argent      ///////////
void afficher_compte_en_banque(Plateau *plateau, ALLEGRO_FONT *roboto) {
    al_draw_textf(roboto, al_map_rgb(255, 255, 255), LARGEUR - 100, 10, ALLEGRO_ALIGN_LEFT, "%d euros",
                  plateau->compte_en_banque);
}


/////////     dessiner tout     ///////////
void dessiner_tout(Plateau *plateau, int etage, int choix_batiment, int caseDeLaSourieX,
                   int caseDeLaSourieY, int souris_sur_le_plateaux, Bouton bouton_etage[], Bouton bouton_batiment[],
                   ALLEGRO_FONT *roboto,
                   int compteur) {
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    dessiner_plateau(plateau);
    dessiner_batiment(plateau, etage);
    ///dessine les boutons pour les etages
    for (int i = 0; i < bouton_etage->nb_bouton; i++) {
        al_draw_filled_rectangle(bouton_etage[i].x, bouton_etage[i].y, bouton_etage[i].x + bouton_etage[i].largeur,
                                 bouton_etage[i].y + bouton_etage[i].hauteur, al_map_rgb(100, 100, 100));

    }
    ///dessine les boutons pour choisir les batiments
    for (int i = 0; i < bouton_batiment->nb_bouton; i++) {
        al_draw_filled_rectangle(bouton_batiment[i].x, bouton_batiment[i].y,
                                 bouton_batiment[i].x + bouton_batiment[i].largeur,
                                 bouton_batiment[i].y + bouton_batiment[i].hauteur, al_map_rgb(200, 200, 200));
        if (i == choix_batiment - 1) {
            al_draw_rectangle(bouton_batiment[i].x, bouton_batiment[i].y,
                              bouton_batiment[i].x + bouton_batiment[i].largeur,
                              bouton_batiment[i].y + bouton_batiment[i].hauteur, al_map_rgb(200, 0, 200), 4);
        }
    }
    ///dessine la case ou est la souris
    if (souris_sur_le_plateaux) {
        al_draw_filled_rectangle(plateau->map[caseDeLaSourieY][caseDeLaSourieX].x,
                                 plateau->map[caseDeLaSourieY][caseDeLaSourieX].y,
                                 plateau->map[caseDeLaSourieY][caseDeLaSourieX].x + plateau->largeur_case,
                                 plateau->map[caseDeLaSourieY][caseDeLaSourieX].y + plateau->largeur_case,
                                 al_map_rgb(0, 255, 0));
    }
    afficher_timer(compteur, roboto);
    afficher_compte_en_banque(plateau, roboto);
    al_flip_display();
}


/////////     sauvegarde jeu     ///////////

void sauvegarde_jeu(Plateau *plateau) {
    FILE *ifs = fopen("../sauvegarde", "w");

    fprintf(ifs, "%d", plateau->nb_colonne);
    fprintf(ifs, "\n");
    fprintf(ifs, "%d", plateau->nb_ligne);
    fprintf(ifs, "\n");
    fprintf(ifs, "%d", plateau->largeur_case);

    for (int i = 0; i < plateau->nb_ligne; i++) {
        fprintf(ifs, "\n");
        for (int j = 0; j < plateau->nb_colonne; j++) {
            if (j + 1 < plateau->nb_colonne) {
                fprintf(ifs, "%d ", plateau->map[i][j].etat);
            } else {
                fprintf(ifs, "%d", plateau->map[i][j].etat);
            }
        }

    }

}