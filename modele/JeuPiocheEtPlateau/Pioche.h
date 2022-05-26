//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PIOCHE_H
#define CARCASSONNE_LO21_P22_PIOCHE_H
#include <iostream>
#include "CasesTuilesEtZones/Tuile.h"

using namespace std;

class Pioche {
private:
    std::vector<Tuile *> tuiles;
    int nbTuilesRestantes;
public:
    Pioche(std::vector<Tuile*> tuiles);
    Tuile* piocher();
};


#endif //CARCASSONNE_LO21_P22_PIOCHE_H
