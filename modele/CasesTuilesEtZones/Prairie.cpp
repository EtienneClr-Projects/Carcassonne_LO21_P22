//
// Created by etienne on 27/04/2022.
//
#include <set>
#include "Prairie.h"

/**
 * Parcoure toutes les tuiles associées aux cases d'une zone et compte le nombre de villes adjacentes fermées.
 * Appelée à la fin du jeu pour compter les points de la prairie.
 * @return le nombre de villes adjacentes fermées
 */
int Prairie::compterNbVillesAdjacentesFermees() {
    int nbVillesAdjacentesFermees = 0;
    std::set<Zone *> villesAdjacentes;//Set : pour qu'il n'y ait pas de doublons

    //parcours des cases de la zone
    for (auto &cZone: cases) {
        //pour chaque case de la zone, on cherche ses cases adjacentes dans la tuile
        std::vector<Case *> voisins = getCasesAdjacentes(cZone->getTuileParente(), cZone->getDirection());

        //puis pour chaque voisin, on regarde si c'est une ville fermée
        for (auto &C: voisins) {
            if (C->getZoneType() == ZONE_TYPE::VILLE && !C->getZoneParente()->estOuverte()) {
                nbVillesAdjacentesFermees++;
            }
        }
    }

    return nbVillesAdjacentesFermees;
}

/**
 * Renvoie les cases adjacentes à une case de la zone.
 * @param tuile
 * @param direction
 * @return
 */
std::vector<Case *> Prairie::getCasesAdjacentes(Tuile *tuile, DIRECTION direction) {
    std::vector<Case *> casesAdjacentes;
    if (direction != DIRECTION::MILIEU) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::MILIEU]);
    }
    if (direction == DIRECTION::NORD) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::SUD) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::EST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
    }
    if (direction == DIRECTION::OUEST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
    }
    if (direction == DIRECTION::NORD_EST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::NORD_OUEST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
    }
    if (direction == DIRECTION::SUD_EST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::SUD_OUEST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
    }
    return casesAdjacentes;
}
