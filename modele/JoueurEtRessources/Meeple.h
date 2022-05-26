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

public:
    COULEUR getCouleur(){return  couleur;}
    MEEPLE_TYPE getType(){return type;}

    Meeple(MEEPLE_TYPE type, COULEUR couleur, std::string cheminImage);

    std::string toString();
};


#endif //CARCASSONNE_LO21_P22_MEEPLE_H
