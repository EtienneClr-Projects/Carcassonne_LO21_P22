//
// Created by etienne on 27/04/2022.
//

#include "Case.h"


void Case::setTuileParente(Tuile *tuileParente) {
//todo
}

std::string Case::toString() {
    return ParametresPartie::toStringZONE_TYPE(type);
}

Tuile *Case::getTuileParente() {
    return nullptr;//todo
}

DIRECTION Case::getDirection() {
    return direction;
}

ZONE_TYPE Case::getZoneType() {
    return type;
}

Zone * Case::getZone() {
    return zone;
}

int Case::getIdConnexion() const {
    return iDConnexion;
}

Joueur *Case::getJoueur() const {
    return joueur;
}

void Case::setZone(Zone *pZone) {
    zone = pZone;
}
