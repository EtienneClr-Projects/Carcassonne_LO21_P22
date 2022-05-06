//
// Created by etienne on 27/04/2022.
//

#include "Zone.h"
#include "Gestion/Partie.h"

/**
 * Constructeur principal de la classe Zone.
 * @param type le type de la zone
 * @param init_case la case avec laquelle la zone est initialisée. C'est à dire la première case de la zone.
 */
Zone::Zone(Case *init_case, std::vector<Joueur *> joueursPartie) {
    this->type = init_case->getZoneType();

    this->cases.push_back(init_case);
    this->joueursPartie = joueursPartie;

    for (Joueur *joueur: joueursPartie) {//todo @Etienne : à améliorer ?
        this->gagnantsActuels.insert({joueur, 0});
    }
}

const ZONE_TYPE &Zone::getType() {
    return this->type;
}

int Zone::getNombreDePoints() const {
    return this->points;
}

/**
 * Renvoie le gagnant actuel de la zone. C'est à dire celui qui a le plus de Meeples dans la zone.
 * @return le gagnat de la zone.
 */
Joueur Zone::getGagnant() {
    // on parcourt la map des gagnants actuels et on prend celui qui a le plus de meeples dans la zone
    int nbMaxMeeples = 0;
    Joueur *gagnant = nullptr;
    for (auto &gagnantsActuel: this->gagnantsActuels) {
        if (gagnantsActuel.second > nbMaxMeeples) {
            nbMaxMeeples = gagnantsActuel.second;
            gagnant = gagnantsActuel.first;
        }
    }
    return *gagnant;
}

/**
 * Permet l'ajout d'une case à la zone. Vérifie également si la zone est bien ouverte.
 * @param c la case à ajouter
 */
void Zone::ajouterCase(Case c) {
    if (ouverte && c.getZoneType() == this->type) {
        this->cases.push_back(&c);
    } else {
        throw "Erreur : la case n'appartient pas à la bonne zone";
    }
}

/**
 * Permet de fusionner deux zones, lorsque deux tuiles adjacentes sont posées.
 * Supprime la zone passée en paramètre. //todo @Etienne
 * @param zone la zone à fusionner avec la zone courante
 */
void Zone::fusionnerAvecEtSupprimer(Zone *zone) {
    if (zone->getType() == this->type) {
        for (Case *c: zone->getCases()) {
            this->cases.push_back(c);
        }
    } else {
        throw "Erreur : la zone n'est pas du bon type";
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
 * Permet de savoir si la zone accepte l'extension de cases.
 * @return vrai si la zone est ouverte, faux sinon.
 */
bool Zone::estOuverte() const {
    return this->ouverte;
}

std::string Zone::toString() {
    std::string s = "ZONE de type " + Config::toStringZONE_TYPE(this->type) + " : \n";
    for (Case *c: this->cases) {
        s += c->toString() + ", ";
    }
    return s;
}
