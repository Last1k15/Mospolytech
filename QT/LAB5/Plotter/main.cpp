#include "plotter.h"

#include <QIODevice>
#include <QFile>
#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QMainWindow>

void readFlightCurves(Plotter *plotter, const QString &fileName)
{
    double  minValue = 0, maxValue = 10;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning
        (
            plotter,
            "Error Occured!",
            "Failed to open file (" + fileName + ')'
        );
        return;
    }

    QVector<QPointF> data[Plotter::CURVE_LIMIT];
    QTextStream txtStream(&file);
    int curCurve = 0;

    while (!txtStream.atEnd())
    {
        QString line = txtStream.readLine();
        QStringList coords = line.split(' ', Qt::SkipEmptyParts);

        for (int ix = 0, iy = 1; iy < coords.count(); ix += 2, iy += 2)
        {
            double x = coords[ix].toDouble();
            double y = coords[iy].toDouble();

            data[curCurve].append(QPointF{x, y});

            if (x < minValue)
                minValue = x;
            else if (x > maxValue)
                maxValue = x;
            if (y < minValue)
                minValue = y;
            else if (y > maxValue)
                maxValue = y;
        }
        curCurve++;
        if (curCurve > Plotter::CURVE_LIMIT) break;
    }

    for (int i = 0; i < Plotter::CURVE_LIMIT; i++)
        if (!data[i].isEmpty())
            plotter->setCurveData(i, data[i]);

    plotter->setPlotSettings(PlotSettings{minValue, maxValue});
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon{R"(:/ico/icons/iconeditor.png)"});

    QMainWindow w;
    w.setWindowTitle(QObject::tr("Plotter test"));

    QWidget mainWidget {&w};
    w.setCentralWidget(&mainWidget);

    QVBoxLayout vl {&mainWidget};
    Plotter plotter;
    vl.addWidget(&plotter);

    readFlightCurves(&plotter, ":/dataRes/data/qt.txt");

    w.show();
    return app.exec();
}
