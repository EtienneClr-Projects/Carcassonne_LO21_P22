//
// Created by etienne on 27/04/2022.
//

#include "Case.h"


void Case::setTuileParente(Tuile *tuileParente) {

}

std::string Case::toString() {
    return ParametresPartie::toStringZONE_TYPE(type);
}

Tuile *Case::getTuileParente() {
    return nullptr;
}

DIRECTION Case::getDirection() {
    return DIRECTION::NORD;
}

ZONE_TYPE Case::getZoneType() {
    return ZONE_TYPE::CHEMIN;
}

Zone *Case::getZone() {
    return nullptr;
}

int Case::getIdConnexion() const {
    return iDConnexion;
}

Joueur *Case::getJoueur() const {
    return joueur;
}
