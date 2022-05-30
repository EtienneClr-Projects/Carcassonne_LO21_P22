#include "JeuPiocheEtPlateau/Plateau.h"

# include <iostream>
# include <string>
# include <map>
#include <vector>

#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"

using namespace std;
Plateau *Plateau::instance = nullptr;

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
    Coord *coordTuile = findCoordTuile(tuile);

    //pour chaque case sur une ParametresPartie::DIRECTION_COTE de la tuile
    for (int i = 0; i < 4; i++) {
        // on prend sa zone
        Zone *zone = tuile->cases[DIRECTIONS_COTE[i]]->getZoneParente();

        //on cherche son voisin dans la liste plateau dans la bonne direction.
        //Par exemple si la case est au NORD, on cherche une tuile au NORD de la case actuelle
        Tuile *tuileVoisine = findTuileVoisine(coordTuile, i);
        if (tuileVoisine == nullptr) continue; //si la tuile voisine n'existe pas on passe au côté suivant

        //on fusionne la zone avec la zone de la tuile voisine pour les COTES
        Case *caseTuileVoisine = tuileVoisine->cases[DIRECTIONS_COTE_INVERSE[i]];


        if (caseTuileVoisine->getZoneParente() == zone) {
            cout << caseTuileVoisine << " == " << tuile->cases[DIRECTIONS_COTE[i]] << endl;
            throw std::runtime_error("caseTuileVoisine->getZoneParente()==zone");
        }
//        cout << "Fusion de la zone " << zone->toString() << " avec la zone de la case voisine "
//             << caseTuileVoisine->getZoneParente()->toString()
//             << endl;
//        cout << "affichage des zones du plateau :" << endl;
//        for (Zone *zPlateau: zones) {
//            cout << zPlateau->toString() << endl;
//        }


        //on met à jour les ouvertures des zones
        int ttOuvertures = zone->ouvertures + caseTuileVoisine->getZoneParente()->ouvertures;
        zone->ouvertures = ttOuvertures - 2;
        caseTuileVoisine->getZoneParente()->ouvertures = ttOuvertures - 2;//todo vérifier après

        //puis on fusionne les zones
        fusionZones(caseTuileVoisine->getZoneParente(), zone);
//        cout << "resultat sur la case " << tuileVoisine->cases[DIRECTIONS_COTE_INVERSE[i]]->getZoneParente()->toString()
//             << ", zone: "
//             << tuile->cases[DIRECTIONS_COTE[i]]->getZoneParente()->toString() << "\n\n" << endl;
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
        _case->setZoneParente(zoneB);
        zoneB->ajouterCase(_case);
//        cout << "\t" <<_case->getZoneParente()->toString() << " ajoute la case " << endl;
    }

    if (zoneASuppr == zoneB) //si ce sont les mêmes adresses on supprime pas
        throw std::invalid_argument("zoneASuppr == zoneB");

    //on supprime la zone A de la liste
    int i = 0;
    for (Zone *z: zones) {
        if (z == zoneASuppr) {
//            cout << "suppression de la zone " << zoneASuppr->toString() << endl;
//            for (Case *_case: zoneASuppr->getCase()) {
//                cout << "\t"<<_case->getZoneParente()->toString() << endl;
//            }
            zones.erase(zones.begin() + i);
            break;
        }
        i++;
    }
}

void Plateau::ajouterTuile(Tuile *tuile, Coord *coord) {
    plateau.emplace_back(coord, tuile);
//    fusionnerZonesAvecPlateau(tuile); //todo @Etienne
}

std::string Plateau::toString() {
    cout << "affichage des tuiles du plateau" << endl;
    //affiche toutes les tuiles du plateau
    std::string str;
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
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
                _caseTuile.second->setZoneParente(pair.second);
                trouveDansZoneExistante = true;
                break;
            }
        }
        if (!trouveDansZoneExistante) {
            //sinon on crée une nouvelle zone et on l'ajoute à la liste
            Zone *zone = new Zone(_caseTuile.second);
            _caseTuile.second->setZoneParente(zone);
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
        Zone *zoneCote = caseCote->getZoneParente();
        tuile->cases[DIRECTIONS_COTE[i]]->getZoneParente()->ouvertures++;
//        std::cout << zoneCote->toString() << "ouvertures = " << zoneCote->ouvertures << std::endl;
        //la tuile n'est pas encore vraiment posée, donc toutes les zones sont ouvertes, donc on les incrémente toutes
    } // todo
}

