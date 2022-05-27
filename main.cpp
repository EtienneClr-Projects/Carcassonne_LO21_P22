//
// Created by etienne on 27/04/2022.
//

#include <iostream>
#include "JeuPiocheEtPlateau/Pioche.h"
#include "JeuPiocheEtPlateau/Jeu.h"
#include "JeuPiocheEtPlateau/Plateau.h"

using namespace std;

void test_Jeu_Pioche_Tuile() {
    cout << "Hello, Carcassonne !" << endl;
    vector<EXTENSION> extensionsChoisies;
    extensionsChoisies.push_back(EXTENSION::NORMAL);
    extensionsChoisies.push_back(EXTENSION::ABBE);
    extensionsChoisies.push_back(EXTENSION::AUBERGES_CATHEDRALES);
    extensionsChoisies.push_back(EXTENSION::MARCHANDS_BATISSEURS);

    Jeu *jeu = Jeu::getInstance();
    jeu->setExtensions(extensionsChoisies);
    for (auto meeple: jeu->meeplesPossibleEnFonctionDesExtensions) {
        cout << meeple->toString() << endl;
    }
    cout << "\n" << endl;

    //test de la pioche
    auto *pioche = new Pioche(jeu->tuiles);
    Tuile *t = pioche->piocher();
    cout << t->toString() << endl;


    //test des tuilesPlateau
//    t->pivoterTuileSensTrigo(1);
//    cout << t->toString() << endl;
//    cout << t->getCase(DIRECTION::NORD_EST)->toString() << endl;

    vector<pair < Coord, Tuile *>>
    tuilesPlateau;
    for (int i = 0; i < 2; i++) {
        auto *TT = pioche->piocher();
        Coord coord = Coord(0, i);
        tuilesPlateau.emplace_back(coord, TT);
        cout << TT->toString() << endl;
    }

    Plateau *plateau = Plateau::getInstance(tuilesPlateau);
    plateau->ajouterTuile(tuilesPlateau[0].second, tuilesPlateau[0].first);
    plateau->checkerTuile(tuilesPlateau[0].second, tuilesPlateau[0].first);
    cout << plateau->checkerTuile(tuilesPlateau[1].second, tuilesPlateau[1].first) << endl;
}


int main() {
    test_Jeu_Pioche_Tuile();
    return 0;
}