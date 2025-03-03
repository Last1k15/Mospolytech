#ifndef GRID_H
#define GRID_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Grid;
}
QT_END_NAMESPACE

class Grid : public QWidget
{
    Q_OBJECT

public:
    Grid(QWidget *parent = nullptr);
    ~Grid();

private:
    Ui::Grid *ui;
};
#endif // GRID_H
