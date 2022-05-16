//
//  Case.cpp
//  Carcassonne
//
//  Created by Silvia on 11/05/2022.
//

#include "Case.hpp"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>



namespace  Carcassonne {

    std::initializer_list<ZONE_TYPE> Zones_types ={ ZONE_TYPE::PRE,  ZONE_TYPE::VILLE,  ZONE_TYPE::CHEMIN,  ZONE_TYPE::VILLAGE,  ZONE_TYPE::ABBAYE,  ZONE_TYPE::RIVIERE,  ZONE_TYPE::SOURCE,  ZONE_TYPE::PONT };
    std::initializer_list<DIRECTION> Directions={ DIRECTION::NORD_OUEST, DIRECTION::NORD, DIRECTION::NORD_EST, DIRECTION::EST, DIRECTION::MILIEU, DIRECTION::OUEST, DIRECTION::SUD_EST, DIRECTION::SUD, DIRECTION::SUD_OUEST};
    std::initializer_list<BONUS_TYPE> Bonus_types={ BONUS_TYPE::BLASON,BONUS_TYPE::AUBERGE,BONUS_TYPE::BLE,BONUS_TYPE::TONNEAU,BONUS_TYPE::AUCUN };
    std::initializer_list<MEEPLE_TYPE> Meeple_types={ MEEPLE_TYPE::ABBE,MEEPLE_TYPE::GRAND_MEEPLE,MEEPLE_TYPE::NORMAL,MEEPLE_TYPE::BATISSEUR,MEEPLE_TYPE::COCHON };

    string toString(ZONE_TYPE zt) {
        switch (zt) {
            case ZONE_TYPE::PRE: return "P";
            case ZONE_TYPE::VILLE: return "V";
            case ZONE_TYPE::CHEMIN: return "C";
            case ZONE_TYPE::ABBAYE: return "A";
            case ZONE_TYPE::RIVIERE: return "R";
            case ZONE_TYPE::SOURCE: return "S";
            case ZONE_TYPE::PONT: return "P";
            default: throw CarcassonneException ("Type de case inconnu");
        }
    }

    string toString(DIRECTION d) {
        switch (d) {
            case DIRECTION::NORD_OUEST: return "NO";
            case DIRECTION::NORD: return "N";
            case DIRECTION::NORD_EST: return "NE";
            case DIRECTION::EST: return "E";
            case DIRECTION::MILIEU: return "M";
            case DIRECTION::OUEST: return "O";
            case DIRECTION::SUD_EST: return "SE";
            case DIRECTION::SUD: return "S";
            case DIRECTION::SUD_OUEST: return "SO";
        default: throw CarcassonneException ("Direction inconnu");
        }
    }

    string toString(BONUS_TYPE b) {
        switch (b) {
            case BONUS_TYPE::BLASON: return "BLAS";
            case BONUS_TYPE::AUBERGE: return "AUB";
            case BONUS_TYPE::BLE: return "BLE";
            case BONUS_TYPE::TONNEAU: return "T";
            case BONUS_TYPE::AUCUN: return "AUCUN";
            default: throw CarcassonneException ("Type de bonus inconnu");
        }
    }

    string toString(MEEPLE_TYPE m) {
        switch (m) {
            case MEEPLE_TYPE::ABBE: return "ABBE";
            case MEEPLE_TYPE::GRAND_MEEPLE: return "GRAND";
            case MEEPLE_TYPE::NORMAL: return "NORM";
            case MEEPLE_TYPE::BATISSEUR: return "BAT";
            case MEEPLE_TYPE::COCHON: return "COCHON";
            default: throw CarcassonneException ("Type de bonus inconnu");
        }
    }

    std::ostream& operator<<(std::ostream& f, ZONE_TYPE zt) { f << toString(zt); return f; }
    std::ostream& operator<<(std::ostream& f, DIRECTION d) {    f << toString(d); return f; }
    std::ostream& operator<<(std::ostream& f, BONUS_TYPE b) { f << toString(b);  return f; }
    std::ostream& operator<<(std::ostream& f, MEEPLE_TYPE m) { f << toString(m);  return f; }

    void printZoneTypes(std::ostream& f) {
        for (auto zt : Zones_types) f << zt << " ";
        f << "\n";
    }

    void printDirections(std::ostream& f) {
        for (auto d : Directions) f << d << " ";
        f << "\n";
    }

    void printBonusTypes(std::ostream& f) {
        for (auto b : Bonus_types) f << b << " ";
        f << "\n";
    }

    void printMeepleTypes(std::ostream& f) {
        for (auto m : Meeple_types) f << m << " ";
        f << "\n";
    }


    Case::Case(ZONE_TYPE zt, DIRECTION d,BONUS_TYPE b,int i,int t,MEEPLE_TYPE m): zone_type(zt),direction(d),bonus_type(b),joueur(0),id_connexion(i),tuile_parente(t),zone_parente(0), meeple_posé(m) {};


    std::ostream& operator<<(std::ostream& f, const Case& c) {
        f << "(Type de la zone : " << c.getZoneType() << ", Direction : " << c.getDirection() << ", Type bonus"
            << c.getBonusType() << "," << c.getIdConnexion() << ")";
        return f;
    }


}
