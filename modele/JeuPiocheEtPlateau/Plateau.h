//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PLATEAU_H
#define CARCASSONNE_LO21_P22_PLATEAU_H

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

using namespace Carcassonne;


bool operator==(Joueur left, const map<Coord, Tuile *> &right);

bool operator==(const map<DIRECTION, Case *> &left, const map<DIRECTION, Case *> &right);

bool operator==(const DIRECTION &left, const DIRECTION &right);

class Plateau {
public:
    Plateau(const vector<std::pair<Coord, Tuile *>> &plateau);

    static bool checkerTuile(Tuile *t, Coord coord);

    static bool
    poserMeeple(Joueur *j, Case *c, MEEPLE_TYPE type, vector<Meeple *> meeplesPoses, vector<Meeple *> meeplesEnReserve);

private:
    static std::vector<std::pair<Coord, Tuile *>> plateau;
    Zone **zones;
};

#endif //CARCASSONNE_LO21_P22_PLATEAU_H
