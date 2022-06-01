#include "jeu_carcassonne.h"
#include "ui_jeu_carcassonne.h"
#include "modele/JeuPiocheEtPlateau/Pioche.h"

Jeu_Carcassonne::Jeu_Carcassonne(QString *joueurs,
                                 int nb_joueurs, bool exPaysans, bool exAbbe, bool exCathAub, bool exRiviere,
                                 QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Jeu_Carcassonne) {

    //création controleur partie (création plateau, paramètresPartie, jeu et pioche)
    cPartie = new controleurPartie(nb_joueurs, exPaysans, exAbbe, exCathAub, exRiviere);

    //création interface, notamment vuePlateau
    ui->setupUi(this);
    this->setWindowTitle(QString("Carcassonne"));
    this->setFixedSize(1920 / 1.5, 900 / 1.5);
    grid = new QTableView;
    modele = new QStandardItemModel(20, 20, this);
    grid->setModel(modele);
    grid->setFixedHeight(175 * 20 + 27);
    grid->setFixedWidth(175 * 20 + 27);
    for (int i = 0; i < 20; i++) {
        grid->setColumnWidth(i, 175);
        grid->setRowHeight(i, 175);
    }
    ui->scrollArea->setWidget(grid);
    //creation boutons de vuePlateau :
    QIcon icon;
    for (int i = 0; i < 400; i++) {
        buttons[i] = new QPushButton;
        images_grilles[i] = new QPixmap(":/Ressources/Blanc/image_blanche.jpg");
        icon.addPixmap(*images_grilles[i]);
        buttons[i]->setIcon(icon);
        buttons[i]->setIconSize(QSize(170, 170));
        buttons[i]->setFixedSize(175, 175);
        connect(buttons[i], &QPushButton::clicked, this, &Jeu_Carcassonne::test);
        grid->setIndexWidget(grid->model()->index(i % 20, i / 20), buttons[i]);
    }
    ui->scrollArea->verticalScrollBar()->setSliderPosition((175 * 15) / 2);
    ui->scrollArea->horizontalScrollBar()->setSliderPosition((175 * 15) / 2);
    //creation des labels des informations des joueurs :
    infos_joueurs[0] = ui->label_4;
    infos_joueurs[1] = ui->label_10;
    infos_joueurs[2] = ui->label_13;
    infos_joueurs[3] = ui->label_7;

    infos_ressources[0] = ui->label_5;
    infos_ressources[1] = ui->label_11;
    infos_ressources[2] = ui->label_14;
    infos_ressources[3] = ui->label_9;

    infos_scores[0] = ui->label_6;
    infos_scores[1] = ui->label_12;
    infos_scores[2] = ui->label_15;
    infos_scores[3] = ui->label_8;



    //débuter le jeu : premier tour
    //initialisation des joueurs et des scores et de la pioche
//    joueurs_couleur = new Joueur[cPartie->getParametresPartie()->getNombreJoueurs()];
    initialisation(joueurs);

    //maintenant le tour peut commencer
    debut_tour();

}

Jeu_Carcassonne::~Jeu_Carcassonne() {
    delete cPartie;


    for (int i = 0; i < 400; i++) {
        delete buttons[i];
        delete images_grilles[i];
    }
    delete grid;
//    delete joueurs_couleur;
    delete modele;
    delete ui;
}


