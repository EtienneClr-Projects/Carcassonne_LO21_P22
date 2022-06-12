#include "jeu_carcassonne.h"
#include "ui_jeu_carcassonne.h"
#include "JeuPiocheEtPlateau/Pioche.h"

Jeu_Carcassonne::Jeu_Carcassonne(QString *joueurs,
                                 int nb_joueurs, int *tj, bool exPaysans, bool exAbbe, bool exCathAub, bool exRiviere,
                                 QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Jeu_Carcassonne) {

    //création controleur partie (création plateau, paramètresPartie, jeu et pioche)
    cPartie = new controleurPartie(nb_joueurs, exPaysans, exAbbe, exCathAub, exRiviere);

    //création interface, notamment vuePlateau
    ui->setupUi(this);
    this->setWindowTitle(QString("Carcassonne"));
    this->showMaximized();
    //affiche me bouton maximiser
    this->setWindowFlag(Qt::WindowMaximizeButtonHint);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint);

    grid = new QTableView;
    modele = new QStandardItemModel(20, 20, this);
    grid->setModel(modele);
    grid->setFixedHeight(gridWidthHeight * 20 + 27);
    grid->setFixedWidth(gridWidthHeight * 20 + 27);
    for (int i = 0; i < 20; i++) {
        grid->setColumnWidth(i, gridWidthHeight);
        grid->setRowHeight(i, gridWidthHeight);
    }
    ui->scrollArea->setWidget(grid);
    //creation boutons de vuePlateau :
    QIcon icon;
    QPixmap pix(":/Ressources/Blanc/image_blanche.jpg");
    for (int i = 0; i < 400; i++) {
        buttons[i] = new QPushButton;
        imagesGrilles[i] = pix;
        icon.addPixmap(pix);
        buttons[i]->setIcon(icon);
        buttons[i]->setIconSize(QSize(gridWidthHeight - 5, gridWidthHeight - 5));
        buttons[i]->setFixedSize(gridWidthHeight, gridWidthHeight);

        connect(buttons[i], &QPushButton::clicked, this, &Jeu_Carcassonne::test);
        grid->setIndexWidget(grid->model()->index(i % 20, i / 20), buttons[i]);
    }
    //connection du bouton annuler
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Jeu_Carcassonne::annuler);

    ui->scrollArea->verticalScrollBar()->setSliderPosition((gridWidthHeight * 15) / 2);
    ui->scrollArea->horizontalScrollBar()->setSliderPosition((gridWidthHeight * 15) / 2);
    ui->lineEdit->close();
    ui->label_3->close();
    ui->label_2->close();
    ui->pushButton_2->close();


    //débuter le jeu : premier tour
    //initialisation des joueurs et des scores et de la pioche
//    joueurs_couleur = new Joueur[cPartie->getParametresPartie()->getNombreJoueurs()];
    initialisation(joueurs, tj);
    //maintenant le tour peut commencer
    debutTour();

}

Jeu_Carcassonne::~Jeu_Carcassonne() {

    for (auto &button: buttons) {
        delete button;
    }
    for (int i = 0; i < cPartie->getParametresPartie()->getNombreJoueurs(); i++) {
        delete listeJoueurs[i];
    }
    delete grid;
    delete modele;
    delete ui;
    delete cPartie;
}

void Jeu_Carcassonne::finTour() {
    //update les meeples retirés des zones
    std::vector<Coord *> coord_tuiles_modifiees = cPartie->getPlateau()->retirerMeeples(
            cPartie->getpartie()->meeplesPoses,
            cPartie->getpartie()->meeplesEnReserve);

    //affichage des points donnés aux joueurs
    for (int i = 0; i < cPartie->getParametresPartie()->getNombreJoueurs(); i++) {
        infosScores[i]->setText(
                QString("Score: %1").arg(cPartie->getpartie()->getJoueur(ALL_COULEURS[i])->getNbPoints()));
        infosScores[i]->update();
    }


    int index = 0;
    QIcon icon;
    if (!coord_tuiles_modifiees.empty()) {
        for (auto c: coord_tuiles_modifiees) {
            index = (c->x_ - 1) * 20 + (c->y_ - 1);
            icon.addPixmap(imagesGrilles[index]);
            buttons[index]->setIcon(icon);
        }
    }

    debutTour();
}

