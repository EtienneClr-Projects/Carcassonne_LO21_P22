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
        images_grilles[i] = pix;
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




    //débuter le jeu : premier tour
    //initialisation des joueurs et des scores et de la pioche
//    joueurs_couleur = new Joueur[cPartie->getParametresPartie()->getNombreJoueurs()];
    initialisation(joueurs, tj);
    //maintenant le tour peut commencer
    debut_tour();

}

Jeu_Carcassonne::~Jeu_Carcassonne() {

    for (auto &button: buttons) {
        delete button;
    }
    for (int i=0; i<cPartie->getParametresPartie()->getNombreJoueurs(); i++)
    {
        delete liste_joueurs[i];
    }
    delete grid;
    delete modele;
    delete ui;
    delete cPartie;
}


void Jeu_Carcassonne::on_pushButton_2_clicked()//suivant
{//todo enlever

//    if (position_tour == TOUR_SCORE) {
//        if (ui->lineEdit->text() != "") {
//            int nouveau_score = ui->lineEdit->text().toInt();
//
//            nouveau_score = nouveau_score + getScore(infos_scores[i_score_suivant]->text());
//            infos_scores[i_score_suivant]->clear();
//            infos_scores[i_score_suivant]->setText(QString("Score: %1").arg(nouveau_score));
//            infos_scores[i_score_suivant]->update();
//            i_score_suivant = i_score_suivant + 1;
//
//            ui->lineEdit->setText(QString(""));
//
//            if (i_score_suivant == cPartie->getParametresPartie()->getNombreJoueurs()) {
//                //nouveau tour
//                fin_tour();
//
//            } else {
//                ui->label_3->clear();
//                ui->label_3->setText(QString("Joueur %1:").arg(i_score_suivant + 1));
//            }
//        } else {
//            QMessageBox::critical(this, "Erreur", "Veuillez insérer un score.");
//        }
//    }
}

void Jeu_Carcassonne::fin_tour()
{
    //update les meeples retirés des zones
    std::vector<Coord *> coord_tuiles_modifiees = cPartie->getPlateau()->retirerMeeples(
            cPartie->getpartie()->meeplesPoses,
            cPartie->getpartie()->meeplesEnReserve);

    //affichage des points donnés aux joueurs
    for (int i = 0; i < cPartie->getParametresPartie()->getNombreJoueurs(); i++) {
        infos_scores[i]->setText(
                QString("Score: %1").arg(cPartie->getpartie()->getJoueur(ALL_COULEURS[i])->getNbPoints()));
        infos_scores[i]->update();
        cout << "affichage du score du joueur de la couleur : " << ParametresPartie::toStringCOULEUR(ALL_COULEURS[i])
             << " score = " << cPartie->getpartie()->getJoueur(ALL_COULEURS[i])->getNbPoints() << endl;
    }


    int index = 0;
    QIcon icon;
    if (!coord_tuiles_modifiees.empty()) {
        for (auto c: coord_tuiles_modifiees) {
            std::cout << "c la fin" << endl;
            index = (c->x_ - 1) * 20 + (c->y_ - 1);
            cout << "x: " << c->x_ << " y: " << c->y_ << "index: " << index << endl;
            icon.addPixmap(images_grilles[index]);
            buttons[index]->setIcon(icon);
        }
    }

    debut_tour();
}

void Jeu_Carcassonne::fin_jeu()
{
    cout << "\nnous sommes en fin de partie\n";
    //création d'une nouvelle fenêtre avec les résultats
    QString labelText;
    int joueur_victoire = 0;
    int nb =cPartie->getParametresPartie()->getNombreJoueurs();
    int numero_joueur = numero_tour%nb;

    for (int i = 0; i < nb; i++) {
        labelText.clear();
        if (i == (numero_joueur - 1) % nb || ((numero_joueur == 0) && (i == (nb - 1)))) {
            labelText = "<P>";
            labelText.append(infos_joueurs[i]->text().remove("<P><b><i>").remove("</font></i></b></P></br>"));
            labelText.append("</font></P></br>");
            infos_joueurs[i]->clear();
            infos_joueurs[i]->setText(labelText);
            infos_joueurs[i]->update();
        }
    }

    for (int i = 0; i < nb; i++)
    {
        if (getScore(infos_scores[joueur_victoire]->text()) < getScore(infos_scores[i]->text()))
        {
            joueur_victoire = i;
        }
    }
    QMessageBox::information(this, "fin de Partie", infos_joueurs[joueur_victoire]->text().append(" a remporté(e) la partie."));
}