Coord *Plateau::findCoordTuile(Tuile *tuile) {
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
        if (pairTuile.second == tuile) {
            return pairTuile.first;
        }
    }
    throw std::invalid_argument("tuile non trouvée");
}

Tuile *Plateau::findTuileVoisine(Coord *coordTuile, int i) {
    Coord *deplacement = ParametresPartie::toDeplacement(DIRECTIONS_COTE[i]);
    auto *coordTuileVoisine = new Coord(coordTuile->x_ + deplacement->x_, coordTuile->y_ + deplacement->y_);
    cout << "CALC DEPLACEMENT Tuile trouvee au : " << ParametresPartie::toStringDIRECTION(DIRECTIONS_COTE[i]) << " "
         << coordTuileVoisine->toString() << "?" << endl;
    //on a sa coordonnée, maintenant on cherche la bonne tuile dans la liste
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
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
            if (fusionPossible(caseAFusionner->getZoneParente(), tuile->cases[deuxCoin]->getZoneParente())) {
                fusionZones(caseAFusionner->getZoneParente(), tuile->cases[deuxCoin]->getZoneParente());
            }
        }
    }
}


bool Plateau::checkerTuile(Tuile *tuile, Coord *coord) {
    //on prend les voisins de la tuile
    auto voisin_droit = new Coord(coord->x_ + 1, coord->y_);
    auto voisin_gauche = new Coord(coord->x_ - 1, coord->y_);
    auto voisin_haut = new Coord(coord->x_, coord->y_ - 1);
    auto voisin_bas = new Coord(coord->x_, coord->y_ + 1);

    map<DIRECTION, Case *> cases = tuile->getCases();
    bool a_un_voisin = false;//vérifier que la tuile a bien un voisin

    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {

        map<DIRECTION, Case *> casesVoisines = pairTuile.second->getCases();
        if (coord == pairTuile.first) {
            return false;//vérifie que l'utilisateur n'a pas cliqué sur une tuile existante
        }

        //verifie que pour chaque tuile, la zone adjacente est la même
        if (pairTuile.first->x_ == voisin_droit->x_ && pairTuile.first->y_ == voisin_droit->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::EST]->getZoneType() != casesVoisines[DIRECTION::OUEST]->getZoneType()) return false;
        }
        if (pairTuile.first->x_ == voisin_gauche->x_ && pairTuile.first->y_ == voisin_gauche->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::OUEST]->getZoneType() != casesVoisines[DIRECTION::EST]->getZoneType()) return false;
        }
        if (pairTuile.first->x_ == voisin_haut->x_ && pairTuile.first->y_ == voisin_haut->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::NORD]->getZoneType() != casesVoisines[DIRECTION::SUD]->getZoneType()) return false;
        }
        if (pairTuile.first->x_ == voisin_bas->x_ && pairTuile.first->y_ == voisin_bas->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::SUD]->getZoneType() != casesVoisines[DIRECTION::NORD]->getZoneType()) return false;
        }
    }
    return a_un_voisin || plateau.empty(); //si il y a un voisin ou si c'est la premiere tuile placée on peut la poser

    //todo @daphne ajouter règle rivière
}

bool Plateau::poserMeeple(Joueur *j, Case *c, MEEPLE_TYPE type, vector<Meeple *> meeplesPoses,
                          vector<Meeple *> meeplesEnReserve) {
    Zone *zone = c->getZoneParente();
    if (nullptr == zone->getGagnant()) {// si pas de meeple déjà posé dans la zone

        COULEUR couleur = j->getCouleur();
        unsigned int i = 0;
        while ((couleur != meeplesEnReserve[i]->getCouleur() and
                type != meeplesEnReserve[i]->getType()) and i <= meeplesEnReserve.size()) { i++; }

        //retirer du tableau "meeple en réserve" le meeple
        if (i > meeplesEnReserve.size()) {
            throw CarcassonneException("pas de meeple de ce type et de cette couleur disponible");
        }
        c->setMeeple(meeplesEnReserve[i]);
        meeplesPoses.push_back(meeplesEnReserve[i]);
        meeplesEnReserve.erase(meeplesEnReserve.begin() + i);
        //on met le meeple dans le bon tableau
        return true;
    }
    return false;
}


