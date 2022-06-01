#ifndef CARCASSONNE_LO21_P22_CASE_H
#define CARCASSONNE_LO21_P22_CASE_H
#pragma once

class Meeple;

class Case;

#include "Gestion/ParametresPartie.h"
#include "JoueurEtRessources/Joueur.h"
#include "CasesTuilesEtZones/Zone.h"
#include "JoueurEtRessources/Meeple.h"
#include "CasesTuilesEtZones/Tuile.h"


class Case {
    ZONE_TYPE zone_type;
    DIRECTION direction;
    SUPP_TYPE supp_type = SUPP_TYPE::AUCUN;
    int id_connexion;
    Tuile *tuile_parente;
    Zone *zone_parente;
    Meeple *meeple_pose;

public:
    int getIdConnexion() const;// {return id_connexion;}
    ZONE_TYPE getZoneType() const;//  { return zone_type; }

    DIRECTION getDirection() const;

    SUPP_TYPE getSuppType() const;

    Tuile *getTuileParente() const;

    Zone *getZoneParente() const;

    Meeple *getMeeplePose() const;

    void setTuileParente(Tuile *t);

    void setZoneParente(Zone *z);

    void setDirection(DIRECTION c);

    void setMeeple(Meeple *m);

    void retirerMeeplePose();

    Case(ZONE_TYPE zt, DIRECTION d, SUPP_TYPE s, int i);

    ~Case() = default;

    Case(const Case &) = default;

    Case &operator=(const Case &) = default;

    std::string toString();
};


#endif //CARCASSONNE_LO21_P22_CASE_H
