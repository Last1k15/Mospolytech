#include <QApplication>
// #include <QMetaType>
#include <QRegularExpression>

int main(int argc, char** argv)
{
    QApplication app{argc, argv};

    static const QRegularExpression cell_regExp {"[A-Za-z][1-9][0-9]{0,2}"};
    QString formula {"A14"};
    QRegularExpressionMatch match = cell_regExp.match(formula);

    qDebug() << "Starting...";

    if (!match.hasMatch()) qDebug() << "No matches";
    else qDebug() << "Matches!" << match.lastCapturedIndex();
    for (int i = 0; i <= match.lastCapturedIndex(); i++)
        qDebug() << match.captured(i);
    return 0;
}
