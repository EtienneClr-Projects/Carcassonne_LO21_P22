//
// Created by etienne on 27/04/2022.
//


#include "Jeu.h"
#include "CasesTuilesEtZones/Case.h"
#include <random>
#include <string>
#include <vector>
#include <dirent.h>
#include <algorithm>
#include "CasesTuilesEtZones/Tuile.h"
#include "JoueurEtRessources/Meeple.h"

using namespace std;
typedef std::vector<std::string> stringVec;
Jeu *Jeu::instance = nullptr;

/**
 * Renvoie un vecteur de _tuiles contenant toutes les _tuiles déjà initialisées
 * et liées à leurs images de l'_extension fournie en paramètre
 * @param _extension l'_extension dont on veut récupérer les _tuiles
 * @param _tuiles le vecteur de _tuiles où seront stockées les _tuiles
 */
void Jeu::getTuilesDesRessources(EXTENSION _extension, vector<Tuile *> *_tuiles) {
    //on récupère le chemin du dossier en fonction de l'_extension demandée
    std::string chemin = "../" + getCheminFromExtension(_extension);
    chemin += TUILES; //ici on récupère les _tuiles
    stringVec v;
    lireDossier(chemin, v);
    //afficher les fichiers du dossier dans la sortie standard
    for (auto &s: v) {
        cout << s << endl;
    }


    //pour chaque nom de fichier
    for (auto &cheminImage: v) {
        //on parcourt chaque caractère de la chaine
        int nbTuilesDeCeType = (int) cheminImage[0] - 48; //conversion depuis l'ascii
        int iCase = 0;
        map<DIRECTION, Case *> cases;
        int iInfo = 0;

        for (auto &c: cheminImage.substr(1)) {
            ZONE_TYPE type;
            int idConnexion;
            SUPP_TYPE suppType;

            if (iInfo == 0) {//type de la tuile
                type = ParametresPartie::toZONE_TYPE(c);
            }
            if (iInfo == 1) {// l'id de connexion de la tuile
                idConnexion = (int) c - 48; //conversion depuis l'ascii
            }
            if (iInfo == 2) {// l'info spéciale de la tuile
                if (c == '1') { //booléen pour le blason
                    suppType = SUPP_TYPE::BLASON;
                }
                if (c == '2') { //booléen pour l'auberge
                    suppType = SUPP_TYPE::AUBERGE;
                }

            }
            iInfo++;

            if (c == '_') {//fin de la description de la case
                cases[ALL_DIRECTIONS[iCase]] = new Case(type, ALL_DIRECTIONS[iCase], suppType, idConnexion);
                iCase++;
                iInfo = 0;
                if (iCase == 9) {//fin de la description de la tuile
                    break;
                }

            }
        }
        for (int i = 0; i < nbTuilesDeCeType; i++) {
            map<DIRECTION, Case *> casesNew = deepCopyMap(cases); //pour que les adresses des cases soient différentes
            auto *tuile = new Tuile(casesNew, chemin + cheminImage);
            for (auto &c: tuile->cases) { //on ajoute la tuile parente à chaque case
                c.second->setTuileParente(tuile);
            }
            _tuiles->push_back(tuile);
        }
    }
}

/**
 * Renvoie un vecteur de meeples contenant tous les meeples déjà initialisés
 * et liées à leurs images de l'extension fournie en paramètre
 * @param extension l'extension dont on veut récupérer les meeples
 * @param meeples le vecteur de meeples où seront stockées les meeples
 */
void Jeu::getMeeplesDesRessources(EXTENSION extension, vector<Meeple *> *meeples) {
    //on récupère le chemin du dossier en fonction de l'extension demandée
    std::string chemin = "../" + getCheminFromExtension(extension);
    chemin += MEEPLES; //ici on récupère les meeples

    stringVec v;
    lireDossier(chemin, v);

    //pour chaque nom de fichier sous la forme :
    // 7NR → 7 meeples Normaux de couleur Rouge
    // <nb D’exemplaires><Type du Meeple><Couleur>
    //N → Normal
    //G → Grand Meeple
    //A → Abbé

    for (auto &cheminImage: v) {
        //on parcourt chaque caractère de la chaine
        int nbMeeplesDeCeType = (int) cheminImage[0] - 48; //conversion depuis l'ascii
        string t(1, cheminImage[1]);
        MEEPLE_TYPE type = ParametresPartie::toMEEPLE_TYPE(t);
        string c(1, cheminImage[2]);
        COULEUR couleur = ParametresPartie::toCOULEUR(c);

        for (int i = 0; i < nbMeeplesDeCeType; i++) {
            auto *meeple = new Meeple(type, couleur, chemin + cheminImage);
            meeples->push_back(meeple);
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

string Jeu::getCheminFromExtension(EXTENSION extension) {
    string chemin;
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
        case EXTENSION::MARCHANDS_BATISSEURS:
            break;
    }
    return chemin;
}

void Jeu::setExtensions(vector<EXTENSION> extensions) {
    vector<Tuile *> tuilesTemp;
    for (auto &ext: extensions) {
        if (ext == EXTENSION::RIVIERE) {
            getTuilesDesRessources(ext, &tuilesRiviere);
        } else
            getTuilesDesRessources(ext, &tuilesTemp);
    }
    if (!tuilesRiviere.empty()) {//on ajoute d'abord les tuiles de la rivière
        for (auto &t: tuilesRiviere) {
            tuiles.push_back(t);
        }
    }

    //puis on ajoute les autres tuiles dans le désordre
    shuffle(tuilesTemp.begin(), tuilesTemp.end(), std::mt19937(std::random_device()()));
    for (auto &t: tuilesTemp) {
        tuiles.push_back(t);
    }

    //todo faire les Meeples aussi ?
}

const Tuile &Jeu::getTuile(size_t i) const {
    return *tuiles[i];
}

