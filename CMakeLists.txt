cmake_minimum_required(VERSION 3.21)
project(Carcassonne_LO21_P22)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.3.0\\mingw_64\\lib\\cmake\\")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6Widgets REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
include_directories(modele)

add_executable(Carcassonne_LO21_P22
        main.cpp
        modele/CasesTuilesEtZones/Zone.cpp modele/CasesTuilesEtZones/Zone.h controleur/controleur.cpp controleur/controleur.h vue/vue.cpp vue/vue.h modele/Gestion/gestionScore.cpp modele/Gestion/gestionScore.h modele/JoueurEtRessources/Joueur.cpp modele/JoueurEtRessources/Joueur.h modele/CasesTuilesEtZones/Case.cpp modele/CasesTuilesEtZones/Case.h modele/CasesTuilesEtZones/Prairie.cpp modele/CasesTuilesEtZones/Prairie.h modele/Gestion/ParametresPartie.cpp modele/Gestion/ParametresPartie.h modele/JoueurEtRessources/JoueurRessources.cpp modele/JoueurEtRessources/JoueurRessources.h modele/Gestion/Partie.cpp modele/Gestion/Partie.h modele/JeuPiocheEtPlateau/Jeu.cpp modele/JeuPiocheEtPlateau/Jeu.h modele/JeuPiocheEtPlateau/Pioche.cpp modele/JeuPiocheEtPlateau/Pioche.h modele/JeuPiocheEtPlateau/Plateau.cpp modele/JeuPiocheEtPlateau/Plateau.h modele/CasesTuilesEtZones/Tuile.cpp modele/CasesTuilesEtZones/Tuile.h modele/JoueurEtRessources/Meeple.cpp modele/JoueurEtRessources/Meeple.h
        controleurpartie.h
        controleurpartie.cpp
        jeu_carcassonne.cpp
        jeu_carcassonne.h
        jeu_carcassonne.ui
        vuemenu.cpp
        vuemenu.h
        vuemenu.ui
        vuepartie.cpp
        vuepartie.h
        vuepartie.ui
        Ressources.qrc
        )


target_link_libraries(Carcassonne_LO21_P22 Qt6::Widgets Qt6::Core)
