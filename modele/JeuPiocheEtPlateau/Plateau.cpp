#include "JeuPiocheEtPlateau/Plateau.h"

# include <iostream>
# include <string>
# include <map>
#include <vector>
#include "JeuPiocheEtPlateau/Jeu.h"
//#include <windows.h>
#include <algorithm>

#include "CasesTuilesEtZones/Tuile.h"
#include "Gestion/Coord.h"
#include "Gestion/Partie.h"
#include <set>

using namespace std;
Plateau *Plateau::instance = nullptr;
int Plateau::nombreDePrairie = 0;

void Plateau::fusionnerZonesAvecPlateau(Tuile *tuile) {
//###################ZONES INTERNES###################
// les zones internes sont déjà calculées, mais il faut les récupérer
    for (auto *zone: tuile->getZonesInternes()) {
        zones.push_back(zone);
    }

//###################ZONES EXTERNES###################
    //on a besoin de la Coord de cette tuile
    Coord *coordTuile = findCoordTuile(tuile);

    //pour chaque case sur une ParametresPartie::DIRECTION_COTE de la tuile
    for (int i = 0; i < 4; i++) {
        // on prend sa zoneCoteActuelle
        Zone *zoneCoteActuelle = tuile->cases[DIRECTIONS_COTE[i]]->getZoneParente();

        //on cherche son voisin dans la liste plateau dans la bonne direction.
        //Par exemple si la case est au NORD, on cherche une tuile au NORD de la case actuelle
        Tuile *tuileVoisine = findTuileVoisine(coordTuile, i);
        if (tuileVoisine == nullptr) {
            continue; //si la tuile voisine n'existe pas on passe au côté suivant
        }
        //on fusionne la zoneCoteActuelle avec la zoneCoteActuelle de la tuile voisine pour les COTES
        Case *caseTuileVoisine = tuileVoisine->cases[DIRECTIONS_COTE_INVERSE[i]];

        //on met à jour les ouvertures des zones
        int ttOuvertures = zoneCoteActuelle->ouvertures;
        if (zoneCoteActuelle != caseTuileVoisine->getZoneParente()) {
            ttOuvertures += caseTuileVoisine->getZoneParente()->ouvertures - 2;
            //puis on fusionne les zones
            transfererZone(caseTuileVoisine->getZoneParente(), zoneCoteActuelle);
        } else {
            ttOuvertures -= 2;
        }
        zoneCoteActuelle->ouvertures = ttOuvertures;
        // Si caseCote est Prairie ou chemin ou rivière, alors on peut fusionner aussi les COINS avec la case à côté
        fusionZonesCOINS(tuile, i, tuileVoisine);
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
void Plateau::transfererZone(Zone *zoneASuppr, Zone *zoneB) {
    // on ajoute toutes les cases de la zoneASuppr à la zoneB
    for (Case *_case: zoneASuppr->getCases()) {
        _case->setZoneParente(zoneB);
        zoneB->ajouterCase(_case);
    }

    if (zoneASuppr == zoneB) { //si ce sont les mêmes adresses on supprime pas
        return;
    }

    //on supprime la zone A de la liste
    int i = 0;
    for (Zone *z: zones) {
        if (z == zoneASuppr) {
            zones.erase(zones.begin() + i);
            break;
        }
        i++;
    }
}

void Plateau::ajouterTuile(Tuile *tuile, Coord *coord) {
    plateau.emplace_back(coord, tuile);
    fusionnerZonesAvecPlateau(tuile);
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


Coord *Plateau::findCoordTuile(Tuile *tuile) {

    for (std::pair<Coord *, Tuile *> pairTuile: Plateau::getInstance()->plateau) {//pour permettre que findCoordTuile soit public
        if (pairTuile.second == tuile) {
            return pairTuile.first;
        }
    }
    throw std::invalid_argument("tuile non trouvée");
}

Tuile *Plateau::findTuileVoisine(Coord *coordTuile, int i) {
    Coord *deplacement = ParametresPartie::toDeplacement(DIRECTIONS_COTE[i]);
    auto *coordTuileVoisine = new Coord(coordTuile->x_ + deplacement->x_, coordTuile->y_ + deplacement->y_);
    //on a sa coordonnée, maintenant on cherche la bonne tuile dans la liste
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
        if (pairTuile.first->x_ == coordTuileVoisine->x_ && pairTuile.first->y_ == coordTuileVoisine->y_) {
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
                transfererZone(caseAFusionner->getZoneParente(), tuile->cases[deuxCoin]->getZoneParente());
            }
        }
    }
}


bool Plateau::checkerTuile(Tuile *tuile, Coord *coord) {
    map<DIRECTION, Case *> cases = tuile->getCases();
//##########################################################
//checker riviere
    bool checkRiviere = true;
    for (auto i: DIRECTIONS_ORDERED) {
        if (cases[i]->getZoneType() == ZONE_TYPE::RIVIERE) {
            checkRiviere = false;
        }
    }//si il y a une rivière sur la tuile
    //on doit vérifier que le côté rivière est bien collé  1 fois à un voisin.
    if (cases[DIRECTION::MILIEU]->getZoneType() == ZONE_TYPE::SOURCE) checkRiviere = true;




//##########################################################
/*
 * règle pour la rivière qui tourne : on doit vérifier que la rivière ne fait pas demi-tour, pourr cela,
 * on a la direction initiale de la tuile source, et on vérifie ici, que le joueur ne veut pas poser une tuile
 * avec une rivière qui part vers la direction inverse de la dir de la tuile source
*/
    //on cherche la dir interdite :
    DIRECTION dirInterdite = DIRECTION::MILIEU;
    int i = 0;
    for (; i < 4; i++) {
        if (DIRECTIONS_COTE[i] == dirSource) dirInterdite = DIRECTIONS_COTE_INVERSE[i];
    }
    bool testerDouVientRiviere = false;
    if (cases[dirInterdite]->getZoneType() == ZONE_TYPE::RIVIERE)//si une riviere pointe vers la dir interdite
        if (cases[dirSource]->getZoneType() != ZONE_TYPE::RIVIERE)
            testerDouVientRiviere = true;




//##########################################################
    //on prend les voisins de la tuile
    auto voisin_droit = new Coord(coord->x_ + 1, coord->y_);
    auto voisin_gauche = new Coord(coord->x_ - 1, coord->y_);
    auto voisin_haut = new Coord(coord->x_, coord->y_ - 1);
    auto voisin_bas = new Coord(coord->x_, coord->y_ + 1);
    bool a_un_voisin = false;//vérifier que la tuile a bien un voisin
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {

        map<DIRECTION, Case *> casesVoisines = pairTuile.second->getCases();
        if (coord->x_ == pairTuile.first->x_ && coord->y_ == pairTuile.first->y_) {
            return false;//vérifie que l'utilisateur n'a pas cliqué sur une tuile existante
        }

        //verifie que pour chaque tuile, la zone adjacente est la même
        if (pairTuile.first->x_ == voisin_droit->x_ && pairTuile.first->y_ == voisin_droit->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::EST]->getZoneType() != casesVoisines[DIRECTION::OUEST]->getZoneType()) return false;
            if (cases[DIRECTION::EST]->getZoneType() == ZONE_TYPE::RIVIERE) {
                if (testerDouVientRiviere && dirInterdite != DIRECTION::EST)
                    return false; //la riviere n'est pas bien orientée !!
                checkRiviere = true;
            }
        }
        if (pairTuile.first->x_ == voisin_gauche->x_ && pairTuile.first->y_ == voisin_gauche->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::OUEST]->getZoneType() != casesVoisines[DIRECTION::EST]->getZoneType()) return false;
            if (cases[DIRECTION::OUEST]->getZoneType() == ZONE_TYPE::RIVIERE) {
                if (testerDouVientRiviere && dirInterdite != DIRECTION::OUEST) return false;
                checkRiviere = true;
            }
        }
        if (pairTuile.first->x_ == voisin_haut->x_ && pairTuile.first->y_ == voisin_haut->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::NORD]->getZoneType() != casesVoisines[DIRECTION::SUD]->getZoneType()) return false;
            if (cases[DIRECTION::NORD]->getZoneType() == ZONE_TYPE::RIVIERE) {
                if (testerDouVientRiviere && dirInterdite != DIRECTION::NORD) return false;
                checkRiviere = true;
            }
        }
        if (pairTuile.first->x_ == voisin_bas->x_ && pairTuile.first->y_ == voisin_bas->y_) {
            a_un_voisin = true;
            if (cases[DIRECTION::SUD]->getZoneType() != casesVoisines[DIRECTION::NORD]->getZoneType()) return false;
            if (cases[DIRECTION::SUD]->getZoneType() == ZONE_TYPE::RIVIERE) {
                if (testerDouVientRiviere && dirInterdite != DIRECTION::SUD) return false;
                checkRiviere = true;
            }
        }
    }

