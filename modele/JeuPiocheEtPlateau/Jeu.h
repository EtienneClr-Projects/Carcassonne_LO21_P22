
#ifndef CARCASSONNE_LO21_P22_JEU_H
#define CARCASSONNE_LO21_P22_JEU_H

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include "CasesTuilesEtZones/Tuile.h"

using namespace std;
typedef std::vector<std::string> stringVec;

const string RESSOURCES = "Ressources/";
const string RESSOURCES_NORMALES = RESSOURCES + "TuilesNormales/";
const string RESSOURCES_RIVIERES = RESSOURCES + "TuilesRiviere/";
const string RESSOURCES_PAYSANS = RESSOURCES + "TuilesPaysans/";
const string RESSOURCES_ABBE = RESSOURCES + "TuilesAbbe/";
const string RESSOURCES_AUBERGES_CATHEDRALES = RESSOURCES + "TuilesAubergesCathedrales/";

class Jeu {
    static void lireDossier(const std::string &chemin, stringVec &vecteurDeStrings);

public:
    static map<DIRECTION, Case *> deepCopyMap(const map<DIRECTION, Case *>& map1);

    static void getTuilesDesRessources(EXTENSION extension, vector<Tuile *> *tuiles);
};


#endif //CARCASSONNE_LO21_P22_JEU_H
