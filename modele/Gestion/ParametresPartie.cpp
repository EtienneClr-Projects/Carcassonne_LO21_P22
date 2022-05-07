//
// Created by etienne on 27/04/2022.
//

#include "ParametresPartie.h"

/**
 * Permet de transformer un DIRECTION en string pour de l'affichage
 * @param dir la DIRECTION
 * @return la direction sous forme de string. Par exemple "NORD_OUEST".
 */
std::string ParametresPartie::toStringDIRECTION(const DIRECTION dir) {
    std::string str;
    switch (dir) {
        case DIRECTION::NORD_OUEST:
            str = "NORD_OUEST";
            break;
        case DIRECTION::NORD_EST:
            str = "NORD_EST";
            break;
        case DIRECTION::SUD_OUEST:
            str = "SUD_OUEST";
            break;
        case DIRECTION::SUD_EST:
            str = "SUD_EST";
            break;
        case DIRECTION::NORD:
            str = "NORD";
            break;
        case DIRECTION::SUD:
            str = "SUD";
            break;
        case DIRECTION::OUEST:
            str = "OUEST";
            break;
        case DIRECTION::EST:
            str = "EST";
            break;
        case DIRECTION::MILIEU:
            str = "MILIEU";
            break;
    }
    return str;
}

/**
 * Renvoie le type de la case en string pour de l'affichage
 * @param _case la case
 * @return le type de la case sous forme de string : "V", "R", "P", et "#" pour autre
 */
std::string ParametresPartie::toStringZONE_TYPE(const ZONE_TYPE type) {

    std::string str;
    switch (type) {
        case ZONE_TYPE::PRE:
            str = "P";
            break;
        case ZONE_TYPE::VILLE:
            str = "V";
            break;
        case ZONE_TYPE::CHEMIN:
            str = "R";
            break;
        case ZONE_TYPE::AUTRE:
            str = "#";
            break;
        default:
            str = "?";
            break;
    }
    return str;
}

EXTENSION ParametresPartie::getExtensionChoisie() const {
    return extensionChoisie;
}

void ParametresPartie::setExtensionChoisie(EXTENSION extensionChoisie) {
    ParametresPartie::extensionChoisie = extensionChoisie;
}

int ParametresPartie::getNombreJoueurs() const {
    return nombreJoueurs;
}

void ParametresPartie::setNombreJoueurs(int nombreJoueurs) {
    ParametresPartie::nombreJoueurs = nombreJoueurs;
}
