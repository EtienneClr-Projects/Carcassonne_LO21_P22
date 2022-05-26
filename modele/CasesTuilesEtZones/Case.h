#ifndef Case_h
#define Case_h
#pragma once
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
class Zone;


#include "Gestion/ParametresPartie.h"
#include "CasesTuilesetZones/Tuile.h"

#include "JoueurEtRessources/Meeple.h"

using namespace std;


    class CarcassonneException {
    public:
        CarcassonneException(const string& i) :info(i) {}
        string getInfo() const { return info; }
    private:
        string info;
    };

    
class Case
{
public:
        ZONE_TYPE getZoneType() const ;
        DIRECTION getDirection() const { return direction; }
        SUPP_TYPE getBonusType() const { return supp_type;}
        int getIdConnexion() const { return id_connexion; }
        Tuile& getTuileParente() const { return *tuile_parente; }
        Zone& getZoneParente() const { return *zone_parente; }
        Meeple& getMeeplePose() const { return *meeple_posé; }
        void setTuileParente(Tuile& t) { tuile_parente=&t;}
        void setZoneParente(Zone& z) { zone_parente=&z;}
        void setDirection(DIRECTION c) { direction=c; }
        void setMeeple(Meeple& m) { meeple_posé=&m;}
        Case(ZONE_TYPE zt, DIRECTION d,SUPP_TYPE s,int i);
        ~Case() = default;
        Case(const Case&) = default;
        Case& operator=(const Case&) = default;
private:
        ZONE_TYPE zone_type;
        DIRECTION direction;
        SUPP_TYPE supp_type;
        int id_connexion;
        Tuile * tuile_parente;
        Zone * zone_parente;
        Meeple * meeple_posé;
    };

#endif /* Case_hpp */

