#include "Case.h"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>



namespace  Carcassonne {


    Case::Case(ZONE_TYPE zt, DIRECTION d,BONUS_TYPE b,int i,int t): zone_type(zt),direction(d),bonus_type(b),joueur(0),id_connexion(i),tuile_parente(t),zone_parente(0), meeple_posé(0) {};


    std::ostream& operator<<(std::ostream& f, const Case& c) {
        f << "(Type de la zone : " << c.getZoneType() << ", Direction : " << c.getDirection() << ", Type bonus"
          << c.getBonusType() << "," << c.getIdConnexion() << ")";
        return f;
    }


}
