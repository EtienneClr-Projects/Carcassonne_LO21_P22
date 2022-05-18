//
// Created by etienne on 27/04/2022.
//

#ifndef CARCASSONNE_LO21_P22_PARTIE_H
#define CARCASSONNE_LO21_P22_PARTIE_H

//Partie est un Singleton
class Partie {
private:
    //SINGLETON
    static Partie *instance;
    Partie()=default;

public:
    //SINGLETON
    Partie(const Partie&) = delete;
    Partie& operator=(const Partie&) = delete;
    static Partie& getInstance();

};


#endif //CARCASSONNE_LO21_P22_PARTIE_H
