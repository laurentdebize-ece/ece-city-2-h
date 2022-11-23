//
// Created by bapti on 18/11/2022.
//

#include "debutDePartie.h"

void bitmapDebutDePartie(DebutDePartie* debutDePartie){

    debutDePartie->debut[0] = al_load_bitmap("../image/affichage1.png");
    debutDePartie->debut[1] = al_load_bitmap("../image/affichage2.png");
    debutDePartie->debut[2] = al_load_bitmap("../image/affichage3.png");
    debutDePartie->debut[3] = al_load_bitmap("../image/affichage4.png");

}
