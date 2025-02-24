#ifndef SORT_H
#define SORT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Sort;
}
QT_END_NAMESPACE

class Sort : public QDialog
{
    Q_OBJECT

public:
    Sort(QWidget *parent = nullptr);
    ~Sort();
signals:
    void processSort(const QString keyCol1, const bool isDescend1, const QString keyCol2 = "", const bool isDescend2 = false, const QString keyCol3 = "", const bool isDescend3 = false);

public slots:
    void on_resizeBtnClicked();
    void on_okBtnClicked();

private:
    Ui::Sort *ui;
};
#endif // SORT_H
