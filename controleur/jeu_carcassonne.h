#ifndef JEU_CARCASSONNE_H
#define JEU_CARCASSONNE_H

static const char *const ajoutMeepleNO = "Ajouter Meeple Normal nord-ouest";

static const char *const ajoutMeepleN = "Ajouter Meeple Normal nord";

static const char *const ajoutMeepleNE = "Ajouter Meeple Normal nord-est";

static const char *const ajoutMeepleO = "Ajouter Meeple Normal ouest";

static const char *const ajoutMeepleC = "Ajouter Meeple Normal centre";

static const char *const ajoutMeepleE = "Ajouter Meeple Normal est";

static const char *const ajoutMeepleSO = "Ajouter Meeple Normal sud-ouest";

static const char *const ajoutMeepleS = "Ajouter Meeple Normal sud";

static const char *const ajoutMeepleSE = "Ajouter Meeple Normal sud-est";

static const char *const ajoutMeeple = "Ajouter Meeple Normal";

static const char *const aucuneAction = "Aucune action";

static const int gridWidthHeight = 100;

#include "controleurpartie.h"
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


    void initialisation(QString *joueurs, const int *tj);

    void debut_tour();

    void fin_tour();

    int getScore(const QString &_infos_scores);

    int getMeeple(QString infos_ressources); //todo [LOW] @Aness, cette fonction n'est pas implémentée et pas utilisée ?

    void setActions();

    void updateRessources();

    void tourIARandom();

    static DIRECTION stringBtnToDir(const QString &dirStr);

    static int getXCaseFromDir(const QString &qString);

    static int getYCaseFromDir(const QString &qString);
};

#endif // JEU_CARCASSONNE_H
