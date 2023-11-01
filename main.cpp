#include "SpicyInvaders.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpicyInvaders game;
    game.show();
    game.setWindowTitle("SpicyInvaders");
    return a.exec();
}
