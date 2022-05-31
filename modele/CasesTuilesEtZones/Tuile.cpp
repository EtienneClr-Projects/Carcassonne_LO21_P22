
#include "CasesTuilesEtZones/Tuile.h"
#include "JeuPiocheEtPlateau/Plateau.h"

# include <string>
# include <map>
#include <windows.h>


using namespace std;


Tuile::Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage) {
    this->cases = std::move(cases);
    this->cheminImage = std::move(cheminImage);
    fusionZonesInternes();
}

void Tuile::fusionZonesInternes() {
    cout << "\n\n FUSION DE LA TUILE :" << toString() << endl;
//###################ZONES INTERNES###################
    //fusion des zones internes
    std::vector<pair<int, Zone *>> zonesInternesTemp = calcZonesInternes();
    // on ajoute les zones internes à la liste des zones
    for (std::pair<const int, Zone *> pair: zonesInternesTemp) {
        zonesInternes.push_back(pair.second);
        cout << "Ajout de la zone : " << pair.second->toString() << endl;
    }
    //on met à jour les ouvertures de chaque zone qui sont sur les côtés de la tuile
    majOuverturesZonesCOTE(this);

    cout << "\nFIN FUSION INTERNE DE LA TUILE :" << toString() << endl;
}


std::vector<pair<int, Zone *>> Tuile::calcZonesInternes() {
    std::vector<pair<int, Zone *>> zonesInternesTemp;
    for (std::pair<const DIRECTION, Case *> _caseTuile: cases) {
        //on vérifie que l'id de la case n'est pas déjà l'id d'une zone existante dans zonesInternes de même type
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

void Tuile::majOuverturesZonesCOTE(Tuile *tuile) {
    for (int i = 0; i < 4; i++) {
        std::cout << "I" + std::to_string(i) << " ";
        // on prend sa zone et on lui ajoute +1 en ouverture
        Case *caseCote = tuile->cases[DIRECTIONS_COTE[i]];
        Zone *zoneCote = caseCote->getZoneParente();
        tuile->cases[DIRECTIONS_COTE[i]]->getZoneParente()->ouvertures++;
//        std::cout << zoneCote->toString() << "ouvertures = " << zoneCote->ouvertures << std::endl;
        //la tuile n'est pas encore vraiment posée, donc toutes les zones sont ouvertes, donc on les incrémente toutes
    }
}

Case *Tuile::getCase(DIRECTION d) const {
    return cases.find(d)->second;
}

void Tuile::afficher() const {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "tuile:\n";
    for (int i = 1; i < 10; i++) {
        Case *c = getCase(DIRECTIONS_ORDERED[i - 1]);
        Plateau::ColorForZone(console_color, c);
        cout << c->toString() + " ";
        if (i % 3 == 0) cout << "\n";
    }
    SetConsoleTextAttribute(console_color, 15);
}

std::string Tuile::toString() {
    std::string res = "tuile:\n";
    for (int i = 1; i < 10; i++) {
        Case *c = getCase(DIRECTIONS_ORDERED[i - 1]);
        res += c->toString() + " ";
//        res += it.second->toString() + std::to_string(it.second->getIdConnexion()) +
//               " ";// +ParametresPartie::toStringDIRECTION(it.second->getDirection())+ " ";
        if (i % 3 == 0) res += "\n";
    }
    return res + "\t" + cheminImage;
}

void Tuile::pivoterTuileSensTrigo(int nbre_rotation) {
    std::map<DIRECTION, Case *> t2;
    //on tourne les cases de 90 degrés dans le sens inverse des aiguilles d'une montre
    //donc par exemple, la case NORD est la case EST de la tuile
    for (int i = 0; i < 8; i++) {
        t2[DIRECTIONS_COTE_COINS[i]] = cases[DIRECTIONS_COTE_COINS[(i + nbre_rotation * 2) % 8]];
    }
    t2[DIRECTION::MILIEU] = cases.find(DIRECTION::MILIEU)->second;

    //on modifie egalement la direction à l'intérieur des cases
    for (auto i: DIRECTIONS_ORDERED) {
        t2[i]->setDirection(i);
    }
    cases = t2;
}

std::map<DIRECTION, Case *> Tuile::getCases() const {
    return cases;
}

bool Tuile::estSource() {
    //on parcourt les cases de la tuile et si y'a une source on renvoie true
    for (auto &it: cases) {
        if (it.second->getZoneType() == ZONE_TYPE::SOURCE) {
            return true;
        }
    }
    return false;
}

bool Tuile::estLac() {
    //on parcourt les cases de la tuile et si y'a un lac on renvoie true
    for (auto &it: cases) {
        if (it.second->getZoneType() == ZONE_TYPE::LAC) {
            return true;
        }
    }
    return false;
}