//si la condition de la rivière est bien respectée
    if (checkRiviere)
        return a_un_voisin ||
               plateau.

                       empty(); //s'il y a un voisin ou si c'est la premiere tuile placée on peut la poser
    else {
        return false;
    }

}

/**
 * Permet de poser un meeple sur une case.
 * @param couleur  la couleur du meeple à poser
 * @param c  la case sur laquelle poser le meeple
 * @param type  le type de meeple à poser
 * @param meeplesPoses  la liste des meeples déjà posés de Partie
 * @param meeplesEnReserve  la liste des meeples en réserve de Partie
 * @return true si le meeple a bien été posé, false sinon.
 */
bool Plateau::poserMeeple(COULEUR couleur, Case *c, MEEPLE_TYPE type, vector<Meeple *> &meeplesPoses,
                          vector<Meeple *> &meeplesEnReserve) {

    //vérifie qu'on ne pose pas un abbé n'importe où
    if (type == MEEPLE_TYPE::ABBE) {
        if (!(c->getZoneType() == ZONE_TYPE::PRAIRIE && c->getSuppType() == SUPP_TYPE::JARDIN) &&
            c->getZoneType() != ZONE_TYPE::ABBAYE) {
            cout << "Vous ne pouvez pas poser un abbe autre part que sur une abbaye ou un jardin" << endl;
            return false;
        }
    } else {
        //vérification que l'extension PAYSANS est activée
        if (c->getZoneType() == ZONE_TYPE::PRAIRIE &&
            not Jeu::getInstance()->hasExtension(EXTENSION::PAYSANS)) { //on a le droit de poser un ABBE sur une prairie
            cout << "Vous devez avoir l'extension PAYSANS pour poser un meeple sur une case de type PRAIRIE" << endl;
            return false;
        }
        //on vérifie qu'on ne pose pas de meeple normal sur un jardin
        if (c->getZoneType() == ZONE_TYPE::PRAIRIE && c->getSuppType() == SUPP_TYPE::JARDIN) {
            cout << "Vous devez poser un meeple Abbé sur un jardin"
                 << endl;
            return false;
        }
        if (c->getZoneType() == ZONE_TYPE::ABBAYE) return false;
    }

    if (c->getZoneType() == ZONE_TYPE::RIVIERE || c->getZoneType() ==
                                                  ZONE_TYPE::FIN_DE_ROUTE)//on a pas le droit de poser de meeples sur la rivière ou fin de route
        return false;

    Zone *zone = c->getZoneParente();
    // si pas de meeple déjà posé dans la zone. Mais pour les prairies on peut avoir plusieurs jardins avec abbés
    if (zone->getGagnants().empty() || c->getSuppType() == SUPP_TYPE::JARDIN) {

        unsigned int i = 0;
        //parcours des meeples en réserve
        for (Meeple *meeple: meeplesEnReserve) {
            if (meeple->getCouleur() == couleur && meeple->getType() == type) {
                //on a trouvé le meeple à poser
                //on déplace le meeple dans le bon tableau
                Meeple *m = meeplesEnReserve[i];
                meeplesPoses.push_back(m);
                meeplesEnReserve.erase(meeplesEnReserve.begin() + i);
                c->setMeeple(m);
                return true;
            }
            i++;
        }
//
//        while ((i < meeplesEnReserve.size() and couleur != meeplesEnReserve.at(i)->getCouleur() and
//                type != meeplesEnReserve.at(i)->getType())) { i++; }
//
//        //retirer du tableau "meeple en réserve" le meeple
//        if (i > meeplesEnReserve.size()) {

//            throw CarcassonneException("pas de meeple de ce type et de cette couleur disponible");
//        }

    }
    return false;
}

