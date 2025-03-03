#include "sort.h"
#include "ui_sort.h"

Sort::Sort(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sort)
{
    ui->setupUi(this);
    ui->SecondaryKeyGroupBox->setVisible(false);
    ui->ThirdKeyGroupBox->setVisible(false);
    setFixedSize(350, 160);

    connect(ui->resizeBtn, &QPushButton::clicked, this, &Sort::on_resizeBtnClicked);
    connect(ui->okBtn, &QPushButton::clicked, this, &Sort::on_okBtnClicked);
}
Sort::~Sort()
{
    delete ui;
}

void Sort::on_okBtnClicked()
{
    QString kc1 {ui->keyCol1_comboBox->currentText()};
    bool order1 {static_cast<bool>(ui->order1_comboBox->currentIndex())};

    if (ui->SecondaryKeyGroupBox->isVisible())
    {
        QString kc2 {ui->keyCol2_comboBox->currentText()};
        QString kc3 {ui->keyCol3_comboBox->currentText()};
        bool order2 {static_cast<bool>(ui->order2_comboBox->currentIndex())};
        bool order3 {static_cast<bool>(ui->order3_comboBox->currentIndex())};

        qDebug() << kc1 << order1 << kc2 << order2 << kc3 << order3;
        emit processSort(kc1, order1, kc2, order2, kc3, order3);
    }

    else {qDebug() << kc1 << order1; emit processSort(kc1, order1);}
}

void Sort::on_resizeBtnClicked()
{

    bool isVisible {ui->SecondaryKeyGroupBox->isVisible()};

    ui->SecondaryKeyGroupBox->setVisible(!isVisible);
    ui->ThirdKeyGroupBox->setVisible(!isVisible);
    ui->resizeBtn->setText(isVisible ? "Больше" : "Меньше");
    setFixedHeight(isVisible ? 160 : 500);
    adjustSize();
}
