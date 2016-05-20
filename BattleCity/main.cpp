#include "battlecityview.h"
#include "mainmenu.h"
#include <QDebug>
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    qDebug() << "sdvsd";

    mainMenu menu;

    return a.exec();
}
