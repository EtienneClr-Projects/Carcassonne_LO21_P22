//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PLATEAU_H
#define CARCASSONNE_LO21_P22_PLATEAU_H


#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"

class Plateau {
public:
    std::map<Coord, Tuile*> plateau;
    void fusionnerZones(Tuile* tuile);
    std::vector<Zone*> zones;
};


#endif //CARCASSONNE_LO21_P22_PLATEAU_H
