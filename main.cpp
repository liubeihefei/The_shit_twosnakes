#include "two_players.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    two_players w;
    w.show();
    return a.exec();
}
