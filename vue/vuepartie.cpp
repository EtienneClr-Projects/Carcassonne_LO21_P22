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



/*
void vuePartie::on_pushButton_clicked()
{
    //QPixmap pix("/Ressources/Normal/1P1_C2_P3_C4_F5_C6_P7_C8_P9_.png") ;
    //ui->label_tuile->setPixmap(pix);
    //QString labelText = ui->listWidget->currentItem()->text();
    //ui->label_tuile->setText(labelText);
    //ui->label_tuile->show();

    //QPixmap rotated = ui->label_tuile->pixmap().transformed(QTransform().rotate(90));
    //ui->label_tuile->setPixmap(rotated);
    //ui->label_tuile->show();
    close();

}


void vuePartie::on_pushButton_2_clicked()
{
    close();
}
*/
