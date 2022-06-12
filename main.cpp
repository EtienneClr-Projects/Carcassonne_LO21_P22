#include <QApplication>
#include "vuemenu.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    vueMenu vue;
    vue.show();

    return a.exec();
}