//
// Created by etienne on 27/04/2022.
//

#include "Jeu.h"
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

typedef std::vector<std::string> stringvec;

void Jeu::getTuilesDesRessources() {
    stringvec v;
    lireDossier("../" + TUILES_NORMALES, v);

    for (auto &s : v) {
        std::cout << s << std::endl;




    }
}

void Jeu::lireDossier(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_name[0] != '.') {
            v.push_back(dp->d_name);
        }
    }
    closedir(dirp);
}