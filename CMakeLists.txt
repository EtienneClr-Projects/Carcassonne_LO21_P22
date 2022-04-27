cmake_minimum_required(VERSION 3.21)
project(Carcassonne_LO21_P22)

set(CMAKE_CXX_STANDARD 14)

include_directories(modele)

add_executable(Carcassonne_LO21_P22
        main.cpp
        modele/CasesTuilesEtZones/Zone.cpp modele/CasesTuilesEtZones/Zone.h controleur/controleur.cpp controleur/controleur.h vue/vue.cpp vue/vue.h modele/Gestion/gestionScore.cpp modele/Gestion/gestionScore.h modele/JoueurEtRessources/Joueur.cpp modele/JoueurEtRessources/Joueur.h modele/CasesTuilesEtZones/Case.cpp modele/CasesTuilesEtZones/Case.h modele/CasesTuilesEtZones/Prairie.cpp modele/CasesTuilesEtZones/Prairie.h modele/Gestion/Config.cpp modele/Gestion/Config.h modele/JoueurEtRessources/JoueurRessources.cpp modele/JoueurEtRessources/JoueurRessources.h modele/Gestion/Partie.cpp modele/Gestion/Partie.h modele/JeuPiocheEtPlateau/Jeu.cpp modele/JeuPiocheEtPlateau/Jeu.h modele/JeuPiocheEtPlateau/Pioche.cpp modele/JeuPiocheEtPlateau/Pioche.h modele/JeuPiocheEtPlateau/Plateau.cpp modele/JeuPiocheEtPlateau/Plateau.h modele/CasesTuilesEtZones/Tuile.cpp modele/CasesTuilesEtZones/Tuile.h)
