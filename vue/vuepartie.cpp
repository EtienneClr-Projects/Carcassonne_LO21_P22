#include "vuepartie.h"
#include "ui_vuepartie.h"


vuePartie::vuePartie(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::vuePartie) {
    QApplication::setWindowIcon(QIcon(":/Ressources/Normal/Meeples/7NB.png"));

    menu = new vueMenu(this);
    menu->setModal(true);
    menu->exec();

    ui->setupUi(this);


    close();

}

vuePartie::~vuePartie() {
    delete ui;
}