bool Plateau::retirerLeMeeple(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve, Case *c) {
    if (c->getMeeplePose() != nullptr) {//si il y a un meeple
        cout << "Joueur " << Partie::getInstance()->getJoueur(c->getMeeplePose()->getCouleur())->getNom()
             << " a recupere un meeple" << endl;
        Joueur *joueurGagnant = Partie::getInstance()->getJoueur(c->getMeeplePose()->getCouleur());
        if (joueurGagnant == nullptr) {
            throw CarcassonneException("joueur gagnant null");
        }
//        donnerPointsPourJoueur(joueurGagnant, c->getZoneParente());
        cout << "Joueur " << joueurGagnant->getNom() << " a recupere un meeple de type "
             << ParametresPartie::toStringMEEPLE_TYPE(c->getMeeplePose()->getType()) << endl;// " et a maintenant "
//             << joueurGagnant->getNbPoints() << " points" << endl;


        meeplesEnReserve.push_back(c->getMeeplePose());//on l'ajoute dans le tableau des meeples en réserve
        int i = 0;
        for (Meeple *meeple: meeplesPoses) {
            if (c->getMeeplePose() == meeple)
                meeplesPoses.erase(meeplesPoses.begin() + i);//et on le retire du tableau des meeple poses
            i++;
        }
        c->retirerMeeplePose(); // on retire le meeple de la case

        return true;
    } else { return false; }
}