void Jeu_Carcassonne::on_pushButton_clicked()//tourner
{
    if (position_tour == TOUR__POSER_TUILE_PIOCHEE) {
        QPixmap rotated = ui->label_tuile->pixmap().transformed(QTransform().rotate(-90));
        ui->label_tuile->setPixmap(rotated);
        tuile_active->pivoterTuileSensTrigo(1);
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
    index_tuile_active = index;

    if (position_tour == TOUR__POSER_TUILE_PIOCHEE) {
        QPixmap image = ui->label_tuile->pixmap();

        if (cPartie->getPioche()->nbTuilesRestantes != 0) {
            if (cPartie->getPlateau()->checkerTuile(tuile_active, new Coord(index / 20 + 1, index % 20 + 1))) {
                cPartie->getPlateau()->ajouterTuile(tuile_active, new Coord(index / 20 + 1, index % 20 + 1));
                cout << "tuile posee : " << tuile_active->toString() << endl;
                cPartie->getPlateau()->afficherConsole();
                QIcon icon;
                QPixmap result(image.width(), image.height());
                result.fill(Qt::transparent);
                QPainter painter(&result);
                painter.drawPixmap(0, 0, image);
                //meeple = meeple.scaledToHeight(50);
                //painter.drawPixmap(25, 25, meeple);

                images_grilles[index] = result;//image de tuile sans meeples
                icon.addPixmap(result);
                buttons[index]->setIcon(icon);
                //buttonSender->setIcon(icon);

                QPixmap pix(":/Ressources/Blanc/image_blanche.jpg");
                ui->label_tuile->setPixmap(pix);

                //la tuile est posée, le tour peut procéder
                position_tour = TOUR__CHOIX_ACTION;
                //donner le focus au bouton OK
                ui->pushButton_5->setFocus();
            }
            else
            {
                if (liste_joueurs[numero_tour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() == 0) {
                    QMessageBox::warning(this, "Erreur", "Vous ne pouvez pas poser de tuile ici");
                }
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
                position_tour = TOUR__CHOIX_ACTION;
            } else {
                if (liste_joueurs[numero_tour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() == 0) {
                    QMessageBox::warning(this, "Erreur", "Vous ne pouvez pas poser de tuile ici");
                }
            }
        }
    }
    if (position_tour == TOUR__CHOIX_ACTION) {
        if (choix_action == 2 && etape_action == 1) {
            //cPartie->getPlateau()->retirerAbbe()
        }
    }
}


void Jeu_Carcassonne::initialisation(QString *joueurs, const int *tj) {
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


    //progress bar de la pioche
    ui->progressBar->setMaximum((int) cPartie->getJeu()->getNbTuiles());
    ui->progressBar->setMinimum(0);
    infos_joueurs[0]->setStyleSheet("QLabel { color : blue}");
    infos_ressources[0]->setStyleSheet("QLabel { color : blue}");
    infos_scores[0]->setStyleSheet("QLabel { color : blue}");
    infos_joueurs[1]->setStyleSheet("QLabel { color : orange}");
    infos_ressources[1]->setStyleSheet("QLabel { color : orange}");
    infos_scores[1]->setStyleSheet("QLabel { color : orange}");
    infos_joueurs[2]->setStyleSheet("QLabel { color : red}");
    infos_ressources[2]->setStyleSheet("QLabel { color : red}");
    infos_scores[2]->setStyleSheet("QLabel { color : red}");
    infos_joueurs[3]->setStyleSheet("QLabel { color : green}");
    infos_ressources[3]->setStyleSheet("QLabel { color : green}");
    infos_scores[3]->setStyleSheet("QLabel { color : green}");

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

    for (int i = 0; i < nb; i++) {//pour chaque joueur

        liste_joueurs[i] = new Joueur(joueurs[i].toStdString(), ALL_COULEURS[i]);
        liste_joueurs[i]->setType(tj[i]);
        cPartie->getpartie()->ajouterJoueur(liste_joueurs[i]);

        if (liste_joueurs[i]->getType() == 1) {
            infos_joueurs[i]->setText(joueurs[i].append(" (Bot: IARandom)"));
        } else {
            infos_joueurs[i]->setText(joueurs[i]);
        }
        infos_ressources[i]->setText(QString("Meeple: %1").arg(0));
        infos_scores[i]->setText(QString("Score: %1").arg(0));

    }
}

void Jeu_Carcassonne::debut_tour() {
    //donner le focus au bouton Tourner
    cout << "\n début de tour\n";
    ui->pushButton->setFocus();
    numero_tour = numero_tour + 1;
    position_tour = TOUR__POSER_TUILE_PIOCHEE;
    i_score_suivant = 0;
    etape_action = 0;
    choix_action = 0;
    actions_finis = 0;
    meeple_type = MEEPLE_TYPE::NORMAL;//par défaut en cas de manipulation de meeple, le meeple est normal

    updateRessources();

    //piocher une tuile
    tuile_active = cPartie->getPioche()->piocher();

    QString qstring = QString::fromStdString(tuile_active->getCheminImage());
    QPixmap pix(qstring);
    ui->label_tuile->setPixmap(pix);
    ui->progressBar->setValue(cPartie->getPioche()->nbTuilesRestantes);

    //ui->label_3->clear();
    //ui->label_3->setText(QString("Attendez fin tour."));
    //score géré automatiquement
    ui->label_3->clear();
    ui->label_3->setText(QString("Le score est traité\n automatiquement\n à chaque fin de tour."));

    int nb = cPartie->getParametresPartie()->getNombreJoueurs();
    int numero_joueur = numero_tour % nb;

    couleur_actuelle = liste_joueurs[numero_joueur]->getCouleur();

    QString labelText;

    for (int i = 0; i < nb; i++) {
        labelText.clear();

        if (i == numero_joueur) {
            labelText = "<P><b><i>";
            labelText.append(infos_joueurs[i]->text().remove("<P>").remove("</font></P></br>"));
            labelText.append("</font></i></b></P></br>");
            infos_joueurs[i]->clear();
            infos_joueurs[i]->setText(labelText);
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
    if (tuile_active != nullptr) {
        if (liste_joueurs[numero_joueur]->getType() == 1) {
            tourIARandom();
        } else {
            //le joueur humain peut prendre les commandes.
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
            ui->listWidget->addItem("Retirer Meeple dans Abbeye");
            ui->listWidget->addItem("Retirer Meeple dans Jardin");
        }
        if (e == EXTENSION::AUBERGES_CATHEDRALES)
        {
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
            if (m->getCouleur() == liste_joueurs[i]->getCouleur()) {
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

        infos_ressources[i]->clear();
        infos_ressources[i]->setText(text);
        infos_ressources[i]->update();
    }
}

void Jeu_Carcassonne::on_pushButton_5_clicked()//bouton OK
{
    QListWidgetItem *item = ui->listWidget->currentItem();

    if (position_tour == TOUR__CHOIX_ACTION) {
        if (ui->listWidget->selectedItems().empty() || item->text() == QString(aucuneAction)) {
            actions_finis = 1;
        } else if (item->text() == QString(ajoutMeeple) && etape_action == 0) {
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
            choix_action = 1;
            etape_action = 1;
        }
        else if (item->text() == "Ajouter Meeple Abbe" && etape_action == 0)
        {
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
            choix_action = 1;
            etape_action = 1;
            meeple_type=MEEPLE_TYPE::ABBE;
        }
        else if (item->text() == "Retirer Meeple Abbe" && etape_action == 0)
        {
            choix_action = 2;
            etape_action = 1;
            ui->listWidget->clear();
            ui->listWidget->addItem("Sélectionner une tuile.");
        }
        else if (item->text() == "Ajouter Grand Meeple" && etape_action == 0)
        {
            choix_action = 1;
            etape_action = 1;
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
            meeple_type=MEEPLE_TYPE::GRAND_MEEPLE;
        }
        /*else if (item->text() == QString(ajoutMeeple) && etape_action == 0)
        {

        }*/
        else if (!ui->listWidget->selectedItems().empty())
        {
            cout << "\n bouton OK appuyé\n";
             if (etape_action == 1 && choix_action == 1 && tuile_active != nullptr)//ajouter meeple de type meeple_type
                {
                    cout << "\noption 1\n";
                    if (cPartie->getPlateau()->poserMeeple(couleur_actuelle,
                                                           tuile_active->getCase(stringBtnToDir(item->text())),
                                                           meeple_type, cPartie->getpartie()->meeplesPoses,
                                                           cPartie->getpartie()->meeplesEnReserve)) {
                        cout << "\n1\n";
                        QPixmap image = images_grilles[index_tuile_active];
                        cout << "\n1\n";
                        QIcon icon;
                        QPixmap result(image.width(), image.height());
                        result.fill(Qt::transparent);
                        QPainter painter(&result);
                        painter.drawPixmap(0, 0, image);
                        cout << "\n1\n";
                        QPixmap meeple_image;
                        for (auto m: cPartie->getJeu()->meeplesPossibleEnFonctionDesExtensions) {
                            if (m->getCouleur() == couleur_actuelle && m->getType() == meeple_type) {
                                QPixmap meep(QString::fromStdString(m->getCheminImage()));
                                meeple_image = meep;
                                break;
                            }
                        }
                        cout << "\n1\n";
                        meeple_image = meeple_image.scaledToHeight(40);
                        painter.drawPixmap(getXCaseFromDir(item->text()), getYCaseFromDir(item->text()), meeple_image);
                        icon.addPixmap(result);
                        buttons[index_tuile_active]->setIcon(icon);
                        cout << "\n1\n";
                        actions_finis = 1;
                    } else {
                        cout << "\noption 2\n";
                        //si le type du joueur est de type 0, on affiche le message
                        if (liste_joueurs[numero_tour % cPartie->getParametresPartie()->getNombreJoueurs()]->getType() == 0)
                                {
                                    QMessageBox::warning(this, "Erreur", "Vous ne pouvez pas poser de meeple ici");
                                }
                            }
                    }
            cout << "\n fin option 1\n";
        }

        if (actions_finis == 1) {
            //ui->label_3->clear();
            //ui->label_3->setText(QString("Joueur %1:").arg(i_score_suivant + 1));
            //score géré automatiquement
            ui->label_3->clear();
            ui->label_3->setText(QString("Le score est traité\n automatiquement\n à chaque fin de tour."));

            position_tour = TOUR__SCORE;

            updateRessources();
            if (tuile_active==nullptr)
            {
                cout << "\nfin du jeu\n";
                fin_jeu();
            }
            else
            {
                cout << "\n fin de tour\n";
                fin_tour();
            }
        }
    }
}

void Jeu_Carcassonne::tourIARandom()//appelé dans début_tour
{
    int random;
    int nb_choix = 0;
    int count = 0;

    while (position_tour == TOUR__POSER_TUILE_PIOCHEE) {
        std::mt19937 rng(rd());// random-number engine Mersenne-Twister
        std::uniform_int_distribution<int> uni(0, 3);
        random = uni(rng);

        for (int i = 0; i < random + 1; i++) {
            on_pushButton_clicked();
            //cout << "Hello\n";
        }

        for (int i = 0; i < 10; i++) {
            nb_choix = 1 + nb_choix;
            std::mt19937 rng(rd());// random-number engine Mersenne-Twister
            std::uniform_int_distribution<int> uni(0, 399);
            random = uni(rng);
            buttons[random]->clicked();
            //cout << nb_choix << "Kitty\n";
            if (position_tour == TOUR__CHOIX_ACTION) {
                break;
            } else if (nb_choix >= 10000)//pas de choix possibles
            {
                cout << "why\n";
                position_tour = TOUR__CHOIX_ACTION;
                break;
            }
        }
    }
    while (position_tour == TOUR__CHOIX_ACTION) {
        if (nb_choix >= 10000)//pas de choix possibles
        {
            break;
        }
        //cout << "Dog\n";
        count = ui->listWidget->count();
        std::mt19937 rng(rd());// random-number engine Mersenne-Twister
        std::uniform_int_distribution<int> uni(0, count);
        random = uni(rng);
        if (random == count) {
            annuler();
        } else {
            ui->listWidget->setCurrentRow(random);
            cout << "actions finis" << position_tour << "\n";
            on_pushButton_5_clicked();
        }
    }
}

void Jeu_Carcassonne::annuler() {
    if (position_tour == TOUR__CHOIX_ACTION) {
        setActions();
        meeple_type = MEEPLE_TYPE::NORMAL;
        etape_action = 0;
        choix_action = 0;
        actions_finis = 0;
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

