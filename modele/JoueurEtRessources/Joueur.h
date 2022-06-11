#ifndef CARCASSONNE_LO21_P22_JOUEUR_H
#define CARCASSONNE_LO21_P22_JOUEUR_H

#include <utility>

#include "Gestion/ParametresPartie.h"

class Joueur {
private :
    /**
     * Le type du joueur : virtuel>0 ou réel=0
     */
    int type = 0;
    int points;
    std::string nom;
    COULEUR couleur;

public :
    Joueur(std::string n, COULEUR c) :
            couleur(c), nom(std::move(n)), points(0) {}

    int getNbPoints() const { return points; }

    std::string getNom() const { return nom; }

    COULEUR getCouleur() const { return couleur; }

    void ajouterPoints(int pt) { points = points + pt; }

    int getType() const {
        return type;
    }

    void setType(int _type) {
        type = _type;
    }

};

#endif //CARCASSONNE_LO21_P22_JOUEUR_H