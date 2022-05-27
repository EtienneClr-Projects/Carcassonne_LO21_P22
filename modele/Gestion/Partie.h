#ifndef CARCASSONNE_LO21_P22_PARTIE_H
#define CARCASSONNE_LO21_P22_PARTIE_H

#include <vector>
#include "JoueurEtRessources/Joueur.h"

using namespace std;

//Partie est un Singleton
class Partie {
private:
    //SINGLETON
    static Partie *instance;
    Partie()=default;


    std::vector<Joueur*> joueurs;
public:
    const vector<Joueur *> &getJoueurs() const;

public:
    //SINGLETON
    Partie(const Partie&) = delete;
    Partie& operator=(const Partie&) = delete;
    static Partie& getInstance();

};


#endif //CARCASSONNE_LO21_P22_PARTIE_H
