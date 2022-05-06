//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PRAIRIE_H
#define CARCASSONNE_LO21_P22_PRAIRIE_H

#pragma once
#include "Zone.h"

class Prairie : public Zone {
    std::vector<Zone *> villesAdjacentesFermees;

public:
    int compterNbVillesAdjacentesFermees();


};


#endif //CARCASSONNE_LO21_P22_PRAIRIE_H
