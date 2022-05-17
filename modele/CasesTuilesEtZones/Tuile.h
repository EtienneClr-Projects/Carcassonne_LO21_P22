//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_TUILE_H
#define CARCASSONNE_LO21_P22_TUILE_H
#pragma once

class Tuile;

#include <map>
#include "Gestion/ParametresPartie.h"


class Tuile {
    std::string cheminImage;
public:

    explicit Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage);

    std::string toString();

    std::map<DIRECTION, Case *> cases;
};


#endif //CARCASSONNE_LO21_P22_TUILE_H
