#ifndef CARCASSONNE_LO21_P22_TUILE_H
#define CARCASSONNE_LO21_P22_TUILE_H
#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <initializer_list>
#include <map>
#include <cstdlib>

class Tuile;

#include "Gestion/ParametresPartie.h"
#include "CasesTuilesEtZones/Case.h"

class Tuile {
    std::string cheminImage;
    std::vector<Zone *> zonesInternes;

public:
    std::vector<Zone *> getZonesInternes() { return zonesInternes; };

    explicit Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage);

    std::string toString();

    Case *getCase(DIRECTION d) const;

    void pivoterTuileSensTrigo(int nbre_rotation);

    std::map<DIRECTION, Case *> getCases() const;

    std::map<DIRECTION, Case *> cases;

    bool estLac();

    bool estSource();

    void afficher() const;

    void fusionZonesInternes();

    void majOuverturesZonesCOTE(Tuile *pTuile);

    std::vector<std::pair<int, Zone *>> calcZonesInternes();

};

#endif