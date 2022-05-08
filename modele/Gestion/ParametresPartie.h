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
    PRAIRIE, VILLE, CHEMIN, AUTRE, FIN
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

enum class MEEPLE_TYPE {
    ABBE, GRAND_MEEPLE, NORMAL
};

enum class COULEUR {
    ROUGE, BLEU, VERT, JAUNE, NOIR
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

    void setExtensionChoisie(EXTENSION extChoisie);

    int getNombreJoueurs() const;

    void setNombreJoueurs(int nbJoueurs);

    static std::string toStringDIRECTION(DIRECTION dir);

    static std::string toStringZONE_TYPE(ZONE_TYPE type);

    static ZONE_TYPE toZONE_TYPE(char type);

    static MEEPLE_TYPE toMEEPLE_TYPE(const std::string& str);

    static COULEUR toCOULEUR(const std::string& str);

    static std::string toStringCOULEUR(COULEUR couleur);

    static std::string toStringMEEPLE_TYPE(MEEPLE_TYPE type);
};


#endif //CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H