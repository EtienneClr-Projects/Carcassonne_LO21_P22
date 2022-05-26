//
//  Case.cpp
//  Carcassonne
//
//  Created by Silvia on 11/05/2022.
//

#include "Case.h"
#include "ParametrePartie.hpp"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>


Case::Case(ZONE_TYPE zt, DIRECTION d,SUPP_TYPE s,int i): zone_type(zt),direction(d),supp_type(s),id_connexion(i),tuile_parente(nullptr),zone_parente(nullptr), meeple_posé(nullptr) {};

std::ostream& operator<<(std::ostream& f, const Case& c) {
        f << "(Type de la zone : " << c.getZoneType() << ", Direction : " << c.getDirection() << ", Type bonus"
            << c.getBonusType() << "," << c.getIdConnexion() << ")";
        return f;
    }
