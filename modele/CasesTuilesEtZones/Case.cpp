//
//  Case.cpp
//  Carcassonne
//
//  Created by Silvia on 11/05/2022.
//

#include "Case.h"


Case::Case(ZONE_TYPE zt, DIRECTION d,SUPP_TYPE s,int i): zone_type(zt),direction(d),supp_type(s),id_connexion(i),tuile_parente(nullptr),zone_parente(nullptr), meeple_pose(nullptr) {};

std::string Case::toString() {
    return ParametresPartie::toStringZONE_TYPE(zone_type);
}
