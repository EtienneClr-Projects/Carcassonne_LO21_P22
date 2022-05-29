
#include "CasesTuilesEtZones/Tuile.h"

# include <string>
# include <map>


using namespace std;


Tuile::Tuile(std::map<DIRECTION, Case *> cases, std::string cheminImage) {
    this->cases = std::move(cases);
    this->cheminImage = std::move(cheminImage);
}

Case *Tuile::getCase(DIRECTION d) const {
    return cases.find(d)->second;
}

std::string Tuile::toString() {
    std::string res = "Tuile:\n";
    int i = 1;
    for (int i = 1; i < 10; i++) {
        res += getCase(DIRECTIONS_ORDERED[i - 1])->toString() + " ";
//        res += it.second->toString() + std::to_string(it.second->getIdConnexion()) +
//               " ";// +ParametresPartie::toStringDIRECTION(it.second->getDirection())+ " ";
        if (i % 3 == 0) res += "\n";
//        i++;
    }
    return res + "\t";// + cheminImage;
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
