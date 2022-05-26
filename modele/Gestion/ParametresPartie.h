//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
#define CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
#pragma once

#include <string>

/**
 * Le type de la zone : PRAIRIE, VILLE, CHEMIN, ou AUTRE ou FIN pour une fin de chemin
 */
enum class ZONE_TYPE {
    PRAIRIE, VILLE, CHEMIN, AUTRE, RIVIERE, FIN_DE_ROUTE, ABBAYE, JARDIN, LAC, SOURCE, CATHEDRALE
};
/**
 * La direction suivant les 9 cardinaux.
 * Par exemple NORD_OUEST.
 */
enum class DIRECTION {
    NORD_OUEST, NORD, NORD_EST,
    EST, MILIEU, OUEST,
    SUD_EST, SUD, SUD_OUEST
};

/**
 * Les différents types de Meeples. Par exemple, NORMAL ou ABBE.
 */
enum class MEEPLE_TYPE {
    ABBE, GRAND_MEEPLE, NORMAL, BATISSEUR, COCHON
};
/**
 * Les différentes couleurs des meeples
 */
enum class COULEUR {
    ROUGE, BLEU, VERT, JAUNE, NOIR
};
/**
 * Un paramètre supplémentaire des cases. Si elles possèdent un blason par exemple.
 */
enum class SUPP_TYPE {
    BLASON, AUBERGE, BLE, TONNEAU, TISSU
};
/**
 * Les différentes extensions avec lesquelles il est possible de jouer.
 * Par exemple PAYSANS.
 */
enum class EXTENSION {
    NORMAL, PAYSANS, ABBE, RIVIERE, AUBERGES_CATHEDRALES, MARCHANDS_BATISSEURS
};

/**
 * Permet de parcourir toutes les directions
 */
constexpr static const DIRECTION ALL_DIRECTIONS[] = {DIRECTION::NORD_OUEST, DIRECTION::NORD, DIRECTION::NORD_EST,
                                                     DIRECTION::EST, DIRECTION::MILIEU, DIRECTION::OUEST,
                                                     DIRECTION::SUD_EST, DIRECTION::SUD, DIRECTION::SUD_OUEST};

#include "CasesTuilesEtZones/Case.h"

/**
 * Parametres de la partie. Singleton.
 * On trouve ici les informations nécessaires à la partie.
 * On trouve également les enumérations des différents types de cases, zones, directions, couleurs, etc.
 * accompagnées des méthodes pour les transformer en string ou l'inverse.
 */
class ParametresPartie {
private:
    int nombreJoueurs;
    EXTENSION extensionChoisie;

    //SINGLETON
    ParametresPartie() = default;

    static ParametresPartie *instance_;

public:
    //SINGLETON
    ParametresPartie(const ParametresPartie &) = delete;

    ParametresPartie &operator=(const ParametresPartie &) = delete;

    static ParametresPartie *getInstance();

    //METHODES DU SINGLETON
    EXTENSION getExtensionChoisie() const;

    void setExtensionChoisie(EXTENSION extChoisie);

    int getNombreJoueurs() const;

    void setNombreJoueurs(int nbJoueurs);


    //METHODES STATIQUES DE CONVERSION
    static std::string toStringDIRECTION(DIRECTION dir);

    static std::string toStringZONE_TYPE(ZONE_TYPE type);

    static ZONE_TYPE toZONE_TYPE(char type);

    static MEEPLE_TYPE toMEEPLE_TYPE(const std::string &str);

    static COULEUR toCOULEUR(const std::string &str);

    static std::string toStringCOULEUR(COULEUR couleur);

    static std::string toStringMEEPLE_TYPE(MEEPLE_TYPE type);

    static std::string toStringEXTENSION(EXTENSION ext);
};


// classe pour gérer les exceptions dans le set
class CarcassonneException {
public:
    explicit CarcassonneException(std::string i) : info(std::move(i)) {}

    std::string getInfo() const { return info; }

private:
    std::string info;
};


#endif //CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H