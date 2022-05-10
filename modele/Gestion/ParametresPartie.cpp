//
// Created by etienne on 27/04/2022.
//

#include <stdexcept>
#include <iostream>
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
        case ZONE_TYPE::PRAIRIE:
            str = "P";
            break;
        case ZONE_TYPE::VILLE:
            str = "V";
            break;
        case ZONE_TYPE::CHEMIN:
            str = "C";
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

void ParametresPartie::setExtensionChoisie(EXTENSION extChoisie) {
    ParametresPartie::extensionChoisie = extChoisie;
}

int ParametresPartie::getNombreJoueurs() const {
    return nombreJoueurs;
}

void ParametresPartie::setNombreJoueurs(int nbJoueurs) {
    ParametresPartie::nombreJoueurs = nbJoueurs;
}

ZONE_TYPE ParametresPartie::toZONE_TYPE(char type) {
    switch (type) {
        case 'P':
            return ZONE_TYPE::PRAIRIE;
        case 'V':
            return ZONE_TYPE::VILLE;
        case 'C':
            return ZONE_TYPE::CHEMIN;
        case 'R':
            return ZONE_TYPE::RIVIERE;
        case 'F':
            return ZONE_TYPE::FIN_DE_ROUTE;
        case 'A':
            return ZONE_TYPE::ABBAYE;
        case 'J':
            return ZONE_TYPE::JARDIN;
        case 'L':
            return ZONE_TYPE::LAC;
        case 'S':
            return ZONE_TYPE::SOURCE;
        case 'c':
            return ZONE_TYPE::CATHEDRALE;
        default:
            throw std::invalid_argument("Type de zone invalide");
    }
}

MEEPLE_TYPE ParametresPartie::toMEEPLE_TYPE(const std::string& str) {
    if (str == "N") {
        return MEEPLE_TYPE::NORMAL;
    }
    else if (str == "G") {
        return MEEPLE_TYPE::GRAND_MEEPLE;
    }
    else if (str=="A") {
        return MEEPLE_TYPE::ABBE;
    }
    else {
        throw std::invalid_argument("Meeple type invalide");
    }
}

COULEUR ParametresPartie::toCOULEUR(const std::string& str) {
    //simplify previous code with switch
    switch (str[0]) {
        case 'R':
            return COULEUR::ROUGE;
        case 'V':
            return COULEUR::VERT;
        case 'B':
            return COULEUR::BLEU;
        case 'J':
            return COULEUR::JAUNE;
        case 'N':
            return COULEUR::NOIR;
        default:
            throw std::invalid_argument("Couleur invalide");
    }
}

std::string ParametresPartie::toStringCOULEUR(COULEUR couleur) {
    switch (couleur) {
        case COULEUR::ROUGE:
            return "R";
        case COULEUR::VERT:
            return "V";
        case COULEUR::BLEU:
            return "B";
        case COULEUR::JAUNE:
            return "J";
        case COULEUR::NOIR:
            return "N";
        default:
            throw std::invalid_argument("Couleur invalide");
    }
}

std::string ParametresPartie::toStringMEEPLE_TYPE(MEEPLE_TYPE type) {
    std::string str;
    switch (type) {
        case MEEPLE_TYPE::NORMAL:
            str = "N";
            break;
        case MEEPLE_TYPE::GRAND_MEEPLE:
            str = "G";
            break;
        case MEEPLE_TYPE::ABBE:
            str = "A";
            break;
        default:
            str = "?";
            break;
    }
    return str;
}
