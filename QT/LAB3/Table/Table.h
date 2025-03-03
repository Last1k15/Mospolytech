#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SpreadSheet;
class MenuGroup;

QT_BEGIN_NAMESPACE
namespace Ui {
class Table;
}
QT_END_NAMESPACE

class Table : public QMainWindow
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();
private:
    QWidget* mainWidget;
    MenuGroup* menuGroup;
    SpreadSheet* spreadSheet;

    Ui::Table *ui;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();

    void cut();
    void copy();
    void paste();
    void del();
    void find();
    void goToCell();

    void recalc();
    void sort();

    void showGrid();
    void recalcAuto();

    void about();




};
#endif // TABLE_H
