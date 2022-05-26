//
//  Tuile.hpp
//  Carcassonne
//
//  Created by Silvia on 11/05/2022.
//

#ifndef Tuile_h
#define Tuile_h
#pragma once
class Tuile;
class Case;
#include "Gestion/ParametresPartie.h"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>


using namespace std;

class Tuile {
    public:
        map<DIRECTION,Case *> getTuile()const{return cases;};
        Case* getCase(DIRECTION d)const;
        explicit Tuile(map<DIRECTION, Case *> m, std::string cheminImage);
        void PivoterTuile(int nbre_rotation);
        // explicitation des opérations générées par défaut
        ~Tuile() = default;
        Tuile(const Tuile&) = default;
        Tuile& operator=(const Tuile&) = default;
    private:
        map<DIRECTION,Case*> cases;
        std::string cheminImage;
        
    };




#endif /* Tuile_h */


