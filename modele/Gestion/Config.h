//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_CONFIG_H
#define CARCASSONNE_LO21_P22_CONFIG_H

#include <string>
#include "CasesTuilesEtZones/Case.h"

/**
 * Le type de la zone : PRE, VILLE, CHEMIN, ou AUTRE
 */
enum ZONE_TYPE {
    PRE, VILLE, CHEMIN, AUTRE
};
/**
 * La direction suivant les 9 cardinaux.
 * Par exemple NORD_OUEST.
 */
enum DIRECTION {
    NORD_OUEST, NORD, NORD_EST,
    EST, MILIEU, OUEST,
    SUD_EST, SUD, SUD_OUEST
};

constexpr static const DIRECTION ALL_DIRECTIONS[] = {NORD_OUEST, NORD, NORD_EST,
                                                     EST, MILIEU, OUEST,
                                                     SUD_EST, SUD, SUD_OUEST};

class Config {
public:
    static std::string toStringDirection(DIRECTION dir);

    static std::string toStringZone(Case _case);
};


#endif //CARCASSONNE_LO21_P22_CONFIG_H
