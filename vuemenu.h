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
    int nb_joueurs = 0;
    bool exPaysans = 0;
    bool exAbbe = 0;
    bool exCathAub = 0;
    bool exRiviere = 0;
    Jeu_Carcassonne *jeu_carca;
};

#endif // VUEMENU_H
