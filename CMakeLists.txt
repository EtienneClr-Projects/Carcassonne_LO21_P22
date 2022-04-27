cmake_minimum_required(VERSION 3.21)
project(Carcassonne_LO21_P22)

set(CMAKE_CXX_STANDARD 14)

include_directories(modele)

add_executable(Carcassonne_LO21_P22
        main.cpp
        modele/zone.cpp modele/zone.h controleur/controleur.cpp controleur/controleur.h vue/vue.cpp vue/vue.h)
