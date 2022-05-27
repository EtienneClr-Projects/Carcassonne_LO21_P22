#ifndef CARCASSONNE_LO21_P22_TUILE_H
#define CARCASSONNE_LO21_P22_TUILE_H

#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>

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

Tuile::Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage) {
    this->cases = std::move(cases);
    this->cheminImage = std::move(cheminImage);
}

Case* Tuile::getCase(DIRECTION d )const{
    return cases.find(d)->second;
}
std::string Tuile::toString() {
    std::string res = "Tuile:\n";
    int i = 1;
    for (auto &it: cases) {
        res += it.second->toString()+std::to_string(it.second->getIdConnexion()) + " ";
        if (i % 3 == 0) res += "\n";
        i++;
    }
    return res + "\t" + cheminImage;
}

void Tuile::PivoterTuile( int nbre_rotation){
        std :: map<DIRECTION,Case*> t2;
        for (unsigned int i=0; i<nbre_rotation%4; i++) {//on decale les cases de 90 degres sans des aiguilles d'une montre
            t2[DIRECTION::NORD_OUEST] = cases.find(DIRECTION::SUD_OUEST)->second;
            t2[DIRECTION::NORD] = cases.find(DIRECTION::OUEST)->second;
            t2[DIRECTION::NORD_EST] = cases.find(DIRECTION::NORD_OUEST)->second;
            t2[DIRECTION::OUEST] = cases.find(DIRECTION::SUD)->second;
            t2[DIRECTION::MILIEU] = cases.find(DIRECTION::MILIEU)->second;
            t2[DIRECTION::EST] = cases.find(DIRECTION::NORD)->second;
            t2[DIRECTION::SUD_OUEST] = cases.find(DIRECTION::SUD_EST)->second;
            t2[DIRECTION::SUD] = cases.find(DIRECTION::EST)->second;
            t2[DIRECTION::SUD_EST] = cases.find(DIRECTION::NORD_EST)->second;
            cases = t2;
        }//on modifie egalement la direction à l'intérieur des cases
        t2[DIRECTION::NORD_OUEST]->setDirection(DIRECTION::NORD_OUEST);
        t2[DIRECTION::NORD]->setDirection(DIRECTION::NORD);
        t2[DIRECTION::NORD_EST]->setDirection(DIRECTION::NORD_EST);
        t2[DIRECTION::OUEST]->setDirection(DIRECTION::OUEST);
        t2[DIRECTION::MILIEU]->setDirection(DIRECTION::MILIEU);
        t2[DIRECTION::EST]->setDirection(DIRECTION::EST);
        t2[DIRECTION::SUD_OUEST]->setDirection(DIRECTION::SUD_OUEST);
        t2[DIRECTION::SUD]->setDirection(DIRECTION::SUD);
        t2[DIRECTION::SUD_EST]->setDirection(DIRECTION::SUD_EST);
        cases=t2;
    }

