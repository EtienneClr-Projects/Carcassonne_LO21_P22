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
    void fusionnerZonesAvecPlateau(Tuile* tuile);
    std::vector<Zone*> zones;
    void ajouterTuile(Tuile* tuile, Coord coord);
    std::string toString();

private :
    void fusionZones(Zone *zoneASuppr, Zone *zoneB);
    static bool fusionPossible(Zone* zone1, Zone* zone2);

    static std::vector<std::pair<int, Zone *>> calcZonesInternes(Tuile *pTuile);

    static void majOuverturesZonesCOTE(Tuile *pTuile);

    Coord findCoordTuile(Tuile *tuile);

    Tuile *findTuileVoisine(Coord coordTuile, int i);

    void fusionZonesCOINS(Tuile *tuile, int i, Tuile *tuileVoisine);
};


#endif //CARCASSONNE_LO21_P22_PLATEAU_H
