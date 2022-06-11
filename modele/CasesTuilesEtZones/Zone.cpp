#include <iostream>
#include "CasesTuilesEtZones/Zone.h"
#include "Gestion/Partie.h"


/**
 * Constructeur principal de la classe Zone.
 * @param type le type de la zone
 * @param init_case la case avec laquelle la zone est initialisée. C'est à dire la première case de la zone.
 */

Zone::Zone(Case *init_case) {
    this->type = init_case->getZoneType();

    this->cases.push_back(init_case);
}

const ZONE_TYPE &Zone::getType() {
    return this->type;
}

int Zone::getNombreDePoints() const {
    return this->points;
}

/**
 * Renvoie le gagnant actuel de la zone. C'est à dire celui qui a le plus de Meeples dans la zone.
 * @return le gagnant de la zone. nullptr si tous les joueurs en ont 0.
 */
vector<Joueur *> Zone::getGagnant() {
    cout << "\n\n\n" << endl;
    cout << "getGagnant" << endl;
    //on parcourt toutes les cases de la Zone, et on compte le nombre de Meeples de chaque COULEUR
    std::map<COULEUR, int> nbMeeplesParCouleur;
    for (Case *c: this->cases) {
        Meeple *m = c->getMeeplePose();
        if (m != nullptr) {
            cout << "m: " << ParametresPartie::toStringCOULEUR(m->getCouleur()) << endl;
            nbMeeplesParCouleur[m->getCouleur()]++;
            if (m->getType() == MEEPLE_TYPE::GRAND_MEEPLE) { //si grand meeple, on rajoute un point en plus
                cout << "GRAND MEEPLE ! PLUS 1 MEEPLE" << endl;
                nbMeeplesParCouleur[m->getCouleur()]++;
            }
        }
    }

    //on cherche le gagnants
    vector<Joueur *> gagnants;
    int nbMaxMeeples = 0;
    for (auto &it: nbMeeplesParCouleur) {
        if (it.second > nbMaxMeeples) {
            gagnants.clear();
            gagnants.push_back(Partie::getInstance()->getJoueur(it.first));
            nbMaxMeeples = it.second;
        } else if (it.second == nbMaxMeeples)
            gagnants.push_back(Partie::getInstance()->getJoueur(it.first));
    }
    //affichage des gagnants
    cout << "gagnants: ";
    for (Joueur *j: gagnants)
        cout << ParametresPartie::toStringCOULEUR(j->getCouleur()) << " : " << nbMeeplesParCouleur[j->getCouleur()]
             << endl;
    cout << endl;
    cout << "\n\n\n" << endl;
    return gagnants;
}

/**
 * Permet l'ajout d'une case à la zone. Vérifie également si la zone est bien ouverte.
 * @param c la case à ajouter
 */
void Zone::ajouterCase(Case *c) {
    if (c->getZoneType() == this->type) {
        this->cases.push_back(c);
    } else {
        cout << "Erreur: la zone " << this->toString() << " ne peut pas recevoir la case " << c->toString() << endl;
//        throw std::invalid_argument("Erreur : la case n'appartient pas à la bonne zone");
    }
}

/**
 * Renvoie la liste des cases de la zone.
 * @return la liste des cases de la zone
 */
std::vector<Case *> Zone::getCases() {
    return this->cases;
}

/**
 * Permet de savoir si la zone accepte l'extensions de cases.
 * @return vrai si la zone est ouverte, faux sinon.
 */
bool Zone::estOuverte() const {
    return this->ouvertures != 0;
}

std::string Zone::toString() {
    std::cout << "ZONE "<<this;
    std::string s = " de type " + ParametresPartie::toStringZONE_TYPE(this->type) + " : \n";
    for (Case *c: this->cases) {
        s += c->toString() + std::to_string(c->getIdConnexion()) + ", ";
    }
    s += "ouvertures = "+std::to_string(ouvertures);
    return s;
}

void Zone::supprimerCase(Case *pCase) {
    for (int i = 0; i < this->cases.size(); i++) {
        if (this->cases[i] == pCase) {
            this->cases.erase(this->cases.begin() + i);
            return;
        }
    }
}


