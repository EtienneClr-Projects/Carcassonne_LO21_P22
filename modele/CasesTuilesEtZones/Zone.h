//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_ZONE_H
#define CARCASSONNE_LO21_P22_ZONE_H

#include <map>
#include <vector>
#include "Gestion/Config.h"
#include "JoueurEtRessources/Joueur.h"


class Zone {
    // Une zone est une agrégation de cases. Elle peut être de différents types (cf. Config).
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

//##################################################################################################################
    //Methodes
public:
    // Constructeur
    explicit Zone(Case *init_case);

    ZONE_TYPE getType();

    int getNombreDePoints() const;

    Joueur getGagnant();

    void ajouterCase(Case c);

    void fusionnerAvecEtSupprimer(Zone *zone);

    bool estOuverte() const;

    std::vector<Case *> getCases();

    std::string toString();
};


#endif //CARCASSONNE_LO21_P22_ZONE_H