std::vector<Coord *> Plateau::retirerMeeples(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve) {
    std::vector<Coord *> coord_tuiles_de_zones_ouvertes;
    for (auto zone: zones) {//on regarde toutes les zones
        bool compterLesPoints = false;
        vector<Joueur *> gagnantsZone = zone->getGagnants();
        if (zone->getType() == ZONE_TYPE::ABBAYE) { // on retire les abbes
            Case *c = zone->getCases()[0];//parce qu'il y a qu'une seule case dans la zone abbaye
            if (CompterVoisins(c->getTuileParente()) == 8) {
                cout << "\t on retire le meeple de l'Abbaye" << endl;
                if (retirerLeMeeple(meeplesPoses, meeplesEnReserve, c)) {
                    compterLesPoints = true;
                    coord_tuiles_de_zones_ouvertes.push_back(Plateau::findCoordTuile(c->getTuileParente()));
                }
            }
        } else if (zone->getType() == ZONE_TYPE::PRAIRIE) { //on retire les meeples qui sont dans les jardins
            for (auto c: zone->getCases()) {//pour toutes les cases de cette zone
                if (c->getSuppType() == SUPP_TYPE::JARDIN && CompterVoisins(c->getTuileParente()) == 8) {
                    cout << "on retire un meeple sur un JARDIN" << endl;
                    if (retirerLeMeeple(meeplesPoses, meeplesEnReserve, c)) {
                        compterLesPoints = true;
                        coord_tuiles_de_zones_ouvertes.push_back(Plateau::findCoordTuile(c->getTuileParente()));
                    }
                }
            }
        } else if (!(zone->estOuverte()) && zone->getType() != ZONE_TYPE::FIN_DE_ROUTE) { // si la zone est fermée
            for (auto c: zone->getCases()) {//pour toutes les cases de cette zone
                if (retirerLeMeeple(meeplesPoses, meeplesEnReserve, c)) {
                    compterLesPoints = true;
                    coord_tuiles_de_zones_ouvertes.push_back(Plateau::findCoordTuile(c->getTuileParente()));
                }
            }
        }

        if (compterLesPoints)//si un meeple a été retiré, la zone est donc fermée, on peut compter les points
            for (Joueur *joueur: gagnantsZone) {
                donnerPointsPourJoueur(joueur, zone);
                cout << "Joueur " << joueur->getNom() << "a maintenant " << joueur->getNbPoints() << " points" << endl;
            }
    }
    return coord_tuiles_de_zones_ouvertes;
}

