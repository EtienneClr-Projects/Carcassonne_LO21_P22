#ifndef JEU_CARCASSONNE_H
#define JEU_CARCASSONNE_H

#include "controleurpartie.h"
#include "modele/JoueurEtRessources/Joueur.h"

#include <QDialog>
#include <QPixmap>
#include <QTransform>
#include <QSize>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QTableView>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <random>

//Attention_grille_20x20 = 400;

namespace Ui {
    class Jeu_Carcassonne;
}

class Jeu_Carcassonne : public QDialog {
Q_OBJECT

public:
    explicit Jeu_Carcassonne(QString *joueurs, int nb_joueurs, int* tj,
                             bool exPaysans, bool exAbbe, bool exCathAub, bool exRiviere, QWidget *parent = nullptr);

    ~Jeu_Carcassonne();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void annuler();

    void test();

    void on_pushButton_5_clicked();

private:
    std::random_device rd;//pour IA random

    int position_tour = 0; //1=poser tuile piocher, 2=choix action, 3=score
    int numero_tour = -1;
    int score_suivant = 0;//permet de vérifier que tout les joueurs ont eu leur score d'enregistré
    //pas oublier de les initialiser dans debut_tour
    int etape_action = 0;
    int choix_action = 0;//1 = ajouter Meeple
    int actions_finis = 0;//1 si actions en cours

    controleurPartie *cPartie;
    Tuile *tuile_active;
    int index_tuile_active=0;

    Ui::Jeu_Carcassonne *ui;
    QTableView *grid;
    QStandardItemModel *modele;

    QPushButton *buttons[400];
    QPixmap images_grilles[400];
    QLabel *infos_joueurs[4];
    QLabel *infos_scores[4];
    QLabel *infos_ressources[4];
    int types_joueurs[4];//0=humain, 1 = IARAndom
    COULEUR couleurs_joueurs[4] = {COULEUR::BLEU, COULEUR::JAUNE, COULEUR::ROUGE, COULEUR::VERT};
    COULEUR couleur_actuelle;


    void initialisation(QString *joueurs, int* tj);

    void debut_tour();

    void fin_tour();

    int getScore(QString infos_scores);

    int getMeeple(QString infos_ressources);

    void setActions();

    void updateRessources();

    void tourIARandom();
};

#endif // JEU_CARCASSONNE_H
