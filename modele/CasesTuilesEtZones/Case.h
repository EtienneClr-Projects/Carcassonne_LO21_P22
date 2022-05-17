//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_CASE_H
#define CARCASSONNE_LO21_P22_CASE_H
#pragma once

class Case;
#include "Gestion/ParametresPartie.h"
#include "JoueurEtRessources/Joueur.h"
#include "CasesTuilesEtZones/Tuile.h"
#include "Zone.h"

class Case {
    ZONE_TYPE type;
    DIRECTION direction;
    SUPP_TYPE suppType;
    int iDConnexion;
    Joueur* joueur;

public:
    Joueur *getJoueur() const;

public:
    int getIdConnexion() const;

public:
    Case(ZONE_TYPE type, DIRECTION direction, SUPP_TYPE spType, int IdConnexion) {
        this->type = type;
        this->direction = direction;
        this->suppType = spType;
        this->iDConnexion = IdConnexion;
    }
    //constructeur par recopie
    Case(Case const &c) {
        this->type = c.type;
        this->direction = c.direction;
        this->suppType = c.suppType;
        this->iDConnexion = c.iDConnexion;
    }

    void setTuileParente(Tuile *tuileParente);

    std::string toString();

    Tuile *getTuileParente();

    DIRECTION getDirection();

    ZONE_TYPE getZoneType();

    Zone *getZone();
};


#endif //CARCASSONNE_LO21_P22_CASE_H
