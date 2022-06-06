#include <stdexcept>
#include <utility>
#include <iostream>
#include "ParametresPartie.h"

//L'instance singleton de ParametresPartie
ParametresPartie *ParametresPartie::instance_ = nullptr;

/**
 * Permet de récupérer l'instance singleton de ParametresPartie
 * @return l'instance
 */
ParametresPartie * ParametresPartie::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new ParametresPartie();
    }
    return instance_;
}

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
 * Renvoie l'extensions choisie par l'utilisateur pour cette partie
 * @return l'extensions choisie par l'utilisateur pour cette partie
 */
std::vector<EXTENSION> ParametresPartie::getExtensionsChoisies() const {
    return extensionsChoisies;
}

/**
 * Définit l'extensions choisie par l'utilisateur pour cette partie
 * @param extChoisie l'extensions choisie
 */
void ParametresPartie::setExtensionsChoisies(std::vector<EXTENSION> extsChoisies) {
    ParametresPartie::extensionsChoisies = std::move(extsChoisies);
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
            throw std::invalid_argument("Type de zone invalide (toZONE_TYPE) : " + std::string(1, type));
    }
}

/**
 * Renvoie le type de la case en string pour de l'affichage
 * @param _case la case
 * @return le type de la case sous forme de string : "V", "R", "P", et "#" pour autre
 */
std::string ParametresPartie::toStringZONE_TYPE(const ZONE_TYPE type) {
    switch (type) {
        case ZONE_TYPE::PRAIRIE:
            return "P";
        case ZONE_TYPE::VILLE:
            return "V";
        case ZONE_TYPE::CHEMIN:
            return "C";
        case ZONE_TYPE::RIVIERE:
            return "R";
        case ZONE_TYPE::FIN_DE_ROUTE:
            return "#";
        case ZONE_TYPE::ABBAYE:
            return "A";
        case ZONE_TYPE::JARDIN:
            return "J";
        case ZONE_TYPE::LAC:
            return "L";
        case ZONE_TYPE::SOURCE:
            return "S";
        case ZONE_TYPE::CATHEDRALE:
            return "c";
        default:
            throw std::invalid_argument("Type de zone invalide (toString Zone)");
    }
}

/**
 * Permet de convertir le string représentant un meeple en MEEPLE_TYPE
 * @param str le string représentant un meeple
 * @return le MEEPLE_TYPE
 */
MEEPLE_TYPE ParametresPartie::toMEEPLE_TYPE(const std::string &str) {
    if (str == "N") {
        return MEEPLE_TYPE::NORMAL;
    } else if (str == "G") {
        return MEEPLE_TYPE::GRAND_MEEPLE;
    } else if (str == "A") {
        return MEEPLE_TYPE::ABBE;
    } else if (str == "C") {
        return MEEPLE_TYPE::COCHON;
    } else if (str == "B") {
        return MEEPLE_TYPE::BATISSEUR;
    } else {
        throw std::invalid_argument("Meeple type invalide");
    }
}

/**
 * Permet de convertir le string représentant une couleur en COULEUR
 * @param str le string représentant une couleur
 * @return la COULEUR
 */
COULEUR ParametresPartie::toCOULEUR(const std::string &str) {
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

/**
 * Transforme les EXTENSIONs en string
 * @param exts Extensions à transformer
 * @return String correspondant aux extensions fournies
 */
std::string ParametresPartie::toStringEXTENSIONS(const std::vector<EXTENSION> &exts) {
    std::string str;
    for (EXTENSION ext: exts) {
        str += toStringEXTENSION(ext) + ", ";
    }
    return str;
}

std::string ParametresPartie::toStringSUPP_TYPE(SUPP_TYPE type) {
    switch (type) {
        case SUPP_TYPE::BLASON:
            return "Bla";
        case SUPP_TYPE::AUBERGE:
            return "Aub";
        case SUPP_TYPE::BLE:
            return "Ble";
        case SUPP_TYPE::TONNEAU:
            return "Ton";
        case SUPP_TYPE::TISSU:
            return "Tis";
        case SUPP_TYPE::AUCUN:
            return " ";
        default:
            throw std::invalid_argument("Type de supplement invalide");
    }
}

Coord *ParametresPartie::toDeplacement(DIRECTION direction) {
    switch (direction) {
        case DIRECTION::NORD:
            return new Coord(0, -1);
        case DIRECTION::SUD:
            return new Coord(0, 1);
        case DIRECTION::EST:
            return new Coord(1, 0);
        case DIRECTION::OUEST:
            return new Coord(-1, 0);
        default:
            throw std::invalid_argument("Direction invalide");
    }
}

std::vector<DIRECTION> ParametresPartie::getCoinsAvecCote(DIRECTION cote) {
    std::vector<DIRECTION> coins;
    switch (cote) {
        case DIRECTION::NORD:
            coins.push_back(DIRECTION::NORD_OUEST);
            coins.push_back(DIRECTION::NORD_EST);
            break;
        case DIRECTION::SUD:
            coins.push_back(DIRECTION::SUD_OUEST);
            coins.push_back(DIRECTION::SUD_EST);
            break;
        case DIRECTION::EST:
            coins.push_back(DIRECTION::NORD_EST);
            coins.push_back(DIRECTION::SUD_EST);
            break;
        case DIRECTION::OUEST:
            coins.push_back(DIRECTION::NORD_OUEST);
            coins.push_back(DIRECTION::SUD_OUEST);
            break;
        default:
            throw std::invalid_argument("Direction invalide");
    }
    return coins;
}

DIRECTION ParametresPartie::getDirDeCasePourTuileVoisine(DIRECTION dirCaseActuelle, DIRECTION dirOuRegarder) {
    switch (dirCaseActuelle) {
        case DIRECTION::NORD_OUEST:
            if (dirOuRegarder == DIRECTION::NORD) return DIRECTION::SUD_OUEST;
            else return DIRECTION::NORD_EST;
        case DIRECTION::NORD_EST:
            if (dirOuRegarder == DIRECTION::NORD) return DIRECTION::SUD_EST;
            else return DIRECTION::NORD_OUEST;
        case DIRECTION::SUD_OUEST:
            if (dirOuRegarder == DIRECTION::SUD) return DIRECTION::NORD_OUEST;
            else return DIRECTION::SUD_EST;
        case DIRECTION::SUD_EST:
            if (dirOuRegarder == DIRECTION::SUD) return DIRECTION::NORD_EST;
            else return DIRECTION::SUD_OUEST;
        default:
            throw std::invalid_argument("Direction invalide");
    }
}

std::string ParametresPartie::toStringEXTENSION(EXTENSION ext) {
    switch (ext) {
        case EXTENSION::NORMAL:
            return "Normal";
        case EXTENSION::ABBE:
            return "Abbe";
        case EXTENSION::RIVIERE:
            return "Riviere";
        case EXTENSION::AUBERGES_CATHEDRALES:
            return "Auberges & Cathedrales";
        case EXTENSION::MARCHANDS_BATISSEURS:
            return "Marchands & Batisseurs";
        case EXTENSION::PAYSANS:
            return "Paysans";
        default:
            throw std::invalid_argument("Extension invalide");
    }
}
