//
// Created by etienne on 27/04/2022.
//

#include <iostream>
#include "Plateau.h"
#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"

using namespace std;

void Plateau::fusionnerZonesAvecPlateau(Tuile *tuile) {
    cout << "\n\n FUSION DE LA TUILE :" << tuile->toString() << endl;
//###################ZONES INTERNES###################
    //fusion des zones internes
    std::vector<pair<int, Zone *>> zonesInternesTemp = calcZonesInternes(tuile);
    // on ajoute les zones internes à la liste des zones
    for (std::pair<const int, Zone *> pair: zonesInternesTemp) {
        zones.push_back(pair.second);
        cout << "Ajout de la zone : " << pair.second->toString() << endl;
    }
    //on met à jour les ouvertures de chaque zone qui sont sur les côtés de la tuile
    majOuverturesZonesCOTE(tuile);

    cout << "FIN FUSION INTERNE DE LA TUILE :" << tuile->toString() << endl;


//###################ZONES EXTERNES###################
    //on a besoin de la Coord de cette tuile
    Coord coordTuile = findCoordTuile(tuile);

    //pour chaque case sur une ParametresPartie::DIRECTION_COTE de la tuile
    for (int i = 0; i < 4; i++) {
        // on prend sa zone
        Zone *zone = tuile->cases[DIRECTIONS_COTE[i]]->getZone();

        //on cherche son voisin dans la liste plateau dans la bonne direction.
        //Par exemple si la case est au NORD, on cherche une tuile au NORD de la case actuelle
        Tuile *tuileVoisine = findTuileVoisine(coordTuile, i);
        if (tuileVoisine == nullptr) continue; //si la tuile voisine n'existe pas on passe au côté suivant

        //on fusionne la zone avec la zone de la tuile voisine pour les COTES
        Case *caseTuileVoisine = tuileVoisine->cases[DIRECTIONS_COTE_INVERSE[i]];


        if (caseTuileVoisine->getZone() == zone) {
            cout << caseTuileVoisine << " == " << tuile->cases[DIRECTIONS_COTE[i]] << endl;
            throw std::runtime_error("caseTuileVoisine->getZone()==zone");
        }
//        cout << "Fusion de la zone " << zone->toString() << " avec la zone de la case voisine "
//             << caseTuileVoisine->getZone()->toString()
//             << endl;
//        cout << "affichage des zones du plateau :" << endl;
//        for (Zone *zPlateau: zones) {
//            cout << zPlateau->toString() << endl;
//        }


        //on met à jour les ouvertures des zones
        int ttOuvertures = zone->ouvertures + caseTuileVoisine->getZone()->ouvertures;
        zone->ouvertures = ttOuvertures - 2;
        caseTuileVoisine->getZone()->ouvertures = ttOuvertures - 2;//todo vérifier après

        //puis on fusionne les zones
        fusionZones(caseTuileVoisine->getZone(), zone);
//        cout << "resultat sur la case " << tuileVoisine->cases[DIRECTIONS_COTE_INVERSE[i]]->getZone()->toString()
//             << ", zone: "
//             << tuile->cases[DIRECTIONS_COTE[i]]->getZone()->toString() << "\n\n" << endl;
//        cout << "REaffichage des zones du plateau :" << endl;
//        for (Zone *zPlateau: zones) {
//            cout << zPlateau->toString() << endl;
//        }

        // Si caseCote est Prairie ou chemin ou rivière, alors on peut fusionner aussi les COINS avec la case à côté
        fusionZonesCOINS(tuile, i, tuileVoisine);

        cout << "###############################################################" << endl;
    }

    //affichage de toutes les zones
    std::cout << "\n\nFIN : \n" << std::endl;
    for (Zone *zone: zones) {
        std::cout << zone->toString() << std::endl;
    }
}

bool Plateau::fusionPossible(Zone *zone1, Zone *zone2) {
    return zone1->getType() == zone2->getType() && zone1 != zone2;
}

/**
 * Ajoute toutes les cases de la zoneASuppr à la zone B donnée.
 * Supprime toutes les cases de la zone A.
 * @param zoneASuppr la zone a fusionner qui va être supprimée.
 * @param zoneB la zone avec laquelle fusionner.
 */
void Plateau::fusionZones(Zone *zoneASuppr, Zone *zoneB) {
    // on ajoute toutes les cases de la zoneASuppr à la zoneB
    for (Case *_case: zoneASuppr->getCases()) {
        _case->setZone(zoneB);
        zoneB->ajouterCase(_case);
//        cout << "\t" <<_case->getZone()->toString() << " ajoute la case " << endl;
    }

    if (zoneASuppr == zoneB) //si ce sont les mêmes adresses on supprime pas
        throw std::invalid_argument("zoneASuppr == zoneB");

    //on supprime la zone A de la liste
    int i = 0;
    for (Zone *z: zones) {
        if (z == zoneASuppr) {
//            cout << "suppression de la zone " << zoneASuppr->toString() << endl;
//            for (Case *_case: zoneASuppr->getCases()) {
//                cout << "\t"<<_case->getZone()->toString() << endl;
//            }
            zones.erase(zones.begin() + i);
            break;
        }
        i++;
    }
}

