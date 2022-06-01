#include "controleurpartie.h"


controleurPartie::controleurPartie(int nb_joueurs, bool exPaysans, bool exAbbe, bool exCathAub, bool exRiviere) {
    vector<EXTENSION> extensionsChoisies;
    extensionsChoisies.push_back(EXTENSION::NORMAL);
    if (exPaysans) {
        extensionsChoisies.push_back(EXTENSION::PAYSANS);
    }
    if (exAbbe) {
        extensionsChoisies.push_back(EXTENSION::ABBE);
    }
    if (exCathAub) {
        extensionsChoisies.push_back(EXTENSION::AUBERGES_CATHEDRALES);
    }
    if (exRiviere) {
        extensionsChoisies.push_back(EXTENSION::RIVIERE);
    }

    //extensionsChoisies.push_back(EXTENSION::MARCHANDS_BATISSEURS);


    pPartie = ParametresPartie::getInstance();
    pPartie->setExtensionsChoisies(extensionsChoisies);
    pPartie->setNombreJoueurs(nb_joueurs);

    jeu = Jeu::getInstance();
    jeu->setExtensions(extensionsChoisies);

    pioche = new Pioche(jeu->tuiles);
    plateau = Plateau::getInstance();

}

controleurPartie::~controleurPartie() {
    delete pioche;
}
