#include "jeu.h"

/////plateau
Plateau *creer_plateau(int nb_ligne, int nb_colonne) {
    Plateau *Newplateau = (Plateau *) malloc(sizeof(Plateau));

    Newplateau->map = (Case **) malloc(nb_ligne * sizeof(Case *));

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

/////choix etage
void initialisation_choix_etage(Bouton *bouton) {
    for (int i = 0; i < 3; i++) {
        bouton[i].largeur = 100;
        bouton[i].hauteur = 50;

    }
    bouton->nb_bouton=3;
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
/////choix batiment
void initialisation_choix_batiment(Bouton *bouton) {

    bouton->nb_bouton=3;
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

}
void choix_batiment(Bouton bouton[], int x, int y, int *batiment) {

    for (int i = 0; i < bouton->nb_bouton; i++) {
        if (x >= bouton[i].x && x <= bouton[i].x + bouton[i].largeur && y >= bouton[i].y &&
            y <= bouton[i].y + bouton[i].hauteur) {
            if(*batiment==i+1){
                *batiment=0;
            }else{
                *batiment = i+1;
            }
        }
    }
}


/////construire batiment
void construire_batiment(Plateau* plateau,int choix_batiment,int souris_sur_le_plateau,int caseX,int caseY){
    if(souris_sur_le_plateau==1){
        switch (choix_batiment) {
            case 1:{
                construire_route(plateau,caseX,caseY);
                break;
            }
            case 2:{
                construire_maison(plateau,caseX,caseY);
                break;
            }
            case 3:{
                construire_chateau_eau(plateau,caseX,caseY);
                break;
            }
        }
    }
}
void construire_route(Plateau* plateau,int caseX,int caseY){
    if(plateau->map[caseY][caseX].etat==0){
        plateau->map[caseY][caseX].etat=1;
    }
}
void construire_maison(Plateau* plateau,int caseX,int caseY){
    int nb_case_vide=0;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(plateau->map[caseY+i][caseX+j].etat==0){
                nb_case_vide++;
            }
        }
    }
    if(nb_case_vide==3*3){
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                if(i==0 && j==0){
                    plateau->map[caseY+i][caseX+j].etat=20;

                }else{
                    plateau->map[caseY+i][caseX+j].etat=2;

                }
            }
        }
    }
}
void construire_chateau_eau(Plateau* plateau,int caseX,int caseY){
    int nb_case_vide=0;
    for(int i=-2;i<=3;i++){
        for(int j=-1;j<=2;j++){
            if(plateau->map[caseY+i][caseX+j].etat==0){
                nb_case_vide++;
            }
        }
    }
    if(nb_case_vide==4*6){
        for(int i=-2;i<=3;i++){
            for(int j=-1;j<=2;j++){
                if(i==0 && j==0){
                    plateau->map[caseY+i][caseX+j].etat=30;

                }else{
                    plateau->map[caseY+i][caseX+j].etat=3;

                }
            }
        }
    }
}

////emplacement souris
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

/////timer
void afficher_timer(int timer, ALLEGRO_FONT *roboto) {
    timer /= 10;
    al_draw_textf(roboto, al_map_rgb(255, 255, 255), 50, 10, ALLEGRO_ALIGN_RIGHT, "%ds", timer);
}

/////dessiner batiment
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


/////dessiner tout
void dessiner_tout(Plateau *plateau, int etage,int choix_batiment, int caseDeLaSourieX,
                   int caseDeLaSourieY, int souris_sur_le_plateaux, Bouton bouton_etage[],Bouton bouton_batiment[],ALLEGRO_FONT *roboto,
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
        al_draw_filled_rectangle(bouton_batiment[i].x, bouton_batiment[i].y, bouton_batiment[i].x + bouton_batiment[i].largeur,
                                 bouton_batiment[i].y + bouton_batiment[i].hauteur, al_map_rgb(200, 200, 200));
        if(i==choix_batiment-1){
            al_draw_rectangle(bouton_batiment[i].x, bouton_batiment[i].y, bouton_batiment[i].x + bouton_batiment[i].largeur,
                                     bouton_batiment[i].y + bouton_batiment[i].hauteur, al_map_rgb(200, 0, 200),4);
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
    al_flip_display();
}

////sauvegarde jeu
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