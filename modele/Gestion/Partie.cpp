//
// Created by etienne on 27/04/2022.
//

#include "Partie.h"


//L'instance de singleton de la classe Partie
Partie *Partie::instance = nullptr;

const vector<Joueur *> &Partie::getJoueurs() const {
    return joueurs;
}

Joueur *Partie::getJoueur(COULEUR couleur) {
    for (auto joueur: joueurs) {
        if (joueur->getCouleur() == couleur) {
            return joueur;
        }
    }
    return nullptr;
}

void Partie::ajouterJoueur(Joueur *joueur) {
    joueurs.push_back(joueur);
}
