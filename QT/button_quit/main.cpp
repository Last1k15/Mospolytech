#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton quit_btn("Quit");
    quit_btn.setFixedSize(100, 50);
    quit_btn.show();
    QObject::connect(&quit_btn, &QPushButton::clicked, [](){QApplication::quit();});
    return a.exec();
}