void Jeu_Carcassonne::on_pushButton_2_clicked()//suivant
{
    if (position_tour == 3) {
        if (ui->lineEdit->text() != "") {
            int nouveau_score = ui->lineEdit->text().toInt();

            nouveau_score = nouveau_score + getScore(infos_scores[score_suivant]->text());
            infos_scores[score_suivant]->clear();
            infos_scores[score_suivant]->setText(QString("Score: %1").arg(nouveau_score));
            infos_scores[score_suivant]->update();
            score_suivant = score_suivant + 1;

            ui->lineEdit->setText(QString(""));

            if (score_suivant == cPartie->getParametresPartie()->getNombreJoueurs()) {
                //nouveau tour
                numero_tour = numero_tour + 1;
                debut_tour();
            } else {
                ui->label_3->clear();
                ui->label_3->setText(QString("Joueur %1:").arg(score_suivant + 1));
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Veuillez insérer un score.");
        }
    }
}

void Jeu_Carcassonne::on_pushButton_clicked()//tourner
{
    if (position_tour == 1) {
        QPixmap rotated = ui->label_tuile->pixmap().transformed(QTransform().rotate(-90));
        ui->label_tuile->setPixmap(rotated);
        tuile_active->pivoterTuileSensTrigo(1);
    }

}

void Jeu_Carcassonne::test() {
    if (position_tour == 1) {
        std::cout << "\n\n\n" << cPartie->getPioche()->nbTuilesRestantes << "\n\n\n";

        QPushButton *buttonSender = qobject_cast<QPushButton *>(sender());

        int index = 0;
        for (int i = 0; i < 400; i++) {
            if (buttonSender == buttons[i]) {
                index = i;
            }
        }


        QPixmap image = ui->label_tuile->pixmap();

        if (cPartie->getPioche()->nbTuilesRestantes != 0) {
            if (cPartie->getPlateau()->checkerTuile(tuile_active, new Coord(index / 20 + 1, index % 20 + 1))) {
                cPartie->getPlateau()->ajouterTuile(tuile_active, new Coord(index / 20 + 1, index % 20 + 1));

                QIcon icon;
                QPixmap result(image.width(), image.height());
                result.fill(Qt::transparent);
                QPainter painter(&result);
                painter.drawPixmap(0, 0, image);
                //meeple = meeple.scaledToHeight(50);
                //painter.drawPixmap(25, 25, meeple);
                icon.addPixmap(result);
                buttonSender->setIcon(icon);


                QPixmap pix(":/Ressources/Blanc/image_blanche.jpg");
                ui->label_tuile->setPixmap(pix);

                //la tuile est posée, le tour peut procéder
                position_tour = 2;
            }
        } else if ((cPartie->getPioche()->nbTuilesRestantes == 0) &&
                   (tuile_active != nullptr)) //dernier élément de la pioche
        {
            if (cPartie->getPlateau()->checkerTuile(tuile_active, new Coord(index / 20 + 1, index % 20 + 1))) {
                cPartie->getPlateau()->ajouterTuile(tuile_active, new Coord(index / 20 + 1, index % 20 + 1));

                QIcon icon;
                QPixmap result(image.width(), image.height());
                result.fill(Qt::transparent);
                QPainter painter(&result);
                painter.drawPixmap(0, 0, image);
                //meeple = meeple.scaledToHeight(50);
                //painter.drawPixmap(25, 25, meeple);
                icon.addPixmap(result);
                buttonSender->setIcon(icon);

                QPixmap pix(":/Ressources_Interface/Blanc/image_blanche.jpg");
                ui->label_tuile->setPixmap(pix);

                tuile_active = nullptr;

                //la tuile est posée, le tour peut procéder
                position_tour = 2;
            }
        }
    }
    /*

    QPixmap meeple(":/Ressources_Interface/Meeple/1GJ.png");
    //ui->label_tuile->setPixmap(meeple);
    */


    /*
    *images_grilles[index] = image;
    */

    //pioche avec couleur blanche;
}

void Jeu_Carcassonne::initialisation(QString *joueurs) {
    //progress bar de la pioche
    ui->progressBar->setMaximum(cPartie->getJeu()->getNbTuiles());
    ui->progressBar->setMinimum(0);

    //informations joueurs
    int nb = cPartie->getParametresPartie()->getNombreJoueurs();
    if (nb == 2) {
        infos_joueurs[3]->close();
        infos_ressources[3]->close();
        infos_scores[3]->close();

        infos_joueurs[2]->close();
        infos_ressources[2]->close();
        infos_scores[2]->close();

    } else if (nb == 3) {
        infos_joueurs[3]->close();
        infos_ressources[3]->close();
        infos_scores[3]->close();
    }

    for (int i = 0; i < nb; i++) {
        infos_joueurs[i]->setText(joueurs[i]);
        infos_ressources[i]->setText(QString("Meeple: %1").arg(0));
        infos_scores[i]->setText(QString("Score: %1").arg(0));
    }
}

void Jeu_Carcassonne::debut_tour() {
    position_tour = 1;
    score_suivant = 0;

    //piocher une tuile
    tuile_active = cPartie->getPioche()->piocher();
    QString qstring = QString::fromStdString(tuile_active->getCheminImage());
    QPixmap pix(qstring);
    ui->label_tuile->setPixmap(pix);
    ui->progressBar->setValue(cPartie->getPioche()->nbTuilesRestantes);

    ui->label_3->clear();
    ui->label_3->setText(QString("Attendez fin tour."));

    int nb = cPartie->getParametresPartie()->getNombreJoueurs();
    int numero_joueur = numero_tour % nb;
    QString labelText;

    for (int i = 0; i < nb; i++) {
        labelText.clear();

        if (i == numero_joueur) {
            labelText = "<P><b><i>";
            labelText.append(infos_joueurs[i]->text().remove("<P>").remove("</font></P></br>"));
            labelText.append("</font></i></b></P></br>");
            infos_joueurs[i]->clear();
            infos_joueurs[i]->setText(labelText);
            cout << labelText.toLocal8Bit().constData() << "\n\n vainqueur\n\n";
            infos_joueurs[i]->update();
        }
            //le joueur précédent perd sa police
        else if (i == (numero_joueur - 1) % nb || ((numero_joueur == 0) && (i == (nb - 1)))) {
            labelText = "<P>";
            labelText.append(infos_joueurs[i]->text().remove("<P><b><i>").remove("</font></i></b></P></br>"));
            labelText.append("</font></P></br>");
            infos_joueurs[i]->clear();
            infos_joueurs[i]->setText(labelText);
            infos_joueurs[i]->update();
        }

    }

    setActions();
}

int Jeu_Carcassonne::getScore(QString infos_scores) {
    return infos_scores.split(" ")[1].toInt();
}

void Jeu_Carcassonne::setActions() {
    ui->listWidget->clear();
    ui->listWidget->addItem("Ajouter Meeple Normal");
    vector<EXTENSION> extensionsChoisies = cPartie->getParametresPartie()->getExtensionsChoisies();
    for (auto e: extensionsChoisies) {
        if (e == EXTENSION::ABBE) {
            ui->listWidget->addItem("Ajouter Meeple Abbe");
            ui->listWidget->addItem("Retirer Meeple Abbe");
            ui->listWidget->addItem("Retirer Meeple normal");
        }
    }
}

void Jeu_Carcassonne::on_pushButton_5_clicked()//bouton OK
{
    if (position_tour == 2) {
        ui->label_3->clear();
        ui->label_3->setText(QString("Joueur %1:").arg(score_suivant + 1));
        position_tour = 3;

    }
}









