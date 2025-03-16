#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPluginLoader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setFixedSize(900, 900);
    connect(ui->actionOpen_file, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionChange_Color, &QAction::triggered, this, &MainWindow::changeColor);
    connect(ui->actionSave_File, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionReset_Color, &QAction::triggered, this, &MainWindow::resetColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QUrl fileUrl = QFileDialog::getOpenFileUrl
    (
        this,
        "open file..."
    );

    QString path = fileUrl.path().mid(1);

    ui->iconeditor->setIconImage(QImage{path});
}

void MainWindow::changeColor()
{
    QColorDialog colorDialog {this};
    colorDialog.setGeometry(x(),y(),500,500);
    colorDialog.exec();

    QColor userColor = colorDialog.selectedColor();
    ui->iconeditor->setPenColor(userColor);
}

void MainWindow::saveFile()
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    ui->iconeditor->iconImage().save(&buffer, "PNG");

    QFileDialog::saveFileContent
    (
        byteArray,
        "myIcon.png"
    );
}

void MainWindow::resetColor()
{
    ui->iconeditor->setPenColor(QColor{"black"});
}
