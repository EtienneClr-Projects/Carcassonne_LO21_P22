#ifndef CARCASSONNE_LO21_P22_PARTIE_H
#define CARCASSONNE_LO21_P22_PARTIE_H

#include <vector>
#include "JoueurEtRessources/Joueur.h"
#include "JoueurEtRessources/Meeple.h"

using namespace std;

//Partie est un Singleton
class Partie {
private:
    Partie() = default;

//SINGLETON
    static Partie *instance;

    std::vector<Joueur *> joueurs;
public:
    const vector<Joueur *> &getJoueurs() const;

    //SINGLETON
    Partie(const Partie &) = delete;

    Partie &operator=(const Partie &) = delete;

    static Partie *getInstance() {
        if (instance == nullptr) {
            instance = new Partie();
        }
        return instance;
    }

    Joueur *getJoueur(COULEUR couleur);

    vector<Meeple *> meeplesPoses;

    vector<Meeple *> meeplesEnReserve;

    void ajouterJoueur(Joueur *joueur);
};


#endif //CARCASSONNE_LO21_P22_PARTIE_H
