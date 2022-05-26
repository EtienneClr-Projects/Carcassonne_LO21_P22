//
// Created by etienne on 27/04/2022.
//

#include "Plateau.h"

#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>
#include <vector>
#include <dirent.h>
#include <vector>


bool Plateau::checkerTuile(Tuile *tuile, Coord coord) {

    auto voisin_droit = coord;
    voisin_droit.x_++;
    auto voisin_gauche = coord;
    voisin_gauche.x_--;
    auto voisin_haut = coord;
    voisin_haut.y_++;
    auto voisin_bas = coord;
    voisin_bas.y_--;
    map<DIRECTION, Case *> t = tuile->getTuile();

    for (std::pair<Coord, Tuile *> pairTuile:plateau) {
        map<DIRECTION, Case *> pt = pairTuile.second->getTuile();
        if (voisin_droit == pairTuile.first) {
            if (t[DIRECTION::EST]->getZoneType() != pt[DIRECTION::OUEST]->getZoneType()) return false;
        }
        if (voisin_gauche == pairTuile.first) {
            if (t[DIRECTION::OUEST]->getZoneType() != pt[DIRECTION::EST]->getZoneType()) return false;
        }
        if (voisin_haut == pairTuile.first) {
            if (t[DIRECTION::NORD]->getZoneType() != pt[DIRECTION::SUD]->getZoneType()) return false;
        }
        if (voisin_bas == pairTuile.first) {
            if (t[DIRECTION::SUD]->getZoneType() != pt[DIRECTION::NORD]->getZoneType()) return false;
        }
    }
    return true;
}

bool Plateau::poserMeeple(Joueur *j, Case *c, MEEPLE_TYPE type, vector<Meeple *> meeplesPoses,
                          vector<Meeple *> meeplesEnReserve) {
    Zone zone = c->getZoneParente();
    if (nullptr == zone.getGagnant()) {// si pas de meeple déjà posé dans la zone

        COULEUR couleur = j->getCouleur();
        unsigned int i = 0;
        while ((couleur != meeplesEnReserve[i]->getCouleur() or
                type != meeplesEnReserve[i]->getType()) and i <= meeplesEnReserve.size()) { i++; }

        //retirer du tableau "meeple en réserve" le meeple
        if (i > meeplesEnReserve.size()) {
            throw CarcassonneException("pas de meeple de ce type et de cette couleur disponible");
        }
        c->setMeeplePose(meeplesEnReserve[i]);
        meeplesPoses.push_back(meeplesEnReserve[i]);
        meeplesEnReserve.erase(meeplesEnReserve.begin() + i);
        //on met le meeple dans le bon tableau
        return true;

    } else { return false; }


}

Plateau::Plateau(const std::vector<std::pair<Coord, Tuile *>> &plat) : plateau(plat), zones(nullptr) {}

