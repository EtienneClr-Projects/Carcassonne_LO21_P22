#ifndef CARCASSONNE_LO21_P22_PLATEAU_H
#define CARCASSONNE_LO21_P22_PLATEAU_H

static const int tailleMaxPlateau = 200;

#include <cstdio>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>
#include <vector>
#include <dirent.h>
#include "CasesTuilesEtZones/Tuile.h"
#include "CasesTuilesEtZones/Case.h"
#include "JoueurEtRessources/Joueur.h"
#include "JoueurEtRessources/Meeple.h"
#include "CasesTuilesEtZones/Zone.h"
#include "Gestion/Coord.h"
#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"

using namespace std;

class Plateau {
private :
    static Plateau *instance;
    std::vector<std::pair<Coord *, Tuile *>> plateau;
    DIRECTION dirSource;
public:
    void setDirSource(DIRECTION dirSource);

private:

    explicit Plateau(const vector<std::pair<Coord *, Tuile *>> &p) : plateau(p) {};

    Plateau() {
        plateau = {};
    };

    ~Plateau() = default;

    vector<Zone *> zones;

    void transfererZone(Zone *zoneASuppr, Zone *zoneB);

    static bool fusionPossible(Zone *zone1, Zone *zone2);

    Tuile *findTuileVoisine(Coord *coordTuile, int i);

    void fusionZonesCOINS(Tuile *tuile, int i, Tuile *tuileVoisine);

    void donnerPointsPourJoueurFinDePartie(Joueur *pJoueur, Zone *pZone);

public:
    static Coord * findCoordTuile(Tuile *tuile);//doit être public pour permettre à l'interface de connaître position des tuiles

    void fusionnerZonesAvecPlateau(Tuile *tuile);

    void ajouterTuile(Tuile *tuile, Coord *coord);

    std::string toString();

    bool retirerLeMeeple(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve, Case *c);

    std::vector<Coord*> retirerMeeples(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve);

    bool checkerTuile(Tuile *tuile, Coord *coord);

    bool poserMeeple(COULEUR couleur, Case *c, MEEPLE_TYPE type, vector<Meeple *> &meeplesPoses,
                     vector<Meeple *> &meeplesEnReserve);

    static Plateau *getInstance(const vector<std::pair<Coord *, Tuile *>> &plateau) {
        if (instance == nullptr) {
            instance = new Plateau(plateau);
        }
        return instance;
    }

    static Plateau *getInstance() {
        if (instance == nullptr) {
            instance = new Plateau();
        }
        return instance;
    }

    static void libererInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

    void afficherConsole();

    Coord *getCoinHautGauche();

    Coord *getCoinBasDroite();

    Coord *retirerAbbe(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve, COULEUR couleur);

    static void ColorForZone(void *console_color, const Case *c);

    void donnerPointsPourJoueur(Joueur *pJoueur, Zone *pZone);


    int CompterVoisins(Tuile *tuile);

    static std::vector<Case *> getCasesAdjacentes(Tuile *tuile, DIRECTION direction);

    static int compterNbVillesAdjacentesFermees(Zone *prairie);

    void finDePartie();

    static int nombreDePrairie;
};

#endif //CARCASSONNE_LO21_P22_PLATEAU_H
