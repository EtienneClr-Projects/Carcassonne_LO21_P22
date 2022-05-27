#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>
#include <vector>
#include <dirent.h>
#include "CasesTuilesEtZones/Tuile.h"
#include "CasesTuilesEtZones/Case.h"
#include "JoueurEtRessources/Joueur.h"
#include "JoueurEtRessources/Meeple.h"
#include "CasesTuilesEtZones/Zone.h"
#include "Gestion/Coord.h"

using namespace std;


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

public:
    void retirerMeeple(vector<Meeple *>& meeplesPoses, vector<Meeple *>& meeplesEnReserve);
    bool checkerTuile(Tuile * t,Coord coord);
    static bool poserMeeple(Joueur *j, Case * c, MEEPLE_TYPE  type, vector<Meeple*>meeplesPoses, vector<Meeple*> meeplesEnReserve);
    static Plateau *getInstance(const vector<std::pair<Coord, Tuile *>> &plateau){
        if(instance==nullptr){
            instance=new Plateau(plateau);
        }
        return instance;
    }
    static void libererInstance(){
        if (instance!=nullptr){
            delete instance;
            instance=nullptr;
        }
    }

private:
    static Plateau * instance;
    std::vector<std::pair<Coord,Tuile*>> plateau;
    Plateau(const vector<std::pair<Coord, Tuile *>> &p):plateau(p){};
    ~Plateau() = default;
    vector<Zone*> zones;
};

#endif //CARCASSONNE_LO21_P22_PLATEAU_H
