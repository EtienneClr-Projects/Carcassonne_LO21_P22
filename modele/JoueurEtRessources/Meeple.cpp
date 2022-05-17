#include "Meeple.h"

#include <utility>

Meeple::Meeple(MEEPLE_TYPE type, COULEUR couleur, std::string cheminImage) {
    this->type = type;
    this->couleur = couleur;
    this->cheminImage = std::move(cheminImage);
}

std::string Meeple::toString() {
    return "Meeple de type " + ParametresPartie::toStringMEEPLE_TYPE(type)
    + " de couleur " + ParametresPartie::toStringCOULEUR(couleur);
}
