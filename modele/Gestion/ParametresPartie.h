#ifndef CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
#define CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H
#pragma once

#include <string>

static const int COLOR_NORMALE = 15;


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
    BLASON, AUBERGE, BLE, TONNEAU, TISSU, AUCUN, JARDIN
};

/**
 * Les différentes extensions avec lesquelles il est possible de jouer.
 * Par exemple PAYSANS.
 */
enum class EXTENSION {
    NORMAL, PAYSANS, ABBE, RIVIERE, AUBERGES_CATHEDRALES, MARCHANDS_BATISSEURS
};
constexpr static const COULEUR ALL_COULEURS[]{COULEUR::BLEU, COULEUR::JAUNE, COULEUR::ROUGE, COULEUR::VERT};

constexpr static const DIRECTION DIRECTIONS_ORDERED[]{DIRECTION::NORD_OUEST, DIRECTION::NORD, DIRECTION::NORD_EST,
                                                      DIRECTION::OUEST, DIRECTION::MILIEU, DIRECTION::EST,
                                                      DIRECTION::SUD_OUEST, DIRECTION::SUD, DIRECTION::SUD_EST};
constexpr static const DIRECTION DIRECTIONS_COTE_COINS[]{DIRECTION::NORD_OUEST, DIRECTION::NORD, DIRECTION::NORD_EST,
                                                         DIRECTION::EST, DIRECTION::SUD_EST, DIRECTION::SUD,
                                                         DIRECTION::SUD_OUEST, DIRECTION::OUEST};
constexpr static const DIRECTION DIRECTIONS_COTE[] = {
        DIRECTION::NORD, DIRECTION::OUEST, DIRECTION::SUD, DIRECTION::EST
};
constexpr static const DIRECTION DIRECTIONS_COTE_INVERSE[]{
        DIRECTION::SUD, DIRECTION::EST, DIRECTION::NORD, DIRECTION::OUEST
};//utilisé pour trouver la case adjacente à une tuile. Cf Plateau::fusionnerZonesAvecPlateau()

// la source est équivalente au lac
constexpr static const ZONE_TYPE ALL_ZONES_TYPES[] = {ZONE_TYPE::PRAIRIE, ZONE_TYPE::VILLE, ZONE_TYPE::CHEMIN,
                                                      ZONE_TYPE::AUTRE, ZONE_TYPE::RIVIERE, ZONE_TYPE::FIN_DE_ROUTE,
                                                      ZONE_TYPE::ABBAYE, ZONE_TYPE::JARDIN, ZONE_TYPE::LAC,
                                                      ZONE_TYPE::CATHEDRALE};

constexpr static const SUPP_TYPE ALL_SUPPS_TYPES[] = {SUPP_TYPE::BLASON, SUPP_TYPE::AUBERGE, SUPP_TYPE::BLE,
                                                      SUPP_TYPE::TONNEAU,
                                                      SUPP_TYPE::TISSU,};

constexpr static const MEEPLE_TYPE ALL_MEEPLES_TYPES[] = {MEEPLE_TYPE::ABBE, MEEPLE_TYPE::GRAND_MEEPLE,
                                                          MEEPLE_TYPE::NORMAL,
                                                          MEEPLE_TYPE::BATISSEUR, MEEPLE_TYPE::COCHON};


#include "Coord.h"
#include <vector>

/**
 * Parametres de la partie. Singleton.
 * On trouve ici les informations nécessaires à la partie.
 * On trouve également les enumérations des différents types de cases, zones, directions, couleurs, etc.
 * accompagnées des méthodes pour les transformer en string ou l'inverse.
 */
class ParametresPartie {
private:
    int nombreJoueurs{};
    std::vector<EXTENSION> extensionsChoisies;

    //SINGLETON
    ParametresPartie() = default;

    static ParametresPartie *instance_;

public:
    //SINGLETON
    ParametresPartie(const ParametresPartie &) = delete;

    ParametresPartie &operator=(const ParametresPartie &) = delete;

    static ParametresPartie *getInstance();

    //METHODES DU SINGLETON
    std::vector<EXTENSION> getExtensionsChoisies() const;

    void setExtensionsChoisies(std::vector<EXTENSION> extsChoisies);

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

    static std::string toStringEXTENSIONS(const std::vector<EXTENSION> &exts);

    static std::string toStringSUPP_TYPE(SUPP_TYPE type);

    static Coord *toDeplacement(DIRECTION direction);

    static std::vector<DIRECTION> getCoinsAvecCote(DIRECTION cote);

    static DIRECTION getDirDeCasePourTuileVoisine(DIRECTION dirCaseActuelle, DIRECTION dirOuRegarder);

    static std::string toStringEXTENSION(EXTENSION extension);
};

// classe pour gérer les exceptions dans le set
class CarcassonneException : public std::exception { //todo utiliser partout cette exception du coup
public:
    explicit CarcassonneException(std::string i) : info(std::move(i)) {}

    std::string getInfo() const { return info; }

private:
    std::string info;
};

#endif //CARCASSONNE_LO21_P22_PARAMETRESPARTIE_H