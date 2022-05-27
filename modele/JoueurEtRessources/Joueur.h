//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_JOUEUR_H
#define CARCASSONNE_LO21_P22_JOUEUR_H


#include "Gestion/ParametresPartie.h"

class Joueur {
private:
    Joueur() = default;

    COULEUR couleur;
public:

    COULEUR getCouleur();
};


#endif //CARCASSONNE_LO21_P22_JOUEUR_H