void Jeu_Carcassonne::finJeu() {
    cPartie->getPlateau()->finDePartie();
    for (int i = 0; i < cPartie->getParametresPartie()->getNombreJoueurs(); i++) {
        infosScores[i]->setText(
                QString("Score: %1").arg(cPartie->getpartie()->getJoueur(ALL_COULEURS[i])->getNbPoints()));
        infosScores[i]->update();
    }

    //création d'une nouvelle fenêtre avec les résultats
    QString labelText;
    int joueur_victoire = 0;
    int nb = cPartie->getParametresPartie()->getNombreJoueurs();
    int numero_joueur = numeroTour % nb;

    for (int i = 0; i < nb; i++) {
        labelText.clear();
        if (i == (numero_joueur - 1) % nb || ((numero_joueur == 0) && (i == (nb - 1)))) {
            labelText = "<P>";
            labelText.append(infosJoueurs[i]->text().remove("<P><b><i>").remove("</font></i></b></P></br>"));
            labelText.append("</font></P></br>");
            infosJoueurs[i]->clear();
            infosJoueurs[i]->setText(labelText);
            infosJoueurs[i]->update();
        }
    }

    for (int i = 0; i < nb; i++) {
        if (getScore(infosScores[joueur_victoire]->text()) < getScore(infosScores[i]->text())) {
            joueur_victoire = i;
        }
    }
    QMessageBox::information(this, "fin de Partie",
                             infosJoueurs[joueur_victoire]->text().append(" a remporté(e) la partie."));
}

void Jeu_Carcassonne::on_pushButton_clicked()//tourner
{
    if (positionTour == TOUR__POSER_TUILE_PIOCHEE) {
        QPixmap rotated = ui->label_tuile->pixmap().transformed(QTransform().rotate(-90));
        ui->label_tuile->setPixmap(rotated);
        tuileActive->pivoterTuileSensTrigo(1);
    }
}

