//
// Created by etienne on 27/04/2022.
//


#include "Jeu.h"
#include "CasesTuilesEtZones/Case.h"
#include <string>
#include <vector>
#include <dirent.h>
#include "CasesTuilesEtZones/Tuile.h"

typedef std::vector<std::string> stringVec;

void Jeu::getTuilesDesRessources(EXTENSION extension, vector<Tuile *> *tuiles) {
    std::string chemin; //on récupère le chemin du dossier en fonction de l'extension demandée
    switch (extension) {
        case EXTENSION::NORMAL:
            chemin = RESSOURCES_NORMALES;
            break;
        case EXTENSION::PAYSANS:
            chemin = RESSOURCES_PAYSANS;
            break;
        case EXTENSION::ABBE:
            chemin = RESSOURCES_ABBE;
            break;
        case EXTENSION::RIVIERE:
            chemin = RESSOURCES_RIVIERES;
            break;
        case EXTENSION::AUBERGES_CATHEDRALES:
            chemin = RESSOURCES_AUBERGES_CATHEDRALES;
            break;
    }

    stringVec v;
    lireDossier("../" + chemin, v);

    //pour chaque nom de fichier
    for (auto &s: v) {
        //on parcourt chaque caractère de la chaine
        int nbTuilesDeCeType = (int) s[0] - 48; //conversion depuis l'ascii
        int iCase = 0;
        map<DIRECTION, Case *> cases;
        int iInfo = 0;

        for (auto &c: s.substr(1)) {
            ZONE_TYPE type;
            int idConnexion;
            bool blason = false;

            if (iInfo == 0) {//type de la tuile
                type = ParametresPartie::toZONE_TYPE(c);
            }
            if (iInfo == 1) {// l'id de connexion de la tuile
                idConnexion = (int) c - 48; //conversion depuis l'ascii
            }
            if (iInfo == 2) {// l'info spéciale de la tuile
                if (c == '1') { //booléen pour le blason
                    blason = true;
                }
            }
            iInfo++;

            if (c == '_') {//fin de la description de la case
                cases[ALL_DIRECTIONS[iCase]] = new Case(type, ALL_DIRECTIONS[iCase], blason, idConnexion);
                iCase++;
                iInfo = 0;
            }
        }
        for (int i = 0; i < nbTuilesDeCeType; i++) {
            map<DIRECTION, Case *> casesNew = deepCopyMap(cases); //pour que les adresses des cases soient différentes
            auto *tuile = new Tuile(casesNew);
            for (auto &c: tuile->cases) { //on ajoute la tuile parente à chaque case
                c.second->setTuileParente(tuile);
            }
            tuiles->push_back(tuile);
        }
    }
}

/**
 * Lit le contenu d'un dossier et le stocke dans un vector de string donné en paramètre
 * @param chemin le chemin du dossier
 * @param vecteurDeStrings le vector de string où sera stocké le contenu du dossier
 */
void Jeu::lireDossier(const std::string &chemin, stringVec &vecteurDeStrings) {
    DIR *dirp = opendir(chemin.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_name[0] != '.') {//pour ne pas ajouter les noms . et ..
            vecteurDeStrings.push_back(dp->d_name);
        }
    }
    closedir(dirp);
}

/**
 * Permet de copier un map de cases en faisant appel au constructeur par recopie de Case
 * @param map1 la map à copier
 * @return le nouvelle map copiée
 */
map<DIRECTION, Case *> Jeu::deepCopyMap(const map<DIRECTION, Case *> &map1) {
    map<DIRECTION, Case *> map2;
    for (auto &c: map1) {
        map2[c.first] = new Case(*c.second);
    }
    return map2;
}
