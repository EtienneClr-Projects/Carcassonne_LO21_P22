#ifndef CARCASSONNE_LO21_P22_JEU_H
#define CARCASSONNE_LO21_P22_JEU_H

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include "CasesTuilesEtZones/Tuile.h"
#include "JoueurEtRessources/Meeple.h"


using namespace std;
typedef std::vector<std::string> stringVec;

const string RESSOURCES = "Ressources/";
const string RESSOURCES_NORMALES = RESSOURCES + "Normal/";
const string RESSOURCES_RIVIERES = RESSOURCES + "Riviere/";
const string RESSOURCES_PAYSANS = RESSOURCES + "Paysans/";
const string RESSOURCES_ABBE = RESSOURCES + "Abbe/";
const string RESSOURCES_AUBERGES_CATHEDRALES = RESSOURCES + "AubergesCathedrales/";
const string RESSOURCES_MARCHANDS_BATISSEURS = RESSOURCES + "MarchandsBatisseurs/";

const string TUILES = "Tuiles/";
const string MEEPLES = "Meeples/";
const string SUPPLEMENTS = "Supplements/";

//donc un chemin vers les tuiles normales s'écrit : RESSOURCES_NORMALES + TUILES c'est à dire : Ressources/Normal/Tuiles/
//  et un chemin vers les meeples paysans s'écrit : RESSOURCES_PAYSANS + MEEPLES c'est à dire : Ressources/Paysans/Meeples/

class Jeu {
    static Jeu *instance;

    static void lireDossier(const std::string &chemin, stringVec &vecteurDeStrings);

    Jeu() = default;

    ~Jeu() {
        //todo
    }

    vector<EXTENSION> extension;
    vector<Tuile *> tuilesRiviere;

    static string getCheminFromExtension(EXTENSION ext);

    static map<DIRECTION, Case *> deepCopyMap(const map<DIRECTION, Case *> &map1);

public:

    vector<Tuile *> tuiles;

    //SINGLETON
    void setExtensions(const vector<EXTENSION> &extensions);

    static Jeu *getInstance() {
        if (instance == nullptr) {
            instance = new Jeu();
        }
        return instance;
    }

    static void libererJeu() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

    //METHODES

    void getTuilesDesRessources(EXTENSION _extension, vector<Tuile *> *_tuiles);

    void getMeeplesDesRessources(EXTENSION _extension, vector<Meeple *> *meeples);

    size_t getNbTuiles() { return tuiles.size(); }

    // désactivation de la duplication (par recopie et affectaion)
    Jeu(const Jeu &j) = delete;

    Jeu &operator=(const Jeu &j) = delete;

    vector<Meeple *> meeplesPossibleEnFonctionDesExtensions;
};


#endif //CARCASSONNE_LO21_P22_JEU_H
