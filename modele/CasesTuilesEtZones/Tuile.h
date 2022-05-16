//
//  Tuile.hpp
//  Carcassonne
//
//  Created by Silvia on 11/05/2022.
//

#ifndef Tuile_hpp
#define Tuile_hpp

#include "Case.hpp"
#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>


using namespace std;

namespace Carcassonne {
class Tuile {
    public:
        map<DIRECTION,Case *> getTuile()const{return tuile;};
        Case* getCase(DIRECTION d)const;
        Tuile(map<DIRECTION,Case*> m);
        void PivoterTuile(int nbre_rotation);
        // explicitation des opérations générées par défaut
        ~Tuile() = default;
        Tuile(const Tuile&) = default;
        Tuile& operator=(const Tuile&) = default;
    private:
        map<DIRECTION,Case*> tuile;
        
    };



}
#endif /* Tuile_hpp */
