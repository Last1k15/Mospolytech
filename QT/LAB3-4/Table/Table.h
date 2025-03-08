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
#include <QSettings>
#include <QToolBar>

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

    friend MenuGroup;

public:
    Table(QWidget *parent = nullptr);
    ~Table();

protected:
    void closeEvent(QCloseEvent*);

private:
    enum
    {
        maxRecentFiles = 5,
        toolbarIconSize = 35
    };

    QWidget* mainWidget;
    SpreadSheet* spreadSheet;

    QList<QAction*> recentFilesActions{maxRecentFiles + 1};
    void createRecentFileActions();
    void updateRecentFileActions();

    QToolBar* toolBar;
    void createToolBar();

    QStatusBar* statusBar;
    QLabel* locationLabel;
    QLabel* formulaLabel;
    void createStatusBar();

    MenuGroup* menuGroup;
    void createMenus();
    void createContextMenu();

    QString currentFile;
    QStringList recentFiles;
    QString strippedName(const QString&);

    bool okToContinue();
    bool loadFile(const QString&);
    void openRecentFile();
    bool saveFile(const QString&);
    void setCurrentFile(const QString&);

    void writeSettings();
    void readSettings();

    Ui::Table *ui;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void closeAll();

    void find();
    void goToCell();

    void sort();
    void about();

    void updateStatusBar();
    void spreadSheetModified();

};
#endif // TABLE_H
