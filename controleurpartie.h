#ifndef CONTROLEURPARTIE_H
#define CONTROLEURPARTIE_H


#include <iostream>
#include "modele/JeuPiocheEtPlateau/Pioche.h"
#include "modele/JeuPiocheEtPlateau/Jeu.h"
#include "modele/JeuPiocheEtPlateau/Plateau.h"
#include "modele/Gestion/ParametresPartie.h"
#include "modele/Gestion/Coord.h"
#include "modele/Gestion/Partie.h"

class controleurPartie {
public:
    controleurPartie(int nb_joueurs, bool exPaysans, bool exAbbe, bool exCathAub, bool exRiviere);

    ~controleurPartie();

    Jeu *getJeu() const { return jeu; }

    Pioche *getPioche() const { return pioche; }

    Plateau *getPlateau() const { return plateau; }

    ParametresPartie *getParametresPartie() const { return pPartie; }

    Partie * getpartie() {return partie;}


private:
    Partie *partie;
    Jeu *jeu;
    Pioche *pioche = nullptr;
    Plateau *plateau;
    ParametresPartie *pPartie;
    vector<pair<Coord, Tuile *>> tuilesPlateau;


};

#endif // CONTROLEURPARTIE_H
