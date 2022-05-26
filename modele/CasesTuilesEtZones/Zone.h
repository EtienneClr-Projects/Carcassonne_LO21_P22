#ifndef ZONE_H
#define ZONE_H
#pragma once
class Case;
#include "JoueurEtRessources/Joueur.h"
#include <map>
#include <vector>
#include"Gestion/ParametresPartie.h"


class Zone {
    // Une zone est une agrégation de cases. Elle peut être de différents types (cf. ParametresPartie).
    // Une zone est ouverte ou fermée en fonction de si on peut ajouter de nouvelles cases à la zone pour l'agrandir.
    // La zone est mise à jour à chaque ajout d'une nouvelle case et les points sont augmentés.
    // Lorsque deux zones de même type sont adjacentes, elles sont fusionnées.
    // Chaque zone contient un tableau gagnantsActuels qui contient les gagnants de la zone en fonction de leurs Meeples sur la zone.
    //
    // À la fin de la partie ou si la zone est fermée, on détermine le gagnant de la zone qui est celui qui possède le plus de Meeples.
    // Le gagnant remporte alors le nombre de points associé à la zone.


//##################################################################################################################
    // Attributs
protected:
    ZONE_TYPE type;
    bool ouverte = true;
    int points = 0;
    // Map associant le nombre de meeples de chaque joueur à la zone.
    std::map<Joueur *, int> gagnantsActuels;
    std::vector<Case *> cases;
    std::vector<Joueur *> joueursPartie;

//##################################################################################################################
    //Méthodes
public:
    // Constructeur
    explicit Zone(Case *init_case);

    const ZONE_TYPE &getType();

    int getNombreDePoints() const;

    Joueur getGagnant();

    bool estOuverte() const;

    std::vector<Case *> getCases();

    std::string toString();

    void ajouterCase(Case *c);

    void supprimerCase(Case *pCase);
};

#endif //CARCASSONNE_LO21_P22_ZONE_H


