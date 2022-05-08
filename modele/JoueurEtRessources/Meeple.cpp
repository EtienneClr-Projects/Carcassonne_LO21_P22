//
// Created by etienne on 08/05/2022.
//

#include "Meeple.h"

Meeple::Meeple(MEEPLE_TYPE type, COULEUR couleur) {
    this->type = type;
    this->couleur = couleur;
}

std::string Meeple::toString() {
    return "Meeple de type " + ParametresPartie::toStringMEEPLE_TYPE(type)
    + " de couleur " + ParametresPartie::toStringCOULEUR(couleur);
}
