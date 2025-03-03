#include "mainwindow.h"
#include <QSlider>
#include <QGridLayout>
#include <QSlider>
#include <QLabel>
#include <QApplication>
#include <QSpinBox>
#include <random>

template <typename T>
T makeRandom(T a, T b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(a, b);
    return dist(gen);
}

void doStuff(QLabel* lb, int b)
{
    lb->setText(QString::number(b));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(1000, 700);

    QWidget* wdgt = new QWidget;
    w.setCentralWidget(wdgt);

    QGridLayout* layout = new QGridLayout(wdgt);

    QSpinBox* sb = new QSpinBox;
    sb->setRange(-5, 5);
    sb->setMinimumSize(100, 100);
    sb->setMaximumSize(300, 300);
    layout->addWidget(sb, 0, 0);

    QLabel* lb1 = new QLabel;
    lb1->setText(QString::number(sb->value()));
    lb1->setMinimumSize(100, 100);
    lb1->setMaximumSize(200, 200);
    layout->addWidget(lb1, 0, 1);

    QObject::connect(sb, &QSpinBox::valueChanged, lb1, [lb1](int value){lb1->setText(QString::number(value));});



    QSlider* sld = new QSlider(Qt::Horizontal);
    layout->addWidget(sld, 1, 0);

    const int sliderMinRange {-300};
    const int sliderMaxRange {300};

    sld->setRange(sliderMinRange, sliderMaxRange);
    sld->setMinimumSize(100, 20);
    sld->setMaximumSize(700, 20);

    QLabel* lb2 = new QLabel;
    lb2->setFixedSize(50, 50);
    layout->addWidget(lb2, 1, 1);

    int guess = makeRandom(sliderMinRange, sliderMaxRange);

    QObject::connect(sld, &QSlider::valueChanged, lb2, [lb2, guess](int value)
    {
        if (value > guess) lb2->setText(QString::fromLocal8Bit("Меньше"));
        else if (value < guess) lb2->setText(QString::fromLocal8Bit("Больше"));
        else lb2->setText(QString::fromLocal8Bit("Найдено!"));
    });

    layout->setAlignment(Qt::AlignCenter);


    w.show();
    return a.exec();
}
