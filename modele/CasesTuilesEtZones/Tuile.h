#ifndef Tuile_h
#define Tuile_h
#pragma once
class Tuile;
class Case;
#include "ParametresPartie.h"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>

class Tuile {
    public:
        std :: map<DIRECTION,Case *> getTuile()const{return cases;};
        Case* getCase(DIRECTION d)const;
        explicit Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage);
        void PivoterTuile(int nbre_rotation);
        // explicitation des opérations générées par défaut
        ~Tuile() = default;
        Tuile(const Tuile&) = default;
        Tuile& operator=(const Tuile&) = default;
        std::string toString();
        std::map<DIRECTION, Case *> cases;
    private:
        std::string cheminImage;
        
    };

#endif //CARCASSONNE_LO21_P22_TUILE_H

