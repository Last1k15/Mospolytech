#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>


class FindDialog : public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

signals:
    void findNext(const QString& str, Qt::CaseSensitivity cs);
    void findPrev(const QString& str, Qt::CaseSensitivity cs);
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
#endif // FINDDIALOG_H
