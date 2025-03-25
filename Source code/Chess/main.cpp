#include "Game.h"
#include "lobby.h"
#include "PromotionDialog.h"
#include <QApplication>
#include <QtMultimedia>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    PromotionDialog a1;
//    a1.show();
    Lobby w;
    w.show();
    return a.exec();
}
