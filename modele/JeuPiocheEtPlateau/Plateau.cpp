//
// Created by etienne on 27/04/2022.
//

#include <iostream>
#include "Plateau.h"
#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"

void Plateau::fusionnerZones(Tuile *tuile) {
    //###################ZONES INTERNES###################
    //fusion des zones internes
    std::map<int, Zone *> zonesInternesTemp;
    for (std::pair<const DIRECTION, Case *> _caseTuile: tuile->cases) {
        //on vérifie que l'id de la case n'est pas déjà dans une zone existante
        for (std::pair<const int, Zone *> pair: zonesInternesTemp) {
            if (pair.first == _caseTuile.second->getIdConnexion()) {
                //si l'id est déjà dedans, c'est que l'on a déjà créé la zone
                //donc on ajoute cette case à la zone
                pair.second->ajouterCase(_caseTuile.second);
            } else {
                //sinon on crée une nouvelle zone et on l'ajoute à la liste
                Zone *zone = new Zone(_caseTuile.second);
                zonesInternesTemp.insert(std::pair<int, Zone *>(_caseTuile.second->getIdConnexion(), zone));
            }
        }
    }
    // on ajoute les zones internes à la liste des zones
    for (std::pair<const int, Zone *> pair: zonesInternesTemp) {
        zones.push_back(pair.second);
    }


    //###################ZONES EXTERNES###################
    //on a besoin de la Coord de cette tuile
    Coord *coordTuile;
    for (std::pair<Coord, Tuile *> pairTuile: plateau) {
        if (pairTuile.second == tuile) {
            coordTuile = &pairTuile.first;
        }
    }

    //pour chaque case sur une ParametresPartie::DIRECTION_COTE de la tuile
    for (int i = 0; i < sizeof DIRECTIONS_COTE; i++) {
        // on prend sa zone
        Zone *zone = tuile->cases[DIRECTIONS_COTE[i]]->getZone();

        //on cherche son voisin dans la liste plateau dans la bonne direction.
        //Par exemple si la case est au NORD, on cherche une tuile au NORD de la case actuelle
        Coord deplacement = ParametresPartie::toDeplacement(DIRECTIONS_COTE[i]);
        Coord coordTuileVoisine = *coordTuile + deplacement;
        Tuile *tuileVoisine = nullptr;
        for (std::pair<Coord, Tuile *> pairTuile: plateau) {
            if (pairTuile.first == coordTuileVoisine) {
                // on a trouvé la bonne tuile dans la liste
                tuileVoisine = pairTuile.second;
                break;
            }
        }
        if (tuileVoisine == nullptr) continue; //si la tuile voisine n'existe pas on passe au coté suivant

        //on fusionne la zone avec la zone de la tuile voisine
        Case *caseTuileVoisine = tuileVoisine->cases[DIRECTIONS_COTE_INVERSE[i]];
        fusionZoneCase(zone, caseTuileVoisine);

        // Si caseCote est Prairie ou chemin ou rivière, alors on peut fusionner aussi les coins
        ZONE_TYPE typeZoneCaseCote = tuile->cases[DIRECTIONS_COTE_INVERSE[i]]->getZoneType();
        if (typeZoneCaseCote == ZONE_TYPE::PRAIRIE || typeZoneCaseCote == ZONE_TYPE::CHEMIN ||
            typeZoneCaseCote == ZONE_TYPE::RIVIERE) {
            //On fusionne les coins. Les coins sont par exemple pour NORD -→ NORD_EST et NORD_OUEST
            std::vector<DIRECTION> deuxCoins = ParametresPartie::getCoinsAvecCote(DIRECTIONS_COTE[i]);
            for (auto &deuxCoin: deuxCoins) {
                //par exemple, si on est sur NORD_OUEST, on fusionne avec la case SUD_OUEST de la tuile en toDeplacement(DIRECTIONS_COTE[i])
                Case *caseAFusionner = tuileVoisine->cases[ParametresPartie::getDirDeCasePourTuileVoisine(deuxCoin,
                                                                                                          DIRECTIONS_COTE[i])];
                //on fusionne les zones
                fusionZoneCase(zone, caseAFusionner);
            }
        }
    }
}

void Plateau::fusionZoneCase(Zone *zone, Case *caseAFusionner) {
    zone->ajouterCase(caseAFusionner);
    //on supprime la case de la zone à laquelle elle appartenait
    //donc on cherche la zone de la case à supprimer en parcourant toutes les zones existantes
    for (Zone *z: zones) {
        std::vector<Case *> casesDeLaZone = z->getCases();
        for (Case *c: casesDeLaZone) {
            if (c == caseAFusionner) {
                z->supprimerCase(c);
                break;
            }
        }
    }
}

void Plateau::ajouterTuile(Tuile *tuile, Coord coord) {
    plateau.emplace_back(coord, tuile);
}

std::string Plateau::toString() {
    //affiche toutes les tuiles du plateau
    std::string str;
    for (std::pair<Coord, Tuile *> pairTuile: plateau) {
        str += pairTuile.second->toString();
    }
    return str;
}
