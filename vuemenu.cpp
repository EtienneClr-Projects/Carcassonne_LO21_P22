#include "vuemenu.h"
#include "ui_vuemenu.h"

vueMenu::vueMenu(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::vueMenu) {
    ui->setupUi(this);
    this->setWindowTitle(QString("Carcassonne"));
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

vueMenu::~vueMenu() {
    delete jeu_carca;
    delete ui;
}

void vueMenu::on_pushButton_clicked() {
    if (nb_joueurs > 1)////////////////////
    {
        if (ui->exAbbe->isChecked()) {
            exAbbe = 1;
        }
        if (ui->exPaysans->isChecked()) {
            exPaysans = 1;
        }
        if (ui->exCathAub->isChecked()) {
            exCathAub = 1;
        }
        if (ui->exRiviere->isChecked()) {
            exRiviere = 1;
        }


        //Compléter paramètres de la partie (et joueurs)



        jeu_carca = new Jeu_Carcassonne(joueurs, nb_joueurs,
                                        exPaysans, exAbbe, exCathAub, exRiviere, this);
        jeu_carca->setModal(true);
        jeu_carca->exec();

        this->close();
    } else {
        QMessageBox::critical(this, "Erreur", "Il vous faut au moins 2 joueurs enregistrés.");
    }

}


void vueMenu::on_pushButton_2_clicked() {
    if (nb_joueurs > 3) {
        QMessageBox::critical(this, "Erreur", "Vous avez déjà 4 joueurs. C'est le maximum!");
    } else if (ui->lineEdit->text() == "") {
        QMessageBox::critical(this, "Erreur", "Veuillez insérer un nom de joueur.");
    } else {
        joueurs[nb_joueurs] = ui->lineEdit->text();
        nb_joueurs++;
        ui->label_2->setText(QString("Joueurs (%1 enregistrés) :").arg(nb_joueurs));
        ui->lineEdit->setText(QString(""));
    }
}

