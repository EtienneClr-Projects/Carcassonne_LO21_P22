//
// Created by etienne on 27/04/2022.
//

#include <iostream>
#include "JeuPiocheEtPlateau/Pioche.h"
#include "JeuPiocheEtPlateau/Jeu.h"

using namespace std;

int main() {
    cout << "Hello, Carcassonne !" << endl;
    vector<EXTENSION> extensionsChoisies;
//    extensionsChoisies.push_back(EXTENSION::NORMAL);
    extensionsChoisies.push_back(EXTENSION::RIVIERE);

    Jeu *jeu = Jeu::getInstance();
    jeu->setExtensions(extensionsChoisies);

//    for (auto tuile : *tuiles) {
//        cout << tuile->toString() << endl;
//    }

    auto * pioche = new Pioche(jeu->tuiles);
    Tuile* t = pioche->piocher();
    cout << t->toString() << endl;

    return 0;
}