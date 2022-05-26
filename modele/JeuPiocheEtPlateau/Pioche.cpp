//
// Created by etienne on 27/04/2022.
//

#include "Pioche.h"

Pioche::Pioche(std::vector<Tuile *> tuiles) {
    this->tuiles = tuiles;
    this->nbTuilesRestantes = tuiles.size();
}

Tuile *Pioche::piocher() {
    //renvoie une tuile au hasard
    if (nbTuilesRestantes == 0) {
        return nullptr;
    }
    int index = rand() % nbTuilesRestantes;
    Tuile *tuile = tuiles[index];
    tuiles.erase(tuiles.begin() + index);
    nbTuilesRestantes--;
    return tuile;
}

