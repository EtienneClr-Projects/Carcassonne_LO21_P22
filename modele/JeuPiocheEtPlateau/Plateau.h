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
#include "Tuile.hpp"

using namespace Carcassonne;

class Coord
    {
    public:
        int x;
        int y;
};


bool operator==(const map <Coord,Tuile*>& left, const map <Coord,Tuile*>& right);
bool operator==(const map<DIRECTION,Case*>& left, const map<DIRECTION,Case*>& right);
bool operator==(const DIRECTION& left, const DIRECTION& right);

class Plateau{
public:
    void poserTuile(Tuile * t,Coord coord);
    void poserMeeple(Tuile * t,Case * c);

private:
    map<Coord,Tuile*> plateau;
};

#endif //CARCASSONNE_LO21_P22_PLATEAU_H
