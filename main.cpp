/*
#include <iostream>
#include "JeuPiocheEtPlateau/Pioche.h"
#include "JeuPiocheEtPlateau/Jeu.h"
#include "JeuPiocheEtPlateau/Plateau.h"
#include "Gestion/Partie.h"

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
        cout << "vous avez pioche la tuile :" << endl;
        t->afficher();
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
        auto *j = new Joueur(nom, ALL_COULEURS[i]);
        Partie::getInstance()->ajouterJoueur(j);
    }


    cout << "Choisissez les extensions : " << endl;
    cout << "1 : Abbe" << endl;
    cout << "2 : Auberges Cathedrales" << endl;
    cout << "3 : Marchands Batisseurs" << endl;
    cout << "4 : Riviere" << endl;
    cout << "5 : Tous" << endl;
    cout << "6 : Aucune" << endl;

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
            case 6:
                break;
            default:
                cout << "Choix invalide" << endl;
                break;
        }
        if (choix != 6 && choix != 5) {
            cout << "Voulez-vous ajouter une autre extensions ? " << endl;
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

    Partie *partie = Partie::getInstance();
    vector<Joueur *> joueursPartie = partie->getJoueurs();
    while (1) {
        for (Joueur *joueur: joueursPartie) {
            Tuile *t = pioche->piocher();
            cout << "Joueur " << joueur->getNom() << " vous avez pioche la " << endl;
            t->afficher();
            //le joueur peut soit tourner la tuile, soit la poser
            int choixPoserTourner = 0;
            while (choixPoserTourner != 1) {
                cout << "Voulez-vous poser ou tourner la tuile ? " << endl;
                cout << "1 : poser" << endl;
                cout << "2 : tourner" << endl;
                cin >> choixPoserTourner;

                if (choixPoserTourner == 2) {
                    cout << "Entrez le nombre de rotations (sens trigo) : ";
                    int nbRotations;
                    cin >> nbRotations;
                    t->pivoterTuileSensTrigo(nbRotations);
                    cout << "La tuile est maintenant : " << endl;
                    t->afficher();
                }
            }

            int x, y;
            cout << "Position de la tuile (Q pour quitter)" << endl;
            cout << "X : ";
            cin >> x;
            cout << "Y : ";
            cin >> y;
            while (!plateau->checkerTuile(t, new Coord(x, y)) && x != 'Q' && y != 'Q') {
                cout << "Placement non valide, veuillez recommencer" << endl;
                cout << "Position de la tuile (Q pour quitter)" << endl;
                cout << "X : ";
                cin >> x;
                cout << "Y : ";
                cin >> y;
            }
            if (x == 'Q' || y == 'Q') {
                continue;
            }
            plateau->ajouterTuile(t, new Coord(x, y));
            cout << "\naffichage du plateau de jeu : " << endl;
            plateau->afficherConsole();

            //le joueur peut choisir de poser un Meeple sur une case de la tuile posée
            cout << "Voulez-vous poser un meeple sur la tuile ? " << endl;
            cout << "1 : oui" << endl;
            cout << "2 : non" << endl;
            int choixPoserMeeple;
            cin >> choixPoserMeeple;
            while (choixPoserMeeple != 1 && choixPoserMeeple != 2) {
                cout << "Choix invalide :" << endl;
                cin >> choixPoserMeeple;
            }
            if (choixPoserMeeple == 1) {
                //le joueur doit choisir la DIRECTION où il pose son meeple
                cout << "Entrez la direction ou vous voulez poser votre meeple : " << endl;
                cout << "1 : NORD_OUEST\t2 : NORD\t3 : NORD_EST\n"
                     << "4 : EST\t\t5 : MILIEU\t6 : OUEST\n"
                     << "7 : SUD_OUEST\t8 : SUD\t\t9:SUD_EST" << endl;

                int choixDir;
                cin >> choixDir;
                while (choixDir < 1 || choixDir > 9) {
                    cout << "Choix invalide :" << endl;
                    cin >> choixDir;
                }
                DIRECTION dir = DIRECTIONS_ORDERED[choixDir - 1];
                auto *meeple = new Meeple(MEEPLE_TYPE::NORMAL, joueur->getCouleur(),
                                          "");//uniquement pour les tests

                if (plateau->poserMeeple(meeple->getCouleur(), t->getCase(dir), meeple->getType(), partie->meeplesPoses,
                                         partie->meeplesEnReserve)) {
                    cout << "Meeple pose" << endl;
                } else {
                    cout << "Meeple non pose !!" << endl;
                }
                cout << "\naffichage du plateau de jeu : " << endl;
                plateau->afficherConsole();
            }
            plateau->retirerMeeple(partie->meeplesPoses, partie->meeplesEnReserve);

            cout << "Scores Actuels : " << endl;
            for (Joueur *j: joueursPartie) {
                cout << j->getNom() << " \t\t: " << j->getNbPoints() << endl;
            }
            cout << "\n" << endl;
        }
    }

    return 0;
}*/


#include "vue/vuepartie.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    vuePartie w;
    w.show();
    return a.exec();
}