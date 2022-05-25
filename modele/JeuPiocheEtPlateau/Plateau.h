//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PLATEAU_H
#define CARCASSONNE_LO21_P22_PLATEAU_H


#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"

class Plateau {
public:
    std::vector<std::pair<Coord, Tuile*>> plateau;
    void fusionnerZones(Tuile* tuile);
    std::vector<Zone*> zones;
    void ajouterTuile(Tuile* tuile, Coord coord);
    std::string toString();

private :
    void fusionZoneCase(Zone *zone, Case *caseAFusionner);
};


#endif //CARCASSONNE_LO21_P22_PLATEAU_H
