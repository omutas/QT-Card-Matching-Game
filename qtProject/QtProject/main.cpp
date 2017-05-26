#include <cardmatchgame.h>
#include <QApplication>
#include <stdio.h>
#include <iostream>
#include "thegame.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    cardMatchGame *dialog = new cardMatchGame;
    dialog->setMinimumSize(800,600);
    dialog->show();
    return app.exec();



}
