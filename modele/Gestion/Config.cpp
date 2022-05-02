//
// Created by etienne on 27/04/2022.
//

#include "Config.h"

/**
 * Permet de transformer un DIRECTION en string pour de l'affichage
 * @param dir la DIRECTION
 * @return la direction sous forme de string. Par exemple "NORD_OUEST".
 */
std::string Config::toStringDirection(DIRECTION dir) {
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
std::string Config::toStringZone(Case _case) {
    std::string str;
    switch (_case.getZoneType()) {
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
    }
    return str;
}
