
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

const string TUILES = "Tuiles/";
const string MEEPLES = "Meeples/";

//donc un chemin vers les tuiles normales s'écrit : RESSOURCES_NORMALES + TUILES c'est à dire : Ressources/Normal/Tuiles/
//  et un chemin vers les meeples paysans s'écrit : RESSOURCES_PAYSANS + MEEPLES c'est à dire : Ressources/Paysans/Meeples/

class Jeu {
    static void lireDossier(const std::string &chemin, stringVec &vecteurDeStrings);

public:
    static map<DIRECTION, Case *> deepCopyMap(const map<DIRECTION, Case *>& map1);

    static void getTuilesDesRessources(EXTENSION extension, vector<Tuile *> *tuiles);
    static void getMeeplesDesRessources(EXTENSION extension, vector<Meeple *> *meeples);

    static string getCheminFromExtension(EXTENSION extension);

};

#endif //CARCASSONNE_LO21_P22_JEU_H
