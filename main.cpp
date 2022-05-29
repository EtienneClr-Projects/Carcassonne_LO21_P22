//
// Created by etienne on 27/04/2022.
//

#include <iostream>
#include "JeuPiocheEtPlateau/Pioche.h"
#include "JeuPiocheEtPlateau/Jeu.h"
#include "JeuPiocheEtPlateau/Plateau.h"

using namespace std;

void test_Jeu_Pioche_Tuile() {
    cout << "Hello, Carcassonne !" << endl;
    vector<EXTENSION> extensionsChoisies;
    extensionsChoisies.push_back(EXTENSION::NORMAL);
    extensionsChoisies.push_back(EXTENSION::ABBE);
    extensionsChoisies.push_back(EXTENSION::AUBERGES_CATHEDRALES);
    extensionsChoisies.push_back(EXTENSION::MARCHANDS_BATISSEURS);

    Jeu *jeu = Jeu::getInstance();
    jeu->setExtensions(extensionsChoisies);
    for (auto meeple: jeu->meeplesPossibleEnFonctionDesExtensions) {
        cout << meeple->toString() << endl;
    }
    cout << "\n" << endl;

    //test de la pioche
    auto *pioche = new Pioche(jeu->tuiles);
//    Tuile *t = pioche->piocher();
//    cout << t->toString() << endl;


    //test des tuilesPlateau
//    t->pivoterTuileSensTrigo(1);
//    cout << t->toString() << endl;
//    cout << t->getCase(DIRECTION::NORD_EST)->toString() << endl;

    vector<pair<Coord, Tuile *>> tuilesPlateau;

    Tuile *t2 = pioche->piocher();
    auto *c2 = new Coord(1, 1);
    cout << t2->toString() << endl;

    Tuile *t3 = pioche->piocher();
    auto *c3 = new Coord(2, 2);
    cout << t3->toString() << endl;

    Tuile *t4 = pioche->piocher();
    auto *c4 = new Coord(0, 2);
    cout << t4->toString() << endl;


    Plateau *plateau = Plateau::getInstance();
    cout << plateau->toString() << endl;
    plateau->ajouterTuile(t2, c2);
    plateau->ajouterTuile(t3, c3);
    plateau->ajouterTuile(t4, c4);


//    cout << "instance got" << endl;
//    cout << plateau->toString() << endl;
//    plateau->ajouterTuile(tuilesPlateau[0].second, tuilesPlateau[0].first);
//    cout << "tuile added" << endl;
//    plateau->ajouterTuile(tuilesPlateau[1].second, tuilesPlateau[1].first);
//    plateau->checkerTuile(tuilesPlateau[0].second, tuilesPlateau[0].first);
//    cout << plateau->checkerTuile(tuilesPlateau[1].second, tuilesPlateau[1].first) << endl;
    cout << "affichage de la console : " << endl;
    plateau->afficherConsole();
}


void test_ajout_user_Tuiles() {
    cout << "Hello, Carcassonne !" << endl;
    vector<EXTENSION> extensionsChoisies;
    extensionsChoisies.push_back(EXTENSION::NORMAL);
    extensionsChoisies.push_back(EXTENSION::ABBE);
    extensionsChoisies.push_back(EXTENSION::AUBERGES_CATHEDRALES);
    extensionsChoisies.push_back(EXTENSION::MARCHANDS_BATISSEURS);

    Jeu *jeu = Jeu::getInstance();
    jeu->setExtensions(extensionsChoisies);
    auto *pioche = new Pioche(jeu->tuiles);

    Plateau *plateau = Plateau::getInstance();


    while (1) {
        Tuile *t = pioche->piocher();
        cout << "vous avez pioche la tuile :" << t->toString() << endl;
        cout << "position de la tuile :";
        int x, y;
        cin >> x >> y;
        plateau->ajouterTuile(t, new Coord(x, y));
        cout << "\naffichage de la console : " << endl;
        plateau->afficherConsole();
    }


}

int main() {
    int nbJoueurs;
    vector<string> nomsJoueurs;
    vector<EXTENSION> extensionsChoisies;
    cout << "Hello, Carcassonne !" << endl;
    cout << "Combien de joueurs ? ";
    cin >> nbJoueurs;
    for (int i = 0; i < nbJoueurs; i++) {
        string nom;
        cout << "nom du joueur " << i + 1 << " : ";
        cin >> nom;
        nomsJoueurs.push_back(nom);
    }


    cout << "Choisissez les extensions : " << endl;
    cout << "1 : Abbe" << endl;
    cout << "2 : Auberges Cathedrales" << endl;
    cout << "3 : Marchands Batisseurs" << endl;
    cout << "4 : Riviere" << endl;
    cout << "5 : Tous" << endl;

    int choix;
    while (true) {
        cout << "Entrez un numero : ";
        cin >> choix;
        switch (choix) {
            case 1:
                extensionsChoisies.push_back(EXTENSION::ABBE);
                break;
            case 2:
                extensionsChoisies.push_back(EXTENSION::AUBERGES_CATHEDRALES);
                break;
            case 3:
                extensionsChoisies.push_back(EXTENSION::MARCHANDS_BATISSEURS);
                break;
            case 4:
                extensionsChoisies.push_back(EXTENSION::RIVIERE);
            case 5:
                extensionsChoisies.push_back(EXTENSION::NORMAL);
                extensionsChoisies.push_back(EXTENSION::ABBE);
                extensionsChoisies.push_back(EXTENSION::AUBERGES_CATHEDRALES);
                extensionsChoisies.push_back(EXTENSION::MARCHANDS_BATISSEURS);
                extensionsChoisies.push_back(EXTENSION::RIVIERE);
                break;
            default:
                cout << "Choix invalide" << endl;
                break;
        }
        if (choix != 7) {
            cout << "Voulez-vous ajouter une extension ? " << endl;
            cout << "1 : Oui" << endl;
            cout << "2 : Non" << endl;
            cin >> choix;
            if (choix == 2) break;
        }
    }

    extensionsChoisies.push_back(EXTENSION::NORMAL);
    Jeu *jeu = Jeu::getInstance();
    jeu->setExtensions(extensionsChoisies);
    auto *pioche = new Pioche(jeu->tuiles);

    Plateau *plateau = Plateau::getInstance();
    cout << "\nDEBUT DU JEU avec ";
    for (int i = 0; i < nbJoueurs; i++) {
        cout << nomsJoueurs[i];
        if (i != nbJoueurs - 1) cout << ", ";
    }
    cout << "\net les extensions : ";
    cout << ParametresPartie::toStringEXTENSIONS(extensionsChoisies) << "\n" << endl;


    while (1) {
        for (string joueur: nomsJoueurs) {
            Tuile *t = pioche->piocher();
            cout << "Joueur" << joueur << " vous avez pioche la " << t->toString() << endl;
            cout << "Position de la tuile :";
            int x, y;
            cin >> x >> y;
            while (plateau->checkerTuile(t, new Coord(x, y))) {
                cout << "Placement non valide, veuillez recommencer" << endl;
                cout << "Position de la tuile :";
                cin >> x >> y;
            }
            plateau->ajouterTuile(t, new Coord(x, y));
            cout << "\naffichage du plateau de jeu : " << endl;
            plateau->afficherConsole();
            cout << "\n" << endl;
        }
    }
    test_ajout_user_Tuiles();
    return 0;
}