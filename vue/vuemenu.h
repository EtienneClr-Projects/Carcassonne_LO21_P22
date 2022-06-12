#ifndef VUEMENU_H
#define VUEMENU_H

#include <QDialog>
#include <QMessageBox>
#include "jeu_carcassonne.h"

namespace Ui {
    class vueMenu;
}

class vueMenu : public QDialog {
Q_OBJECT

public:
    explicit vueMenu(QWidget *parent = nullptr);

    ~vueMenu();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::vueMenu *ui;
    QString joueurs[4];
    int typeJoueurs[4];
    int nbJoueurs = 0;
    bool exPaysans = false;
    bool exAbbe = false;
    bool exCathAub = false;
    bool exRiviere = false;
    Jeu_Carcassonne *jeuCarca;
};

#endif // VUEMENU_H
