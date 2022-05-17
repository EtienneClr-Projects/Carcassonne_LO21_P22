//
// Created by etienne on 27/04/2022.
//

#include "Plateau.h"
//
//  Plateau.cpp
//  Carcassonne
//
//  Created by Silvia on 16/05/2022.
//

#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>
#include <vector>
#include <dirent.h>


bool operator==(const map <Coord,Tuile*>& left, const map <Coord,Tuile*>& right);
bool operator==(const map<DIRECTION,Case*>& left, const map<DIRECTION,Case*>& right);
bool operator==(const ZONE_TYPE& left, const ZONE_TYPE& right);

void Plateau :: poserTuile(Tuile * t,Coord co){
    Coord voisin_droit=co;
    voisin_droit.x++;
    Coord voisin_gauche=co;
    voisin_gauche.x--;
    Coord voisin_haut=co;
    voisin_haut.y++;
    Coord voisin_bas=co;
    voisin_bas.y--;
    Tuile* tui=plateau[voisin_droit];
    if(*tui[DIRECTION::OUEST]==*t[DIRECTION::EST]);
}