//
// Created by etienne on 27/04/2022.
//

#include "Pioche.h"

Pioche::Pioche(std::vector<Tuile *> tuiles) {
    this->tuiles = tuiles;
    this->nbTuilesRestantes = tuiles.size();
}

/**
 * Renvoie la premiere tuile de la pioche et l'enleve de la pioche
 * @return la tuile au dessus de la pioche
 */
Tuile *Pioche::piocher() {
    Tuile *tuile = tuiles.front();
    tuiles.erase(tuiles.begin());
    nbTuilesRestantes--;
    return tuile;
}