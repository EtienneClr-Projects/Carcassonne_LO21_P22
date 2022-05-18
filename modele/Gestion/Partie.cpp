//
// Created by etienne on 27/04/2022.
//

#include "Partie.h"


//L'instance de singleton de la classe Partie
Partie *Partie::instance = nullptr;

Partie &Partie::getInstance() {
    if (instance == nullptr) {
        instance = new Partie();
    }
    return *instance;
}

const vector<Joueur *> &Partie::getJoueurs() const {
    return joueurs;
}