void Plateau::retirerMeeple(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve) {
    for (auto zone: zones) {//on regarde toutes les zones
        if (!(zone->estOuverte())) { // si la zone est fermée
            for (auto c: zone->getCases()) {//pour toute les cases de cette zone
                if (c->getMeeplePose() != nullptr) {//si il y a un meeple
                    meeplesEnReserve.push_back(c->getMeeplePose());//on l'ajoute dans le tableau des meeples en réserve
                    int i = 0;
                    for (auto meeple: meeplesPoses) {
                        if (meeple == c->getMeeplePose())
                            meeplesPoses.erase(meeplesPoses.begin() + i);//et on le retire du tableau des meeple poses
                        i++;
                    }
                    c->retirerMeeplePose(); // on retire le meeple de la case

                }
            }
        }
    }
}

void Plateau::afficherConsole() {
//on trouve le coin en haut à gauche du plateau par rapport aux coordonnées (x,y) des tuiles
//puis on affiche toutes les tuiles une par une
    Coord *coinHautGauche = getCoinHautGauche();
    Coord *coinBasDroite = getCoinBasDroite();
//    cout << "coins :" << coinHautGauche->toString() << " " << coinBasDroite->toString() << endl;
    for (int y = coinHautGauche->y_; y <= coinBasDroite->y_; y++) {
        for (int iYCase = 0; iYCase < 3; iYCase++) {//permet de passer sur les 3 hauteurs de cases
            for (int x = coinHautGauche->x_; x <= coinBasDroite->x_; x++) {
                for (int iXCase = 0; iXCase < 3; iXCase++) {//permet de passer sur les 3 hauteurs de cases
                    bool found = false;
                    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
                        if (pairTuile.first->x_ == x and pairTuile.first->y_ == y) {
                            cout << pairTuile.second->cases[DIRECTIONS_ORDERED[iYCase * 3 + iXCase]]->toString() << " ";
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "   ";
                }
                //affichage de la ligne de separation verticale
                cout << "|";
            }
            cout << endl;
        }
        //affichage de la ligne de separation horizontale
        for (int iSep = 0; iSep <= coinBasDroite->x_ - coinHautGauche->x_; iSep++)
            cout << "----------";
        cout << endl;
    }
}

Coord *Plateau::getCoinHautGauche() {
    auto *coinHautGauche = new Coord(200, 200); //todo @etienne améliorer le 200
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
        if (pairTuile.first->x_ < coinHautGauche->x_) {
            coinHautGauche->x_ = pairTuile.first->x_;
        }
        if (pairTuile.first->y_ < coinHautGauche->y_) {
            coinHautGauche->y_ = pairTuile.first->y_;
        }
    }
    if (coinHautGauche->x_ == 200 || coinHautGauche->y_ == 200) {
        throw CarcassonneException("erreur dans le calcul du coin haut gauche");
    }
    return coinHautGauche;
}

Coord *Plateau::getCoinBasDroite() {
    auto *coinBasDroite = new Coord(-200, -200);
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
        if (pairTuile.first->x_ > coinBasDroite->x_) {
            coinBasDroite->x_ = pairTuile.first->x_;
        }
        if (pairTuile.first->y_ > coinBasDroite->y_) {
            coinBasDroite->y_ = pairTuile.first->y_;
        }
    }
    if (coinBasDroite->x_ == -200 || coinBasDroite->y_ == -200) {
        cout << "erreur dans le calcul du coin bas droite" << endl;
        throw CarcassonneException("erreur dans le calcul du coin bas droite");
    }
    return coinBasDroite;
}