Coord *Plateau::retirerAbbe(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve, COULEUR couleur) {
    for (auto zone: zones) {
        if (zone->getType() == ZONE_TYPE::ABBAYE || zone->getType() == ZONE_TYPE::PRAIRIE)
            for (auto c: zone->getCases()) {
                if (c->getMeeplePose() != nullptr)
                    if (c->getMeeplePose()->getType() == MEEPLE_TYPE::ABBE &&
                        couleur == c->getMeeplePose()->getCouleur()) {
                        //on vérifie la couleur du joueur et celui du meeple à retirer, on ne veut pas retirer un meeple qui n'appartient pas au joueur
                        meeplesEnReserve.push_back(
                                c->getMeeplePose());//on l'ajoute dans le tableau des meeples en réserve
                        int i = 0;
                        for (Meeple *meeple: meeplesPoses) {
                            if (meeple == c->getMeeplePose())
                                meeplesPoses.erase(
                                        meeplesPoses.begin() + i);//et on le retire du tableau des meeple poses
                            i++;
                        }
                        Joueur *joueurGagnant = Partie::getInstance()->getJoueur(couleur);
                        donnerPointsPourJoueur(joueurGagnant, c->getZoneParente());
                        cout << "Joueur " << joueurGagnant->getNom() << " a recupere un meeple ABBE" << endl;
                        c->retirerMeeplePose(); // on retire le meeple de la case
                        return findCoordTuile(c->getTuileParente());
                    }
            }
    }
    return nullptr; //si les conditions ne sont pas respectées, rien n'est retiré
}

/*
void Plateau::retirerMeeple(vector<Meeple *> &meeplesPoses, vector<Meeple *> &meeplesEnReserve) {
    for (auto zone: zones) {//on regarde toutes les zones
        if (!(zone->estOuverte()) && zone->getType()!=ZONE_TYPE::ABBAYE) { // si la zone est fermée
            for (auto c: zone->getCases()) {//pour toutes les cases de cette zone
                if (c->getMeeplePose() != nullptr) {//si il y a un meeple
                    meeplesEnReserve.push_back(c->getMeeplePose());//on l'ajoute dans le tableau des meeples en réserve
                    int i = 0;
                    for (auto meeple: meeplesPoses) {
                        if (meeple == c->getMeeplePose())
                            meeplesPoses.erase(meeplesPoses.begin() + i);//et on le retire du tableau des meeple poses
                        i++;
                    }
                    Joueur *joueurGagnant = Partie::getInstance()->getJoueur(c->getMeeplePose()->getCouleur());
                    donnerPointsPourJoueur(joueurGagnant, c->getZoneParente());
                    cout << "Joueur " << joueurGagnant->getNom() << " a recupere un meeple" << endl;
                    c->retirerMeeplePose(); // on retire le meeple de la case
                }
            }
        }
    }
}
*/

