#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForLocale(codec);
    setWindowTitle("Привет, Qt!");
    resize(700, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}
