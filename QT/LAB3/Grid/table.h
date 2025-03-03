#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>

class SpreadSheet;
class MenuGroup;
class FindDialog;

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

protected:
    void closeEvent(QCloseEvent*);

private:
    QWidget* mainWidget;

    void createActions();
    void updateRecentFileActions();
    void createMenus();


    SpreadSheet* spreadSheet;
    QStatusBar* statusBar; // possible realization?
    QMenu* menuFile; // possible realization?
    FindDialog* findDialog;
    MenuGroup* menuGroup;

    enum {maxRecentFiles = 5};

    QAction* recentFilesActions[maxRecentFiles];
    QAction* separatorAction;

    QString currentFile;
    QStringList recentFiles;
    QString strippedName(const QString&);

    bool okToContinue();
    bool loadFile(const QString&);
    void openRecentFile();
    bool saveFile(const QString&);
    void setCurrentFile(const QString&);


    void createContextMenu();

    void writeSettings();

    QLabel* locationLabel;
    QLabel* formulaLabel;

    void createStatusBar();

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

    void updateStatusBar();
    void spreadSheetModified();

};
#endif // TABLE_H
