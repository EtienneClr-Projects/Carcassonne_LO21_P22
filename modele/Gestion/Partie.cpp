//
// Created by etienne on 27/04/2022.
//

#include <iostream>
#include "Partie.h"


//L'instance de singleton de la classe Partie
Partie *Partie::instance = nullptr;

const vector<Joueur *> &Partie::getJoueurs() const {
    return joueurs;
}

Joueur *Partie::getJoueur(COULEUR couleur) {
    for (auto joueur: joueurs) {
        std::cout << "joueur: " << joueur << std::endl;
        if (joueur->getCouleur() == couleur) {
            return joueur;
        }
    }
    return nullptr;
}

void Partie::ajouterJoueur(Joueur *joueur) {
    joueurs.push_back(joueur);
}
