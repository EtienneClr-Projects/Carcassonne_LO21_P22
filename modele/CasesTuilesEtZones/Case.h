#ifndef CARCASSONNE_LO21_P22_CASE_H
#define CARCASSONNE_LO21_P22_CASE_H
#pragma once
class Meeple;
class Case;
#include "Gestion/ParametresPartie.h"
#include "JoueurEtRessources/Joueur.h"
#include "CasesTuilesEtZones/Tuile.h"
#include "CasesTuilesEtZones/Zone.h"
#include "JoueurEtRessources/Meeple.h"
#pragma once


class Case {
    ZONE_TYPE zone_type;
    DIRECTION direction;
    SUPP_TYPE supp_type;
    int id_connexion;
    Tuile * tuile_parente;
    Zone * zone_parente;
    Meeple * meeple_pose;
public:
    ZONE_TYPE getZoneType() const  { return zone_type; }
    DIRECTION getDirection() const { return direction; }
    SUPP_TYPE getSuppType() const { return supp_type;}
    int getIdConnexion() const { return id_connexion; }
    Tuile* getTuileParente() const { return tuile_parente; }
    Zone* getZoneParente() const { return zone_parente; }
    Meeple* getMeeplePose() const { return meeple_pose; }
    void setTuileParente(Tuile* t) { tuile_parente=t;}
    void setZoneParente(Zone& z) { zone_parente=&z;}
    void setDirection(DIRECTION c) { direction=c; }
    void setMeeple(Meeple* m) { meeple_pose=m;}
    void retirerMeeplePose() { meeple_pose = nullptr; }
    Case(ZONE_TYPE zt, DIRECTION d,SUPP_TYPE s,int i);
    ~Case() = default;
    Case(const Case&) = default;
    Case& operator=(const Case&) = default;
    std::string toString();
};


#endif //CARCASSONNE_LO21_P22_CASE_H
