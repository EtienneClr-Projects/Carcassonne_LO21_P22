//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_JEU_H
#define CARCASSONNE_LO21_P22_JEU_H
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
using namespace std;
typedef std::vector<std::string> stringvec;

const string RESSOURCES = "Ressources/";
const string TUILES_NORMALES = RESSOURCES+"TuilesNormales/";
const string TUILES_RIVIERES = RESSOURCES+"TuilesRiviere/";

class Jeu {
    static void lireDossier(const std::string& name, stringvec& v);
public:
    static void getTuilesDesRessources();
};


#endif //CARCASSONNE_LO21_P22_JEU_H
