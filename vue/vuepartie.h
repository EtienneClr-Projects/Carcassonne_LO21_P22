#ifndef VUEPARTIE_H
#define VUEPARTIE_H

#include <QMainWindow>
#include <QPixmap>
#include <QTransform>
#include "vuemenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class vuePartie; }
QT_END_NAMESPACE

class vuePartie : public QMainWindow {
Q_OBJECT

public:
    vuePartie(QWidget *parent = nullptr);

    ~vuePartie();

private slots:

private:
    Ui::vuePartie *ui;
    vueMenu *menu;
};

#endif // VUEPARTIE_H
