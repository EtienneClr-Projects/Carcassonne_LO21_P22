//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PRAIRIE_H
#define CARCASSONNE_LO21_P22_PRAIRIE_H

#pragma once
#include "Zone.h"
#include "Tuile.h"

class Prairie : public Zone {//todo en fait on s'en sert pas ?
    std::vector<Zone *> villesAdjacentesFermees;

    static std::vector<Case *> getCasesAdjacentes(Tuile *tuile, DIRECTION direction);

public:

    int compterNbVillesAdjacentesFermees();
};


#endif //CARCASSONNE_LO21_P22_PRAIRIE_H
