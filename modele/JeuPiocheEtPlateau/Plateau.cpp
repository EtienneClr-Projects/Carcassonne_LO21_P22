#include "JeuPiocheEtPlateau/Plateau.h"

#include <stdio.h>
# include <iostream>
# include <string>
# include <initializer_list>
# include <cstdlib>
# include <map>
#include <vector>
#include <dirent.h>
#include <vector>



bool Plateau :: checkerTuile(Tuile * tuile,Coord coord){

    auto voisin_droit=coord;
    voisin_droit.x_++;
    auto voisin_gauche=coord;
    voisin_gauche.x_--;
    auto voisin_haut=coord;
    voisin_haut.y_++;
    auto voisin_bas=coord;
    voisin_bas.y_--;
    map<DIRECTION,Case*> t=tuile->getTuile();

    for(std::pair<Coord,Tuile*> pairTuile:plateau){
        map<DIRECTION,Case*> pt=pairTuile.second->getTuile();
        if(voisin_droit == pairTuile.first){
            if (t[DIRECTION::EST]->getZoneType() != pt[DIRECTION::OUEST]->getZoneType()) return false;
        }
        if(voisin_gauche == pairTuile.first){
            if (t[DIRECTION::OUEST]->getZoneType() != pt[DIRECTION::EST]->getZoneType()) return false;
        }
        if(voisin_haut == pairTuile.first){
            if (t[DIRECTION::NORD]->getZoneType() != pt[DIRECTION::SUD]->getZoneType()) return false;
        }
        if(voisin_bas == pairTuile.first){
            if (t[DIRECTION::SUD]->getZoneType() != pt[DIRECTION::NORD]->getZoneType()) return false;
        }
    }
    return true;




}

bool Plateau::poserMeeple(Joueur *j, Case * c, MEEPLE_TYPE type,vector<Meeple*>meeplesPoses, vector<Meeple*> meeplesEnReserve){
    Zone *zone=c->getZoneParente();
    if (nullptr == zone->getGagnant()){// si pas de meeple déjà posé dans la zone

        COULEUR couleur=j->getCouleur();
        unsigned int i=0;
        while ((couleur!= meeplesEnReserve[i]->getCouleur() or
                type != meeplesEnReserve[i]->getType()) and i <= meeplesEnReserve.size()){i++;}

        //retirer du tableau "meeple en réserve" le meeple
        if (i>meeplesEnReserve.size())
        {
            throw CarcassonneException("pas de meeple de ce type et de cette couleur disponible");
        }
        c->setMeeple(meeplesEnReserve[i]);
        meeplesPoses.push_back(meeplesEnReserve[i]);
        meeplesEnReserve.erase(meeplesEnReserve.begin()+i);
        //on met le meeple dans le bon tableau
        return true;

    }
    else {return false;}
}



void Plateau:: retirerMeeple(vector<Meeple *>& meeplesPoses, vector<Meeple *>& meeplesEnReserve) {
    for (auto zone : zones){
        if (!(zone->estOuverte())){
            for (auto c : zone->getCases()){
                if(c->getMeeplePose() != nullptr){
                    meeplesEnReserve.push_back(c->getMeeplePose());
                    int i=0;
                    for (auto meeple : meeplesPoses){
                        if (meeple==c->getMeeplePose())
                            meeplesPoses.erase(meeplesPoses.begin() + i);
                            i++;
                    }
                    c->retirerMeeplePose();
                    
                }
            }
        }
    }
}
