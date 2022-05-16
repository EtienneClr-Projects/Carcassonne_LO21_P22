//
// Created by etienne on 27/04/2022.
//

#include <stdexcept>
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

/**
 * Renvoie l'extension choisie par l'utilisateur pour cette partie
 * @return l'extension choisie par l'utilisateur pour cette partie
 */
EXTENSION ParametresPartie::getExtensionChoisie() const {
    return extensionChoisie;
}

/**
 * Définit l'extension choisie par l'utilisateur pour cette partie
 * @param extChoisie l'extension choisie
 */
void ParametresPartie::setExtensionChoisie(EXTENSION extChoisie) {
    ParametresPartie::extensionChoisie = extChoisie;
}

/**
 * Renvoie le nombre de joueurs choisis par l'utilisateur pour cette partie
 * @return le nombre de joueurs
 */
int ParametresPartie::getNombreJoueurs() const {
    return nombreJoueurs;
}

/**
 * Définit le nombre de joueurs choisis par l'utilisateur pour cette partie
 * @param nbJoueurs le nombre de joueurs
 */
void ParametresPartie::setNombreJoueurs(int nbJoueurs) {
    ParametresPartie::nombreJoueurs = nbJoueurs;
}

/**
 * Permet de convertir le caractère représentant un type de zone en ZONE_TYPE
 * @param type le caractère représentant un type de zone
 * @return le type de zone
 */
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

/**
 * Permet de convertir le string représentant un meeple en MEEPLE_TYPE
 * @param str le string représentant un meeple
 * @return le MEEPLE_TYPE
 */
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
    else if (str == "C") {
        return MEEPLE_TYPE::COCHON;
    }
    else if (str =="B") {
        return MEEPLE_TYPE::BATISSEUR;
    }
    else {
        throw std::invalid_argument("Meeple type invalide");
    }
}

/**
 * Permet de convertir le string représentant une couleur en COULEUR
 * @param str le string représentant une couleur
 * @return la COULEUR
 */
COULEUR ParametresPartie::toCOULEUR(const std::string& str) {
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

/**
 * Permet de convertir une COULEUR en string
 * @param couleur la COULEUR
 * @return le string représentant la COULEUR
 */
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

/**
 * Permet de convertir un MEEPLE_TYPE en string
 * @param type le MEEPLE_TYPE
 * @return le string représentant le MEEPLE_TYPE
 */
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
            case MEEPLE_TYPE::COCHON:
            str = "C";
            break;
        case MEEPLE_TYPE::BATISSEUR:
            str = "B";
            break;
        default:
            str = "?";
            break;
    }
    return str;
}
//L'instance singleton de ParametresPartie
ParametresPartie* ParametresPartie::instance_ = nullptr;

/**
 * Permet de récupérer l'instance singleton de ParametresPartie
 * @return l'instance
 */
ParametresPartie *ParametresPartie::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new ParametresPartie();
    }
    return instance_;
}

/**
 * Transforme les EXTENSION en string
 * @param ext Extension à transformer
 * @return String correspondant à l'extension
 */
std::string ParametresPartie::toStringEXTENSION(EXTENSION ext) {
    switch (ext) {
        case EXTENSION::NORMAL:
            return "Normal";
        case EXTENSION::PAYSANS:
            return "Paysans";
        case EXTENSION::ABBE:
            return "Abbe";
        case EXTENSION::RIVIERE:
            return "Riviere";
        case EXTENSION::AUBERGES_CATHEDRALES:
            return "Auberges_Cathedrales";
        case EXTENSION::MARCHANDS_BATISSEURS:
            return "Marchands_Batisseurs";
        default:
            throw std::invalid_argument("Extension invalide");
    }
}
