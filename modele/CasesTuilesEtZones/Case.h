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


    class Case {
    public:
        //get
        ZONE_TYPE getZoneType() const { return zone_type; }

        DIRECTION getDirection() const { return direction; }

        BONUS_TYPE getBonusType() const { return bonus_type; }

        int getIdConnexion() const { return id_connexion; }

        int getTuileParente() const { return tuile_parente; }//changer type tuile*

        int getZoneParente() const { return zone_parente; }//changer type zone*

        Meeple *getMeeplePose() const { return *meeple_pose; }//changer type meeple*

        //set
        void setTuileParente(int t) { tuile_parente = t; }//changer type tuile*
        void setZoneParente(int z) { zone_parente = z; }//changer type zone*
        void setDirection(DIRECTION c) { direction = c; }

        void setMeeplePose(Meeple *mt) { meeple_pose = *mt; }//ajouter un meeple dans la case

        //constructeur
        Case(ZONE_TYPE zt, DIRECTION c, BONUS_TYPE b, int i, int t); //changer tous les types
        // explicitation des opérations générées par défaut

        //destructeur
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
