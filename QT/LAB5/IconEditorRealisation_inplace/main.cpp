#include "iconeditorrealisation.h"

#include <QApplication>

#include <QImage>
#include <QPainter>
#include <QMainWindow>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IconEditorRealisation* ier = new IconEditorRealisation;
    ier->show();

    return a.exec();
}
