#include "debutDePartie.h"

void bitmapDebutDePartie(DebutDePartie* debutDePartie){

    debutDePartie->debut[0] = al_load_bitmap("../image/DebutDePartie/affichage1.png");
    debutDePartie->debut[1] = al_load_bitmap("../image/DebutDePartie/affichage2.png");
    debutDePartie->debut[2] = al_load_bitmap("../image/DebutDePartie/affichage3.png");
    debutDePartie->debut[3] = al_load_bitmap("../image/DebutDePartie/affichage4.png");

}
