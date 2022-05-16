//
//  Tuile.cpp
//  Carcassonne
//
//  Created by Silvia on 11/05/2022.
//

#include "Case.hpp"
#include "Tuile.hpp"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>


using namespace std;
using namespace Carcassonne;

namespace Carcassonne {

    Tuile::Tuile(map<DIRECTION,Case*> t):tuile(t) {};

    Case* Tuile::getCase(DIRECTION d )const{
        return tuile.find(d)->second;
    }


    void Tuile::PivoterTuile( int nbre_rotation){
        map<DIRECTION,Case*> t2;
        for (unsigned int i=0; i<nbre_rotation; i++){
            t2[DIRECTION::NORD_OUEST]=tuile.find( DIRECTION::SUD_OUEST)->second;
            t2[DIRECTION::NORD]=tuile.find( DIRECTION::OUEST)->second;
            t2[DIRECTION::NORD_EST]=tuile.find( DIRECTION::NORD_OUEST)->second;
            t2[DIRECTION::OUEST]=tuile.find( DIRECTION::SUD)->second;
            t2[DIRECTION::MILIEU]=tuile.find( DIRECTION::MILIEU)->second;
            t2[DIRECTION::EST]=tuile.find( DIRECTION::NORD)->second;
            t2[DIRECTION::SUD_OUEST]=tuile.find( DIRECTION::SUD_EST)->second;
            t2[DIRECTION::SUD]=tuile.find( DIRECTION::EST)->second;
            t2[DIRECTION::SUD_EST]=tuile.find( DIRECTION::NORD_EST)->second;
            tuile=t2;
            /*for(DIRECTION d=DIRECTION::NORD_OUEST; d!=DIRECTION::SUD_EST; d=(DIRECTION) (d+1)) {//si jamais on garde attribut cardinal dans cases
                tuile.find(d)->second->setDirection(d);
            }*/
        }
    }
    
    

}

