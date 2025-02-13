#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString{"Привет, Qt!"});
    w.show();

    QLabel label(QString::fromLocal8Bit("Привет, Qt!"), &w);

    return a.exec();
}
