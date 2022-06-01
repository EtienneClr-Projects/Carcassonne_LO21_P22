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

//Attention_grille_20x20 = 400;

namespace Ui {
    class Jeu_Carcassonne;
}

class Jeu_Carcassonne : public QDialog {
Q_OBJECT

public:
    explicit Jeu_Carcassonne(QString *joueurs, int nb_joueurs,
                             bool exPaysans, bool exAbbe, bool exCathAub, bool exRiviere, QWidget *parent = nullptr);

    ~Jeu_Carcassonne();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void test();

    void on_pushButton_5_clicked();

private:
    int position_tour = 0; //1=poser tuile piocher, 2=choix action, 3=score
    int numero_tour = 0;
    int score_suivant = 0;//permet de vérifier que tout les joueurs ont eu leur score d'enregistré

    controleurPartie *cPartie;
    Tuile *tuile_active;

    Ui::Jeu_Carcassonne *ui;
    QTableView *grid;
    QStandardItemModel *modele;

    QPushButton *buttons[400];
    QPixmap *images_grilles[400];
    QLabel *infos_joueurs[4];
    QLabel *infos_scores[4];
    QLabel *infos_ressources[4];
//    Joueur *joueurs_couleur;


    void initialisation(QString *joueurs);

    void debut_tour();

    int getScore(QString infos_scores);

    int getMeeple(QString infos_ressources);

    void setActions();
};

#endif // JEU_CARCASSONNE_H
