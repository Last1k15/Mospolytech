#include "gotocell.h"
#include "ui_gotocell.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

GoToCell::GoToCell(QWidget *parent)
    :   QDialog(parent),
    ui(new Ui::GoToCell)
{
    ui->setupUi(this);
    QRegularExpression reg {"[A-Za-z][1-9][0-9]{0,2}"};
    QValidator *validator = new QRegularExpressionValidator{reg, this};
    ui->lineEdit->setValidator(validator);
    connect(ui->okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

GoToCell::~GoToCell()
{
    delete ui;
}

void GoToCell::on_lineEdit_textChanged()
{
    ui->okBtn->setEnabled(ui->lineEdit->hasAcceptableInput());
}

QString GoToCell::getText() const
{
    return ui->lineEdit->text().toUpper();
}
