#include "sort.h"
#include "ui_sort.h"
/////////////////////////////////
/// LIFETME
///
Sort::Sort(QWidget *parent)
    : QDialog(parent), ui(new Ui::Sort)
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
/////////////////////////////////


/////////////////////////////////
/// SLOTS
///
void Sort::on_okBtnClicked()
{
    QDialog::reject();
    if (ui->keyCol1_comboBox->currentText() == "Пусто") QDialog::reject();
    else QDialog::accept();
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
/////////////////////////////////


/////////////////////////////////
/// STARTUP SETTINGS
///
void Sort::setColumnRange(QChar first, QChar last){

    QChar ch = first;

    while (ch <= last)
    {
        QString value = QString(ch);

        ui->keyCol1_comboBox->addItem(value);
        ui->keyCol2_comboBox->addItem(value);
        ui->keyCol3_comboBox->addItem(value);

        ch = QChar{ch.unicode() + 1};
    }

    if (ui->keyCol1_comboBox->count() == 2)
        ui->keyCol1_comboBox->setCurrentIndex(1);
}
/////////////////////////////////


/////////////////////////////////
/// UTILITY
///

int Sort::getIndexFirst() const
{
    return ui->keyCol1_comboBox->currentIndex();
}

int Sort::getFirstOrder() const
{
    return ui->order1_comboBox->currentIndex();
}

int Sort::getIndexSecond() const
{
    return ui->order2_comboBox->currentIndex();
}

int Sort::getSecondOrder() const
{
    return ui->order2_comboBox->currentIndex();
}

int Sort::getIndexThird() const
{
    return ui->order3_comboBox->currentIndex();
}

int Sort::getThirdOrder() const
{
    return ui->order3_comboBox->currentIndex();
}
/////////////////////////////////
