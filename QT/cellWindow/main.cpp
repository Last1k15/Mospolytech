#include "goToCell.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GoToCell w;
    w.show();
    return a.exec();
}