void Plateau::ajouterTuile(Tuile *tuile, Coord coord) {
    plateau.emplace_back(coord, tuile);
    fusionnerZonesAvecPlateau(tuile);
}

std::string Plateau::toString() {
    //affiche toutes les tuiles du plateau
    std::string str;
    for (std::pair<Coord, Tuile *> pairTuile: plateau) {
        str += pairTuile.second->toString();
    }
    return str;
}

std::vector<pair<int, Zone *>> Plateau::calcZonesInternes(Tuile *tuile) {
    std::vector<pair<int, Zone *>> zonesInternesTemp;
    for (std::pair<const DIRECTION, Case *> _caseTuile: tuile->cases) {
        //on vérifie que l'id de la case n'est pas déjà l'id d'une zone existante dans zonesInternesTemp de même type
        bool trouveDansZoneExistante = false;
        for (std::pair<const int, Zone *> pair: zonesInternesTemp) {
            if (pair.first == _caseTuile.second->getIdConnexion() &&
                pair.second->getType() == _caseTuile.second->getZoneType()) {
                //si l'id est déjà dedans et c'est le même type,
                // donc c'est que l'on a déjà créé la zone donc on ajoute cette case à la zone
                pair.second->ajouterCase(_caseTuile.second);
                _caseTuile.second->setZone(pair.second);
                trouveDansZoneExistante = true;
                break;
            }
        }
        if (!trouveDansZoneExistante) {
            //sinon on crée une nouvelle zone et on l'ajoute à la liste
            Zone *zone = new Zone(_caseTuile.second);
            _caseTuile.second->setZone(zone);
            zonesInternesTemp.emplace_back(_caseTuile.second->getIdConnexion(), zone);
        }
    }
    return zonesInternesTemp;
}

void Plateau::majOuverturesZonesCOTE(Tuile *tuile) {
    for (int i = 0; i < 4; i++) {
        std::cout << "I" + std::to_string(i) << " ";
        // on prend sa zone et on lui ajoute +1 en ouverture
        Case *caseCote = tuile->cases[DIRECTIONS_COTE[i]];
        Zone *zoneCote = caseCote->getZone();
        tuile->cases[DIRECTIONS_COTE[i]]->getZone()->ouvertures++;
//        std::cout << zoneCote->toString() << "ouvertures = " << zoneCote->ouvertures << std::endl;
        //la tuile n'est pas encore vraiment posée, donc toutes les zones sont ouvertes, donc on les incrémente toutes
    }
}

Coord Plateau::findCoordTuile(Tuile *tuile) {
    for (std::pair<Coord, Tuile *> pairTuile: plateau) {
        if (pairTuile.second == tuile) {
            return pairTuile.first;
        }
    }
    throw std::invalid_argument("tuile non trouvée");
}

Tuile *Plateau::findTuileVoisine(Coord coordTuile, int i) {
    Coord deplacement = ParametresPartie::toDeplacement(DIRECTIONS_COTE[i]);
    Coord coordTuileVoisine = coordTuile + deplacement;
    cout << "CALC DEPLACEMENT Tuile trouvee au : " << ParametresPartie::toStringDIRECTION(DIRECTIONS_COTE[i]) << " "
         << coordTuileVoisine.toString() << "?" << endl;
    //on a sa coordonnée, maintenant on cherche la bonne tuile dans la liste
    for (std::pair<Coord, Tuile *> pairTuile: plateau) {
        if (pairTuile.first == coordTuileVoisine) {
            // on a trouvé la bonne tuile dans la liste
            return pairTuile.second;
        }
    }
    return nullptr;
}

void Plateau::fusionZonesCOINS(Tuile *tuile, int i, Tuile *tuileVoisine) {
    ZONE_TYPE typeZoneCaseCote = tuile->cases[DIRECTIONS_COTE[i]]->getZoneType();
    if (typeZoneCaseCote == ZONE_TYPE::PRAIRIE || typeZoneCaseCote == ZONE_TYPE::CHEMIN ||
        typeZoneCaseCote == ZONE_TYPE::RIVIERE) {
        //On fusionne les coins. Les coins sont par exemple pour NORD -→ NORD_EST et NORD_OUEST
        std::vector<DIRECTION> deuxCoins = ParametresPartie::getCoinsAvecCote(DIRECTIONS_COTE[i]);
        for (auto deuxCoin: deuxCoins) {
            //par exemple, si on est sur NORD_OUEST, on fusionne avec la case SUD_OUEST de la tuile en toDeplacement(DIRECTIONS_COTE[i])
            Case *caseAFusionner = tuileVoisine->cases[ParametresPartie::getDirDeCasePourTuileVoisine(deuxCoin,
                                                                                                      DIRECTIONS_COTE[i])];
            //on fusionne les zones si même type de zone et si les zones ne sont déjà pas fusionnées
            if (fusionPossible(caseAFusionner->getZone(), tuile->cases[deuxCoin]->getZone())) {
                fusionZones(caseAFusionner->getZone(), tuile->cases[deuxCoin]->getZone());
            }
        }
    }
}
