#ifndef GOTOCELL_H
#define GOTOCELL_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class GoToCell;
}
QT_END_NAMESPACE

class GoToCell : public QDialog
{
    Q_OBJECT

public:
    GoToCell(QWidget *parent = nullptr);
    ~GoToCell();
    QString getText() const;

public slots:
    void on_lineEdit_textChanged();

private:
    Ui::GoToCell* ui;
};
#endif // GOTOCELL_H
