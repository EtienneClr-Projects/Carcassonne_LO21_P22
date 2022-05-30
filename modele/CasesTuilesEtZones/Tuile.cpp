
#include "CasesTuilesEtZones/Tuile.h"
#include "JeuPiocheEtPlateau/Plateau.h"

# include <string>
# include <map>
#include <windows.h>


using namespace std;


Tuile::Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage) {
    this->cases = std::move(cases);
    this->cheminImage = std::move(cheminImage);
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
