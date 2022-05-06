//
// Created by etienne on 27/04/2022.
//
#include <set>
#include "Prairie.h"

/**
 * Parcoure toutes les tuiles associées aux cases d'une zone et compte le nombre de villes adjacentes fermees.
 * Appelée à la fin du jeu pour compter les points de la prairie.
 * @return le nombre de villes adjacentes fermées
 */
int Prairie::compterNbVillesAdjacentesFermees() {
    std::set<Zone *> villesAdjacentes;//Set : pour qu'il n'y ait pas de doublons
    for (auto &Case: cases) {
        Tuile &tuile = Case->getTuileParente();
        for (auto &caseDeLaTuile: tuile.getCases()) {
            if (caseDeLaTuile->getZoneType() == ZONE_TYPE::VILLE) {
                villesAdjacentes.insert(caseDeLaTuile->getZone());
            }
        }
    }

    int nbVillesAdjacentesFermees = 0;
    for (auto &ville: villesAdjacentes) {
        if (!ville->estOuverte()) {
            nbVillesAdjacentesFermees++;
        }
    }
    return nbVillesAdjacentesFermees;
}