void Plateau::afficherConsole() {
//    HANDLE console_color; //pour afficher en couleur le plateau (ne fonctionne que sur windows, avec la lib windows.h
//    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
//on trouve le coin en haut à gauche du plateau par rapport aux coordonnées (x,y) des tuiles
//puis on affiche toutes les tuiles une par une
    Coord *coinHautGauche = getCoinHautGauche();
    Coord *coinBasDroite = getCoinBasDroite();
    for (int y = coinHautGauche->y_; y <= coinBasDroite->y_; y++) {
        for (int iYCase = 0; iYCase < 3; iYCase++) {//permet de passer sur les 3 hauteurs de cases
            for (int x = coinHautGauche->x_; x <= coinBasDroite->x_; x++) {
                for (int iXCase = 0; iXCase < 3; iXCase++) {//permet de passer sur les 3 hauteurs de cases
                    bool found = false;
                    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
                        if (pairTuile.first->x_ == x and pairTuile.first->y_ == y) {
                            Case *c = pairTuile.second->cases[DIRECTIONS_ORDERED[iYCase * 3 + iXCase]];
//                            ColorForZone(console_color, c);
                            cout << c->toString() << " ";
//                            SetConsoleTextAttribute(console_color, COLOR_NORMALE);
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
        cout << "\n\n\n\n";
    }
}

//void Plateau::ColorForZone(HANDLE console_color, const Case *c) {
//    //cf https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.codeproject.com%2FArticles%2F24896%2FJLib-A-Windows-Console-Library&psig=AOvVaw2HJb7bJSXUngLwowMwWUs7&ust=1653986979192000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCIjbmefXifgCFQAAAAAdAAAAABAD
//
//    switch (c->getZoneType()) {
//        case ZONE_TYPE::PRAIRIE:
//            SetConsoleTextAttribute(console_color, 32);//34
//            break;
//        case ZONE_TYPE::VILLE:
//            SetConsoleTextAttribute(console_color, 203);//204
//            break;
//        case ZONE_TYPE::CHEMIN:
//            SetConsoleTextAttribute(console_color, 112);//119
//            break;
//        case ZONE_TYPE::RIVIERE:
//            SetConsoleTextAttribute(console_color, 16);//19
//            break;
//        case ZONE_TYPE::FIN_DE_ROUTE:
//            SetConsoleTextAttribute(console_color, 8);
//            break;
//        case ZONE_TYPE::ABBAYE:
//            SetConsoleTextAttribute(console_color, 12);
//            break;
//        case ZONE_TYPE::JARDIN:
//            SetConsoleTextAttribute(console_color, 10);
//            break;
//        case ZONE_TYPE::LAC:
//            SetConsoleTextAttribute(console_color, 16);
//            break;
//        case ZONE_TYPE::SOURCE:
//            SetConsoleTextAttribute(console_color, 16);
//            break;
//        case ZONE_TYPE::CATHEDRALE:
//            SetConsoleTextAttribute(console_color, 48);
//            break;
//        case ZONE_TYPE::AUTRE:
//            break;
//    }
//}

Coord *Plateau::getCoinHautGauche() {
    auto *coinHautGauche = new Coord(tailleMaxPlateau,
                                     tailleMaxPlateau);
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
        if (pairTuile.first->x_ < coinHautGauche->x_) {
            coinHautGauche->x_ = pairTuile.first->x_;
        }
        if (pairTuile.first->y_ < coinHautGauche->y_) {
            coinHautGauche->y_ = pairTuile.first->y_;
        }
    }
    if (coinHautGauche->x_ == tailleMaxPlateau || coinHautGauche->y_ == tailleMaxPlateau) {
        throw CarcassonneException("erreur dans le calcul du coin haut gauche");
    }
    return coinHautGauche;
}

Coord *Plateau::getCoinBasDroite() {
    auto *coinBasDroite = new Coord(-tailleMaxPlateau, -tailleMaxPlateau);
    for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
        if (pairTuile.first->x_ > coinBasDroite->x_) {
            coinBasDroite->x_ = pairTuile.first->x_;
        }
        if (pairTuile.first->y_ > coinBasDroite->y_) {
            coinBasDroite->y_ = pairTuile.first->y_;
        }
    }
    if (coinBasDroite->x_ == -tailleMaxPlateau || coinBasDroite->y_ == -tailleMaxPlateau) {
        throw CarcassonneException("erreur dans le calcul du coin bas droite");
    }
    return coinBasDroite;
}

void Plateau::donnerPointsPourJoueur(Joueur *pJoueur, Zone *pZone) {
// en fonction du type de la zone, on affecte pas le même nombre de points avec la méthode joueur.ajouterPoints
    vector<Tuile *> tuilesPassees;
    //on vérifie s'il y a une auberge ou une cathédrale sur le chemin
    bool auberge = false;
    bool cathedrale = false;
    for (Case *c: pZone->getCases()) {
        if (c->getSuppType() == SUPP_TYPE::AUBERGE) {
            auberge = true;
        }
        if (c->getSuppType() == SUPP_TYPE::CATHEDRALE) {
            cathedrale = true;
        }
    }
    //pour chaque case de la zone, on ajoute les points au joueur
    for (Case *c: pZone->getCases()) {
        //si la tuile parente de la case est dans tuilesPassees, on continue;
        if (std::find(begin(tuilesPassees), end(tuilesPassees), c->getTuileParente()) != tuilesPassees.end())
            continue;

        if (c->getSuppType() == SUPP_TYPE::BLASON) {
            if (cathedrale) {
                pJoueur->ajouterPoints(3);
            } else {
                pJoueur->ajouterPoints(2);
            }
        }
        if (pZone->getType() == ZONE_TYPE::VILLE) {
            if (cathedrale) {
                pJoueur->ajouterPoints(3);
            } else {
                pJoueur->ajouterPoints(2);
            }
            tuilesPassees.push_back(c->getTuileParente());
        }
        if (pZone->getType() == ZONE_TYPE::CHEMIN) {
            if (auberge) {
                pJoueur->ajouterPoints(2);
            } else {
                pJoueur->ajouterPoints(1);
            }
            tuilesPassees.push_back(c->getTuileParente());
        }
        if (pZone->getType() == ZONE_TYPE::ABBAYE ||
            c->getSuppType() == SUPP_TYPE::JARDIN) {
            cout << "essai d'ajout de points pour le joueur "
                 << ParametresPartie::toStringCOULEUR(pJoueur->getCouleur()) << endl;
//            if (c->getMeeplePose() != nullptr && c->getMeeplePose()->getCouleur() == pJoueur->getCouleur()) {
            cout << "ajout de " << CompterVoisins(c->getTuileParente()) + 1 << "points pour jardin ou abbaye"
                 << endl;
            pJoueur->ajouterPoints(CompterVoisins(c->getTuileParente()) + 1);
            tuilesPassees.push_back(c->getTuileParente());
//            }
        }
    }
}


void Plateau::finDePartie() {
    for (auto zone: zones) {
        vector<Joueur *> joueur = zone->getGagnants();
        for (auto j: joueur) {
            donnerPointsPourJoueurFinDePartie(j, zone);
        }
    }
}


void Plateau::donnerPointsPourJoueurFinDePartie(Joueur *pJoueur, Zone *pZone) {
// en fonction du type de la zone, on affecte pas le même nombre de points avec la méthode joueur.ajouterPoints
    vector<Tuile *> tuilesPassees;
    //on vérifie s'il y a une auberge ou une cathédrale sur le chemin
    bool auberge = false;
    bool cathedrale = false;
    for (Case *c: pZone->getCases()) {
        if (c->getSuppType() == SUPP_TYPE::AUBERGE) {
            auberge = true;
        }
        if (c->getSuppType() == SUPP_TYPE::CATHEDRALE) {
            cathedrale = true;
        }
    }

    //pour chaque case de la zone, on ajoute les points au joueur
    for (Case *c: pZone->getCases()) {
        //si la tuile parente de la case est dans tuilesPassees, on continue;
        if (std::find(begin(tuilesPassees), end(tuilesPassees), c->getTuileParente()) != tuilesPassees.end())
            continue;

        if (c->getSuppType() == SUPP_TYPE::BLASON) {
            pJoueur->ajouterPoints(1);
        }
        if (pZone->getType() == ZONE_TYPE::VILLE) {
            if (cathedrale) {
                pJoueur->ajouterPoints(0);
            } else {
                pJoueur->ajouterPoints(1);
            }
            tuilesPassees.push_back(c->getTuileParente());
        }
        if (pZone->getType() == ZONE_TYPE::CHEMIN) {
            if (auberge) {
                pJoueur->ajouterPoints(0);
            } else {
                pJoueur->ajouterPoints(1);
            }
            tuilesPassees.push_back(c->getTuileParente());
        }
        if (pZone->getType() == ZONE_TYPE::ABBAYE ||
            c->getSuppType() == SUPP_TYPE::JARDIN) {
            pJoueur->ajouterPoints(CompterVoisins(c->getTuileParente()));
            tuilesPassees.push_back(c->getTuileParente());
        }
    }
    //cas spécifique : prairie
    if (pZone->getType() == ZONE_TYPE::PRAIRIE) {
        pJoueur->ajouterPoints(3 * compterNbVillesAdjacentesFermees(pZone));
    }
}

int Plateau::CompterVoisins(Tuile *tuile) {
    int nbVoisins = 0;
    vector<Tuile *> tuilesPassees;
    Coord *co = findCoordTuile(tuile);

    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            auto voisin = new Coord(co->x_ + i, co->y_ + j);
            for (std::pair<Coord *, Tuile *> pairTuile: plateau) {
                if (std::find(begin(tuilesPassees), end(tuilesPassees), pairTuile.second) != tuilesPassees.end())
                    continue;
                if (voisin->x_ == pairTuile.first->x_ && voisin->y_ == pairTuile.first->y_ &&
                    pairTuile.second != tuile) {
                    nbVoisins++;
                    tuilesPassees.push_back(pairTuile.second);
                }
            }
        }
    return nbVoisins;
}


int Plateau::compterNbVillesAdjacentesFermees(Zone *prairie) {
    std::set<Zone *> villesAdjacentesFermees;//Set : pour qu'il n'y ait pas de doublons

    //parcours des cases de la prairie
    for (Case *c: prairie->getCases()) {
        //pour chaque case de la prairie, on cherche ses cases adjacentes dans la tuile
        std::vector<Case *> voisins = getCasesAdjacentes(c->getTuileParente(), c->getDirection());
        for (Case *_c: voisins) {
            //on parcours toutes les cases voisines et on compte sa prairie une seule fois
            if (_c->getZoneType() == ZONE_TYPE::VILLE && !_c->getZoneParente()->estOuverte()) {
                villesAdjacentesFermees.insert(_c->getZoneParente());
            }
        }
    }
    return (int) villesAdjacentesFermees.size();
}

/**
 * Renvoie les cases adjacentes à une case de la zone.
 * @param tuile
 * @param direction
 * @return
 */
std::vector<Case *> Plateau::getCasesAdjacentes(Tuile *tuile, DIRECTION direction) {
    std::vector<Case *> casesAdjacentes;
    if (direction != DIRECTION::MILIEU) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::MILIEU]);
    } else {
        //renvoyer toutes les directions sauf le milieu
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_OUEST]);
    }
    if (direction == DIRECTION::NORD) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::SUD) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::EST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_EST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
    }
    if (direction == DIRECTION::OUEST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD_OUEST]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
    }
    if (direction == DIRECTION::NORD_EST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::NORD_OUEST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::NORD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
    }
    if (direction == DIRECTION::SUD_EST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::EST]);
    }
    if (direction == DIRECTION::SUD_OUEST) {
        casesAdjacentes.push_back(tuile->cases[DIRECTION::SUD]);
        casesAdjacentes.push_back(tuile->cases[DIRECTION::OUEST]);
    }
    return casesAdjacentes;
}

void Plateau::setDirSource(DIRECTION dirSource) {
    Plateau::dirSource = dirSource;
}
