//
// Created by etienne on 08/05/2022.
//

#ifndef CARCASSONNE_LO21_P22_MEEPLE_H
#define CARCASSONNE_LO21_P22_MEEPLE_H


#include "Gestion/ParametresPartie.h"
#include "Joueur.h"

class Meeple {
    MEEPLE_TYPE type;
    COULEUR couleur;
    std::string cheminImage;

    Joueur *joueur = nullptr;
public:

    Meeple(MEEPLE_TYPE type, COULEUR couleur, std::string cheminImage);

    std::string toString();
};


#endif //CARCASSONNE_LO21_P22_MEEPLE_H
