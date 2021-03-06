#ifndef JEU_CARCASSONNE_H
#define JEU_CARCASSONNE_H

static const char *const ajoutMeepleNO = "Ajouter Meeple nord-ouest";

static const char *const ajoutMeepleN = "Ajouter Meeple nord";

static const char *const ajoutMeepleNE = "Ajouter Meeple nord-est";

static const char *const ajoutMeepleO = "Ajouter Meeple ouest";

static const char *const ajoutMeepleC = "Ajouter Meeple centre";

static const char *const ajoutMeepleE = "Ajouter Meeple est";

static const char *const ajoutMeepleSO = "Ajouter Meeple sud-ouest";

static const char *const ajoutMeepleS = "Ajouter Meeple sud";

static const char *const ajoutMeepleSE = "Ajouter Meeple sud-est";

static const char *const ajoutMeeple = "Ajouter Meeple";

static const char *const aucuneAction = "Aucune action";

static const int gridWidthHeight = 100;

static const int TOUR__POSER_TUILE_PIOCHEE = 1;//utilisés dans positionTour
static const int TOUR__CHOIX_ACTION = 2;
static const int TOUR__SCORE = 3;


#include "../controleur/controleurpartie.h"
#include "JoueurEtRessources/Joueur.h"

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

    ~Jeu_Carcassonne() override;

private slots:

    void on_pushButton_clicked();

    void annuler();

    void test();

    void on_pushButton_5_clicked();

private:
    std::random_device rd;//pour IA random

    int positionTour = 0; //1=poser tuile piocher, 2=choix action, 3=score
    int numeroTour = -1;
    int i_score_suivant = 0;//permet de vérifier que tous les joueurs ont eu leur score d'enregistré
    //pas oublier de les initialiser dans debutTour
    int etapeAction = 0;
    int choixAction = 0;//1 = ajouter Meeple
    int actionsFinies = 0;//1 si actions en cours

    controleurPartie *cPartie;
    Tuile *tuileActive;
    int indexTuileActive = 0;

    Ui::Jeu_Carcassonne *ui;
    QTableView *grid;
    QStandardItemModel *modele;

    QPushButton *buttons[400];
    QPixmap imagesGrilles[400];
    QLabel *infosJoueurs[4];
    QLabel *infosScores[4];
    QLabel *infosRessources[4];
    Joueur *listeJoueurs[4];//gettype() : 0=humain, 1 = IARAndom

    COULEUR couleurActuelle;
    MEEPLE_TYPE meepleType = MEEPLE_TYPE::NORMAL;


    void initialisation(QString *joueurs, const int *tj);

    void debutTour();

    void finTour();

    void finJeu();

    int getScore(const QString &_infos_scores);
    void setActions();

    void updateRessources();

    void tourIARandom();

    static DIRECTION stringBtnToDir(const QString &dirStr);

    static int getXCaseFromDir(const QString &qString);

    static int getYCaseFromDir(const QString &qString);
};

#endif // JEU_CARCASSONNE_H