void Jeu_Carcassonne::test() {
    auto *buttonSender = qobject_cast<QPushButton *>(sender());

    int index = 0;
    for (int i = 0; i < 400; i++) {
        if (buttonSender == buttons[i]) {
            index = i;
        }
    }
    indexTuileActive = index;

    if (positionTour == TOUR__POSER_TUILE_PIOCHEE) {
        QPixmap image = ui->label_tuile->pixmap();

        if (cPartie->getPioche()->nbTuilesRestantes != 0) {
            if (cPartie->getPlateau()->checkerTuile(tuileActive, new Coord(index / 20 + 1, index % 20 + 1))) {
                cPartie->getPlateau()->ajouterTuile(tuileActive, new Coord(index / 20 + 1, index % 20 + 1));
                //si la tuile est la tuile source, on donne la dirSource à Plateau
                if (tuileActive->estSource())
                    for (DIRECTION dir: DIRECTIONS_COTE)//on cherche dans quelle direction elle part
                        if (tuileActive->getCase(dir)->getZoneType() == ZONE_TYPE::RIVIERE)
                            cPartie->getPlateau()->setDirSource(dir);

                cPartie->getPlateau()->afficherConsole();
                QIcon icon;
                QPixmap result(image.width(), image.height());
                result.fill(Qt::transparent);
                QPainter painter(&result);
                painter.drawPixmap(0, 0, image);

                imagesGrilles[index] = result;//image de tuile sans meeples
                icon.addPixmap(result);
                buttons[index]->setIcon(icon);
                //buttonSender->setIcon(icon);

                QPixmap pix(":/Ressources/Blanc/image_blanche.jpg");
                ui->label_tuile->setPixmap(pix);

                //la tuile est posée, le tour peut procéder
                positionTour = TOUR__CHOIX_ACTION;
                //donner le focus au bouton OK
                ui->pushButton_5->setFocus();
            } else {
                if (listeJoueurs[numeroTour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() == 0) {
                    QMessageBox::warning(this, "Erreur", "Vous ne pouvez pas poser de tuile ici");
                }
            }

        } else if ((cPartie->getPioche()->nbTuilesRestantes == 0) &&
                   (tuileActive != nullptr)) //dernier élément de la pioche
        {
            if (cPartie->getPlateau()->checkerTuile(tuileActive, new Coord(index / 20 + 1, index % 20 + 1))) {
                cPartie->getPlateau()->ajouterTuile(tuileActive, new Coord(index / 20 + 1, index % 20 + 1));

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

                tuileActive = nullptr;

                //la tuile est posée, le tour peut procéder
                positionTour = TOUR__CHOIX_ACTION;
            } else {
                if (listeJoueurs[numeroTour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() == 0) {
                    QMessageBox::warning(this, "Erreur", "Vous ne pouvez pas poser de tuile ici");
                }
            }
        }
    }
    if (positionTour == TOUR__CHOIX_ACTION) {
        if (choixAction == 2 && etapeAction == 1) {
            //cPartie->getPlateau()->retirerAbbe()
        }
    }
}


void Jeu_Carcassonne::initialisation(QString *joueurs, const int *tj) {
    //creation des labels des informations des joueurs :
    infosJoueurs[0] = ui->label_4;
    infosJoueurs[1] = ui->label_10;
    infosJoueurs[2] = ui->label_13;
    infosJoueurs[3] = ui->label_7;

    infosRessources[0] = ui->label_5;
    infosRessources[1] = ui->label_11;
    infosRessources[2] = ui->label_14;
    infosRessources[3] = ui->label_9;

    infosScores[0] = ui->label_6;
    infosScores[1] = ui->label_12;
    infosScores[2] = ui->label_15;
    infosScores[3] = ui->label_8;


    //progress bar de la pioche
    ui->progressBar->setMaximum((int) cPartie->getJeu()->getNbTuiles());
    ui->progressBar->setMinimum(0);
    infosJoueurs[0]->setStyleSheet("QLabel { color : blue}");
    infosRessources[0]->setStyleSheet("QLabel { color : blue}");
    infosScores[0]->setStyleSheet("QLabel { color : blue}");
    infosJoueurs[1]->setStyleSheet("QLabel { color : orange}");
    infosRessources[1]->setStyleSheet("QLabel { color : orange}");
    infosScores[1]->setStyleSheet("QLabel { color : orange}");
    infosJoueurs[2]->setStyleSheet("QLabel { color : red}");
    infosRessources[2]->setStyleSheet("QLabel { color : red}");
    infosScores[2]->setStyleSheet("QLabel { color : red}");
    infosJoueurs[3]->setStyleSheet("QLabel { color : green}");
    infosRessources[3]->setStyleSheet("QLabel { color : green}");
    infosScores[3]->setStyleSheet("QLabel { color : green}");

    //informations joueurs
    int nb = cPartie->getParametresPartie()->getNombreJoueurs();
    if (nb == 2) {
        infosJoueurs[3]->close();
        infosRessources[3]->close();
        infosScores[3]->close();

        infosJoueurs[2]->close();
        infosRessources[2]->close();
        infosScores[2]->close();

    } else if (nb == 3) {
        infosJoueurs[3]->close();
        infosRessources[3]->close();
        infosScores[3]->close();
    }

    for (int i = 0; i < nb; i++) {//pour chaque joueur

        listeJoueurs[i] = new Joueur(joueurs[i].toStdString(), ALL_COULEURS[i]);
        listeJoueurs[i]->setType(tj[i]);
        cPartie->getpartie()->ajouterJoueur(listeJoueurs[i]);

        if (listeJoueurs[i]->getType() == 1) {
            infosJoueurs[i]->setText(joueurs[i].append(" (Bot: IARandom)"));
        } else {
            infosJoueurs[i]->setText(joueurs[i]);
        }
        infosRessources[i]->setText(QString("Meeple: %1").arg(0));
        infosScores[i]->setText(QString("Score: %1").arg(0));

    }
}

void Jeu_Carcassonne::debutTour() {
    //donner le focus au bouton Tourner
    ui->pushButton->setFocus();
    numeroTour = numeroTour + 1;
    positionTour = TOUR__POSER_TUILE_PIOCHEE;
    i_score_suivant = 0;
    etapeAction = 0;
    choixAction = 0;
    actionsFinies = 0;
    meepleType = MEEPLE_TYPE::NORMAL;//par défaut en cas de manipulation de meeple, le meeple est normal

    updateRessources();

    //piocher une tuile
    tuileActive = cPartie->getPioche()->piocher();

    QString qstring = QString::fromStdString(tuileActive->getCheminImage());
    QPixmap pix(qstring);
    ui->label_tuile->setPixmap(pix);
    ui->progressBar->setValue(cPartie->getPioche()->nbTuilesRestantes);

    //ui->label_3->clear();
    //ui->label_3->setText(QString("Attendez fin tour."));
    //score géré automatiquement
    ui->label_3->clear();
    ui->label_3->setText(QString("Le score est traité\n automatiquement\n à chaque fin de tour."));

    int nb = cPartie->getParametresPartie()->getNombreJoueurs();
    int numero_joueur = numeroTour % nb;

    couleurActuelle = listeJoueurs[numero_joueur]->getCouleur();

    QString labelText;

    for (int i = 0; i < nb; i++) {
        labelText.clear();

        if (i == numero_joueur) {
            labelText = "<P><b><i>";
            labelText.append(infosJoueurs[i]->text().remove("<P>").remove("</font></P></br>"));
            labelText.append("</font></i></b></P></br>");
            infosJoueurs[i]->clear();
            infosJoueurs[i]->setText(labelText);
            infosJoueurs[i]->update();
        }
            //le joueur précédent perd sa police
        else if (i == (numero_joueur - 1) % nb || ((numero_joueur == 0) && (i == (nb - 1)))) {
            labelText = "<P>";
            labelText.append(infosJoueurs[i]->text().remove("<P><b><i>").remove("</font></i></b></P></br>"));
            labelText.append("</font></P></br>");
            infosJoueurs[i]->clear();
            infosJoueurs[i]->setText(labelText);
            infosJoueurs[i]->update();
        }

    }

    setActions();
    if (tuileActive != nullptr) {
        if (listeJoueurs[numero_joueur]->getType() == 1) {
            tourIARandom();
        } else {


            //on colore en vert les tuiles où il est possible de poser la tuile active
            //on parcourt tous les boutons du plateau
            int nbPossibilites = 0;
            for (int iBtn = 0; iBtn < 400; iBtn++) {
                //on essaie les 4 rotations de la tuile
                for (int rotTuile = 0; rotTuile < 4; rotTuile++) {
                    //on regarde si checkerTuile retourne true à la position du bouton
                    if (cPartie->getPlateau()->checkerTuile(tuileActive, new Coord(iBtn / 20 + 1, iBtn % 20 + 1))) {
                        //on colorie le bouton en vert
                        buttons[iBtn]->setStyleSheet("background-color: green");
                        tuileActive->pivoterTuileSensTrigo(4 - rotTuile);
                        nbPossibilites++;
                        break;
                    } else {
                        //on enleve la couleur
                        buttons[iBtn]->setStyleSheet("background-color: white");
                    }
                    tuileActive->pivoterTuileSensTrigo(1);
                }
            }
            if (nbPossibilites == 0) {
                //on affiche un message d'erreur
                QMessageBox::warning(this, "Erreur",
                                     "Aucune position possible pour la tuile active. Recommencez la partie !");
            }
        }
    }
}


int Jeu_Carcassonne::getScore(const QString &_infos_scores) {
    return _infos_scores.split(" ")[1].toInt();
}

void Jeu_Carcassonne::setActions() {
    ui->listWidget->clear();
    ui->listWidget->addItem(aucuneAction);
    ui->listWidget->addItem(ajoutMeeple);
    vector<EXTENSION> extensionsChoisies = cPartie->getParametresPartie()->getExtensionsChoisies();
    for (auto e: extensionsChoisies) {
        if (e == EXTENSION::ABBE) {
            ui->listWidget->addItem("Ajouter Meeple Abbe");
            ui->listWidget->addItem("Retirer Meeple Abbe");
        }
        if (e == EXTENSION::AUBERGES_CATHEDRALES) {
            ui->listWidget->addItem("Ajouter Grand Meeple");
        }
        //rajouter d'autres actions en fonctions d'extensions
    }
}

void Jeu_Carcassonne::updateRessources() {
    int nb = cPartie->getParametresPartie()->getNombreJoueurs();

    //pour chaque extensions
    int normal = 0;
    int abbe = 0;
    int grand = 0;
    QString text;
    QString tmp;
    vector<EXTENSION> extensionsChoisies = cPartie->getParametresPartie()->getExtensionsChoisies();

    for (int i = 0; i < nb; i++) {
        text.clear();
        tmp.clear();
        normal = 0;
        abbe = 0;
        grand = 0;
        for (auto m: cPartie->getpartie()->meeplesEnReserve) {
            if (m->getCouleur() == listeJoueurs[i]->getCouleur()) {
                if (m->getType() == MEEPLE_TYPE::NORMAL) {
                    normal += 1;
                }
                if (m->getType() == MEEPLE_TYPE::ABBE) {
                    abbe += 1;
                }
                if (m->getType() == MEEPLE_TYPE::GRAND_MEEPLE) {
                    grand += 1;
                }
            }

        }
        text.append("m: ");
        tmp = QString::number(normal);
        text.append(tmp);

        for (auto e: extensionsChoisies) {
            if (e == EXTENSION::ABBE) {
                text.append(", A: ");
                tmp = QString::number(abbe);
                text.append(tmp);
            } else if (e == EXTENSION::AUBERGES_CATHEDRALES) {
                text.append(", G: ");
                tmp = QString::number(grand);
                text.append(tmp);
            }
            //rajouter d'autres possibilités de meeple en fonctions d'extensions
        }

        infosRessources[i]->clear();
        infosRessources[i]->setText(text);
        infosRessources[i]->update();
    }
}

void Jeu_Carcassonne::on_pushButton_5_clicked()//bouton OK
{
    QListWidgetItem *item = ui->listWidget->currentItem();

    if (positionTour == TOUR__CHOIX_ACTION) {
        if (ui->listWidget->selectedItems().empty() || item->text() == QString(aucuneAction)) {
            actionsFinies = 1;
        } else if (item->text() == QString(ajoutMeeple) && etapeAction == 0) {
            ui->listWidget->clear();
            ui->listWidget->addItem(ajoutMeepleNO);
            ui->listWidget->addItem(ajoutMeepleN);
            ui->listWidget->addItem(ajoutMeepleNE);
            ui->listWidget->addItem(ajoutMeepleO);
            ui->listWidget->addItem(ajoutMeepleC);
            ui->listWidget->addItem(ajoutMeepleE);
            ui->listWidget->addItem(ajoutMeepleSO);
            ui->listWidget->addItem(ajoutMeepleS);
            ui->listWidget->addItem(ajoutMeepleSE);
            choixAction = 1;
            etapeAction = 1;
        } else if (item->text() == "Ajouter Meeple Abbe" && etapeAction == 0) {
            ui->listWidget->clear();
            ui->listWidget->addItem(ajoutMeepleNO);
            ui->listWidget->addItem(ajoutMeepleN);
            ui->listWidget->addItem(ajoutMeepleNE);
            ui->listWidget->addItem(ajoutMeepleO);
            ui->listWidget->addItem(ajoutMeepleC);
            ui->listWidget->addItem(ajoutMeepleE);
            ui->listWidget->addItem(ajoutMeepleSO);
            ui->listWidget->addItem(ajoutMeepleS);
            ui->listWidget->addItem(ajoutMeepleSE);
            choixAction = 1;
            etapeAction = 1;
            meepleType = MEEPLE_TYPE::ABBE;
        } else if (item->text() == "Retirer Meeple Abbe" && etapeAction == 0) {
            //choixAction = 2;
            //etapeAction = 1;

            ui->listWidget->clear();
            Coord *coord_tmp = cPartie->getPlateau()->retirerAbbe(cPartie->getpartie()->meeplesPoses,
                                                                  cPartie->getpartie()->meeplesEnReserve,
                                                                  couleurActuelle);
            if (coord_tmp == nullptr) {
                if (listeJoueurs[numeroTour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() == 0) {
                    QMessageBox::warning(this, "Erreur", "Vous n'avez pas de Meeple Abbe sur le plateau.'");
                }
            } else {
                QIcon icon;
                int index = (coord_tmp->x_ - 1) * 20 + (coord_tmp->y_ - 1);
                icon.addPixmap(imagesGrilles[index]);
                buttons[index]->setIcon(icon);

                actionsFinies = 1;
            }
            //ui->listWidget->addItem("Sélectionner une tuile.");
        } else if (item->text() == "Ajouter Grand Meeple" && etapeAction == 0) {
            choixAction = 1;
            etapeAction = 1;
            ui->listWidget->clear();
            ui->listWidget->addItem(ajoutMeepleNO);
            ui->listWidget->addItem(ajoutMeepleN);
            ui->listWidget->addItem(ajoutMeepleNE);
            ui->listWidget->addItem(ajoutMeepleO);
            ui->listWidget->addItem(ajoutMeepleC);
            ui->listWidget->addItem(ajoutMeepleE);
            ui->listWidget->addItem(ajoutMeepleSO);
            ui->listWidget->addItem(ajoutMeepleS);
            ui->listWidget->addItem(ajoutMeepleSE);
            meepleType = MEEPLE_TYPE::GRAND_MEEPLE;
        } else if (!ui->listWidget->selectedItems().empty() && etapeAction == 1) {
            if (etapeAction == 1 && choixAction == 1 && tuileActive != nullptr)//ajouter meeple de type meepleType
            {
                if (cPartie->getPlateau()->poserMeeple(couleurActuelle,
                                                       tuileActive->getCase(stringBtnToDir(item->text())),
                                                       meepleType, cPartie->getpartie()->meeplesPoses,
                                                       cPartie->getpartie()->meeplesEnReserve)) {
                    QPixmap image = imagesGrilles[indexTuileActive];
                    QIcon icon;
                    QPixmap result(image.width(), image.height());
                    result.fill(Qt::transparent);
                    QPainter painter(&result);
                    painter.drawPixmap(0, 0, image);
                    QPixmap meeple_image;
                    for (auto m: cPartie->getJeu()->meeplesPossibleEnFonctionDesExtensions) {
                        if (m->getCouleur() == couleurActuelle && m->getType() == meepleType) {
                            QPixmap meep(QString::fromStdString(m->getCheminImage()));
                            meeple_image = meep;
                            break;
                        }
                    }
                    meeple_image = meeple_image.scaledToHeight(40);
                    painter.drawPixmap(getXCaseFromDir(item->text()), getYCaseFromDir(item->text()), meeple_image);
                    icon.addPixmap(result);
                    buttons[indexTuileActive]->setIcon(icon);
                    actionsFinies = 1;
                } else {
                    //si le type du joueur est de type 0, on affiche le message
                    if (listeJoueurs[numeroTour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() ==
                        0) {
                        QMessageBox::warning(this, "Erreur", "Vous ne pouvez pas poser ce meeple ici");
                    }
                }
            }
        }

        if (actionsFinies == 1) {
            //ui->label_3->clear();
            //ui->label_3->setText(QString("Joueur %1:").arg(i_score_suivant + 1));
            //score géré automatiquement
            ui->label_3->clear();
            ui->label_3->setText(QString("Le score est traité\n automatiquement\n à chaque fin de tour."));

            positionTour = TOUR__SCORE;

            updateRessources();
            if (tuileActive == nullptr) {
                finJeu();
            } else {
                finTour();
            }
        }
    }
}

void Jeu_Carcassonne::tourIARandom()//appelé dans début_tour
{
    int random;
    int nb_choix = 0;
    int count = 0;

    while (positionTour == TOUR__POSER_TUILE_PIOCHEE) {
        std::mt19937 rng(rd());// random-number engine Mersenne-Twister
        std::uniform_int_distribution<int> uni(0, 3);
        random = uni(rng);

        for (int i = 0; i < random + 1; i++) {
            on_pushButton_clicked();
        }

        for (int i = 0; i < 10; i++) {
            nb_choix = 1 + nb_choix;
            std::mt19937 rng(rd());// random-number engine Mersenne-Twister
            std::uniform_int_distribution<int> uni(0, 399);
            random = uni(rng);
            buttons[random]->clicked();
            if (positionTour == TOUR__CHOIX_ACTION) {
                break;
            } else if (nb_choix >= 40000)//pas de choix possibles
            {
                positionTour = TOUR__CHOIX_ACTION;
                break;
            }
        }
    }
    while (positionTour == TOUR__CHOIX_ACTION) {
        if (nb_choix >= 40000)//pas de choix possibles
        {
            QMessageBox::warning(this, "Erreur", "Il n'y a plus de possibilités, recommencez la partie !");
            break;
        }
        count = ui->listWidget->count();
        std::mt19937 rng(rd());// random-number engine Mersenne-Twister
        std::uniform_int_distribution<int> uni(0, count);
        random = uni(rng);
        if (random == count) {
            annuler();
        } else {
            ui->listWidget->setCurrentRow(random);
            on_pushButton_5_clicked();
        }
    }
}

void Jeu_Carcassonne::annuler() {
    if (positionTour == TOUR__CHOIX_ACTION) {
        setActions();
        meepleType = MEEPLE_TYPE::NORMAL;
        etapeAction = 0;
        choixAction = 0;
        actionsFinies = 0;
    }
}

DIRECTION Jeu_Carcassonne::stringBtnToDir(const QString &dirStr) {
    if (dirStr == ajoutMeepleN) {
        return DIRECTION::NORD;
    }
    if (dirStr == ajoutMeepleNE) {
        return DIRECTION::NORD_EST;
    }
    if (dirStr == ajoutMeepleE) {
        return DIRECTION::EST;
    }
    if (dirStr == ajoutMeepleSE) {
        return DIRECTION::SUD_EST;
    }
    if (dirStr == ajoutMeepleS) {
        return DIRECTION::SUD;
    }
    if (dirStr == ajoutMeepleSO) {
        return DIRECTION::SUD_OUEST;
    }
    if (dirStr == ajoutMeepleO) {
        return DIRECTION::OUEST;
    }
    if (dirStr == ajoutMeepleNO) {
        return DIRECTION::NORD_OUEST;
    }
    if (dirStr == ajoutMeepleC) {
        return DIRECTION::MILIEU;
    }
    throw CarcassonneException("Direction non reconnue");
}

int Jeu_Carcassonne::getXCaseFromDir(const QString &qString) {
    DIRECTION dir = stringBtnToDir(qString);

    if (dir == DIRECTION::NORD_OUEST || dir == DIRECTION::OUEST || dir == DIRECTION::SUD_OUEST) {
        return 10;
    } else if (dir == DIRECTION::NORD || dir == DIRECTION::MILIEU || dir == DIRECTION::SUD) {
        return 65;
    } else if (dir == DIRECTION::NORD_EST || dir == DIRECTION::EST || dir == DIRECTION::SUD_EST) {
        return 120;
    }
    throw CarcassonneException("Direction non reconnue");
}

int Jeu_Carcassonne::getYCaseFromDir(const QString &qString) {
    DIRECTION dir = stringBtnToDir(qString);

    if (dir == DIRECTION::NORD_OUEST || dir == DIRECTION::NORD || dir == DIRECTION::NORD_EST) {
        return 10;
    } else if (dir == DIRECTION::OUEST || dir == DIRECTION::MILIEU || dir == DIRECTION::EST) {
        return 70;
    } else if (dir == DIRECTION::SUD_OUEST || dir == DIRECTION::SUD || dir == DIRECTION::SUD_EST) {
        return 130;
    }
    throw CarcassonneException("Direction non reconnue");
}

