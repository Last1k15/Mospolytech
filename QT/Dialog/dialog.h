#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>


class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void findNext(const QString& str, Qt::CaseSensitivity cs);
    void findPrevious(const QString& str, Qt::CaseSensitivity cs);
public slots:
    void findClicked();
private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;
    QVBoxLayout* leftLayout;
    QHBoxLayout* topLeftLayout;

    QLabel* label;
    QLineEdit* lineEdit;
    QCheckBox* backwardBox;
    QCheckBox* caseBox;
    QPushButton* findBtn;
    QPushButton* closeBtn;
};
#endif // DIALOG_H
