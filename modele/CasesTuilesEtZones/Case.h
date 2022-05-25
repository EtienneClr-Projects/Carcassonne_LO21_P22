#ifndef Case_h
#define Case_h

#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
#include <utility>
#include <Gestion/ParametresPartie.h>


using namespace std;

namespace Carcassonne {
    // classe pour gérer les exceptions dans le set
    class CarcassonneException {
    public:
        explicit CarcassonneException(string i) : info(std::move(i)) {}

        string getInfo() const { return info; }

    private:
        string info;
    };

    // caractéristiques
    enum class ZONE_TYPE {
        PRE, VILLE, CHEMIN, VILLAGE, ABBAYE, RIVIERE, SOURCE, PONT
    };
    enum class DIRECTION {
        NORD_OUEST, NORD, NORD_EST, EST, MILIEU, OUEST, SUD_EST, SUD, SUD_OUEST
    };
    enum class BONUS_TYPE {
        BLASON, AUBERGE, BLE, TONNEAU, AUCUN
    };


    // conversion d'une caractéristique en string
    string toString(ZONE_TYPE zt);

    string toString(DIRECTION d);

    string toString(BONUS_TYPE bt);

    // écriture d'une caractéristique sur un flux ostream
    ostream &operator<<(ostream &f, ZONE_TYPE zt);

    ostream &operator<<(ostream &f, DIRECTION d);

    ostream &operator<<(ostream &f, BONUS_TYPE bt);

    // listes contenant les valeurs possibles pour chacune des caractéristiques
    extern std::initializer_list<ZONE_TYPE> Zones_types;
    extern std::initializer_list<DIRECTION> Directions;
    extern std::initializer_list<BONUS_TYPE> Bonus_types;


    // affichage des valeurs possibles pour chaque caractéristiques
    void printZone_type(std::ostream &f = cout);

    void printDirection(std::ostream &f = cout);

    void printBonusType(std::ostream &f = cout);


    class Case {
    public:
        ZONE_TYPE getZoneType() const { return zone_type; }

        DIRECTION getDirection() const { return direction; }

        BONUS_TYPE getBonusType() const { return bonus_type; }

        int getJoueur() const { return joueur; } //changer type joueur*
        int getIdConnexion() const { return id_connexion; }

        int getTuileParente() const { return tuile_parente; }//changer type tuile*
        int getZoneParente() const { return zone_parente; }//changer type zone*
        int getMeeplePose() const { return meeple_posé; }//changer type meeple*
        void setTuileParente(int t) { tuile_parente = t; }//changer type tuile*
        void setZoneParente(int z) { zone_parente = z; }//changer type zone*
        void setDirection(DIRECTION c) { direction = c; }

        void setJoueur(int j) { joueur = j; }//changer type joueur*
        void setMeeplePose(Meeple *mt) { meeple_pose = *mt; }//changer type tuile*
        Case(ZONE_TYPE zt, DIRECTION c, BONUS_TYPE b, int i, int t); //changer tous les types
        // explicitation des opérations générées par défaut
        ~Case() = default;

        Case(const Case &) = default;

        Case &operator=(const Case &) = default;

    private:
        ZONE_TYPE zone_type;
        DIRECTION direction;
        BONUS_TYPE bonus_type;
        int id_connexion;
        Tuile *tuile_parente;
        Zone *zone_parente;
        Meeple *meeple_pose;
    };
}
#endif /* Case_h */
