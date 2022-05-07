//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
#define CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
#pragma once
#include <string>

/**
 * Le type de la zone : PRE, VILLE, CHEMIN, ou AUTRE
 */
enum class ZONE_TYPE {
    PRE, VILLE, CHEMIN, AUTRE
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
 * Les différentes extensions avec lesquelles il est possible de jouer.
 * Par exemple PAYSANS.
 */
enum class EXTENSION {
    NORMAL, PAYSANS, ABBE, RIVIERE, AUBERGES_CATHEDRALES
};

//todo faire aussi un truc qui lie le chemin de l'image au machin


constexpr static const DIRECTION ALL_DIRECTIONS[] = {DIRECTION::NORD_OUEST, DIRECTION::NORD, DIRECTION::NORD_EST,
                                                     DIRECTION::EST, DIRECTION::MILIEU, DIRECTION::OUEST,
                                                     DIRECTION::SUD_EST, DIRECTION::SUD, DIRECTION::SUD_OUEST};

#include "CasesTuilesEtZones/Case.h"

class ParametresPartie {
private:
    int nombreJoueurs;
    EXTENSION extensionChoisie;

public:
    EXTENSION getExtensionChoisie() const;

    void setExtensionChoisie(EXTENSION extensionChoisie);

    int getNombreJoueurs() const;

    void setNombreJoueurs(int nombreJoueurs);




public:
    static std::string toStringDIRECTION(DIRECTION dir);

    static std::string toStringZONE_TYPE(ZONE_TYPE type);
};


#endif //CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
