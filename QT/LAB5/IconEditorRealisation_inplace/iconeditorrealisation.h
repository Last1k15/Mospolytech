#ifndef ICONEDITORREALISATION_H
#define ICONEDITORREALISATION_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QShortcut>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>

class IconEditor;

QT_BEGIN_NAMESPACE
namespace Ui {
class IconEditorRealisation;
}
QT_END_NAMESPACE

class IconEditorRealisation : public QMainWindow
{
    Q_OBJECT

public:
    IconEditorRealisation();
    ~IconEditorRealisation();

public slots:
    void open();
private:
    Ui::IconEditorRealisation *ui;
    IconEditor* iconEditor;
};
#endif // ICONEDITORREALISATION_H
