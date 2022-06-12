#include "vuemenu.h"
#include "ui_vuemenu.h"

vueMenu::vueMenu(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::vueMenu) {
    ui->setupUi(this);
    this->setWindowTitle(QString("Carcassonne"));
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    ui->exAbbe->setText("L'Abbé");
}

vueMenu::~vueMenu() {
    delete jeuCarca;
    delete ui;
}

void vueMenu::on_pushButton_clicked() {
    if (nbJoueurs > 1)////////////////////
    {
        if (ui->exAbbe->isChecked()) {
            exAbbe = true;
        }
        if (ui->exPaysans->isChecked()) {
            exPaysans = true;
        }
        if (ui->exCathAub->isChecked()) {
            exCathAub = true;
        }
        if (ui->exRiviere->isChecked()) {
            exRiviere = true;
        }


        jeuCarca = new Jeu_Carcassonne(joueurs, nbJoueurs, typeJoueurs,
                                       exPaysans, exAbbe, exCathAub, exRiviere, this);
        jeuCarca->setModal(true);
        jeuCarca->exec();

        this->close();
    } else {
        QMessageBox::critical(this, "Erreur", "Il vous faut au moins 2 joueurs enregistrés.");
    }

}


void vueMenu::on_pushButton_2_clicked() {
    if (nbJoueurs > 3) {
        QMessageBox::critical(this, "Erreur", "Vous avez déjà 4 joueurs. C'est le maximum!");
    } else if (ui->lineEdit->text() == "") {
        QMessageBox::critical(this, "Erreur", "Veuillez insérer un nom de joueur.");
    } else {
        joueurs[nbJoueurs] = ui->lineEdit->text();
        if (ui->checkBox->isChecked()) {
            typeJoueurs[nbJoueurs] = 1;
            ui->checkBox->setChecked(false);
        } else {
            typeJoueurs[nbJoueurs] = 0;
        }
        nbJoueurs++;
        ui->label_2->setText(QString("Joueurs (%1 enregistrés) :").arg(nbJoueurs));
        ui->lineEdit->setText(QString(""));
    }
}

