//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_CONFIG_H
#define CARCASSONNE_LO21_P22_CONFIG_H
#pragma once
#include <string>

/**
 * Le type de la zone : PRE, VILLE, CHEMIN, ou AUTRE
 */
enum class ZONE_TYPE {
    PRE, VILLE, CHEMIN, AUTRE
};
/**
 * La direction suivant les 9 cardinaux.
 * Par exemple NORD_OUEST.
 */
enum class DIRECTION {
    NORD_OUEST, NORD, NORD_EST,
    EST, MILIEU, OUEST,
    SUD_EST, SUD, SUD_OUEST
};

constexpr static const DIRECTION ALL_DIRECTIONS[] = {DIRECTION::NORD_OUEST, DIRECTION::NORD, DIRECTION::NORD_EST,
                                                     DIRECTION::EST, DIRECTION::MILIEU, DIRECTION::OUEST,
                                                     DIRECTION::SUD_EST, DIRECTION::SUD, DIRECTION::SUD_OUEST};

#include "CasesTuilesEtZones/Case.h"

class Config {
public:
    static std::string toStringDIRECTION(const DIRECTION dir);

    static std::string toStringZONE_TYPE(const ZONE_TYPE type);
};


#endif //CARCASSONNE_LO21_P22_CONFIG_H
