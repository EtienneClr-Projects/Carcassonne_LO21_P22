#ifndef CARCASSONNE_LO21_P22_JOUEUR_H
#define CARCASSONNE_LO21_P22_JOUEUR_H
#include "Gestion/ParametresPartie.h"

class Joueur {

public :
    Joueur(const std::string &n, COULEUR c) :
            couleur(c), nom(n), points(0) {}

    int getNbPoints() const { return points; }

    std::string getNom() const { return nom; }

    COULEUR getCouleur() const { return couleur; }

    void ajouterPoints(int pt) { points = points + pt; }


private :
    int points;
    std::string nom;
    COULEUR couleur;

};

#endif //CARCASSONNE_LO21_P22_JOUEUR_H