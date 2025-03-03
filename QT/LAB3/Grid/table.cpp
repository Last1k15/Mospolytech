#include "table.h"
#include "spreadsheet.h"
#include "ui_Table.h"
#include "menugroup.h"
#include "finddialog.h"

///////////////////////////////
/// LIFETIME
///
Table::Table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Table)
{
    ///////////////////////////////
    /// SETUP
    ///
    ui->setupUi(this);
    setWindowTitle("Table");
    resize(1000, 1000);

    setToolTipDuration(120000);

    const QIcon windowIcon {":/visual/ico/windowIcon.png"};
    setWindowIcon(windowIcon);
    //////////////////////////////////

    // //////////////////////////////////
    /// MAIN WIDGET
    ///
    mainWidget = new QWidget{this};
    mainWidget->setAutoFillBackground(true);
    setCentralWidget(mainWidget);
    mainWidget->setPalette(palette().dark().color());
    ////////////////////////////////////

    QVBoxLayout* mainLayout = new QVBoxLayout{mainWidget};
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainWidget->setLayout(mainLayout);

    createActions();
    createMenus();

    spreadSheet = new SpreadSheet{mainWidget};
    spreadSheet->setPalette(palette());
    mainLayout->addWidget(spreadSheet);

    createContextMenu();

    setCurrentFile("");
    connect(menuGroup->action_new, &QAction::triggered, this, &Table::newFile);
}

Table::~Table()
{
    delete ui;
}
///////////////////////////////


//////////////////////////////////
/// MENU
///
void Table::createMenus()
{
    menuGroup = new MenuGroup{this};
    menuBar()->setContentsMargins(0,0,0,0);

    connect(menuGroup->action_aboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(menuGroup->action_new, &QAction::triggered, this, &Table::newFile);
    connect(menuGroup->action_open, &QAction::triggered, this, &Table::open);
    connect(menuGroup->action_save, &QAction::triggered, this, &Table::save);
    connect(menuGroup->action_saveAs, &QAction::triggered, this, &Table::saveAs);
    connect(menuGroup->action_exit, &QAction::triggered, this, &Table::close);

    connect(menuGroup->action_cut, &QAction::triggered, this, &Table::cut);
    connect(menuGroup->action_copy, &QAction::triggered, this, &Table::copy);
    connect(menuGroup->action_paste, &QAction::triggered, this, &Table::paste);
    connect(menuGroup->action_delete, &QAction::triggered, this, &Table::del);
    connect(menuGroup->action_find, &QAction::triggered, this, &Table::find);
    connect(menuGroup->action_select, &QAction::triggered, this, &Table::goToCell);
    connect(menuGroup->action_row, &QAction::triggered, this, &Table::goToCell);
    connect(menuGroup->action_col, &QAction::triggered, this, &Table::goToCell);
    connect(menuGroup->action_all, &QAction::triggered, this, &Table::goToCell);

    connect(menuGroup->action_recalc, &QAction::triggered, this, &Table::recalc);
    connect(menuGroup->action_sort, &QAction::triggered, this, &Table::sort);

    connect(menuGroup->action_showGrid, &QAction::triggered, this, &Table::showGrid);
    connect(menuGroup->action_recalc_auto, &QAction::triggered, this, &Table::recalcAuto);
    connect(menuGroup->action_about, &QAction::triggered, this, &Table::about);

    menuFile = new QMenu{this};
    separatorAction = menuFile->addSeparator();
    for (int i = 0; i < maxRecentFiles; i++)
        menuFile->addAction(recentFilesActions[i]);

    menuFile->addSeparator();
}
///////////////////////////////


///////////////////////////////
/// SPREADSHEET
///
void Table::spreadSheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}
///////////////////////////////


///////////////////////////////
/// ACTIONS
///
void Table::createActions()
{
    for (int i = 0; i < maxRecentFiles; i++)
    {
        recentFilesActions[i] = new QAction{this};
        recentFilesActions[i]->setVisible(false);
        connect(recentFilesActions[i], &QAction::triggered, this, &Table::openRecentFile);
    }
}

void Table::updateRecentFileActions()
{
    QMutableStringListIterator fileIter {recentFiles};

    while (fileIter.hasNext())
        if (!QFile::exists(fileIter.next()))
            fileIter.remove();

    for(int j = 0; j < maxRecentFiles; j++)
    {
        if(j < recentFiles.count())
        {

            QString text = tr("&%1 %2").arg(j+1).arg(strippedName(recentFiles[j]));

            recentFilesActions[j]->setText(text);
            recentFilesActions[j]->setData(recentFiles[j]);
            recentFilesActions[j]->setVisible(true);

        }
        else recentFilesActions[j]->setVisible(false);

    }

    separatorAction->setVisible(!recentFiles.isEmpty());
}
///////////////////////////////


///////////////////////////////
/// FILE
///
void Table::setCurrentFile(const QString& file)
{
    currentFile = file;

    setWindowModified(false);

    QString shownName = "Untitled";

    if (!currentFile.isEmpty())
    {
        shownName = strippedName(currentFile);
        recentFiles.removeAll(currentFile);
        recentFiles.prepend(currentFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*]-%2").arg(shownName, tr("SpreadSheet")));
}



bool Table::saveFile(const QString& file)
{
    if (!spreadSheet->writeFile(file))
    {
        statusBar->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(file);
    statusBar->showMessage(tr("File saved"), 2000);
    return true;
}

bool Table::loadFile(const QString& file)
{
    if (spreadSheet->readFile(file))
    {
        statusBar->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(file);
    statusBar->showMessage(tr("File loaded"), 2000);
    return true;
}

void Table::openRecentFile()
{
    if (okToContinue()){

        QAction *action = qobject_cast<QAction *>(sender());

        if (action) loadFile(action->data().toString());
    }
}
///////////////////////////////


///////////////////////////////
/// CONTEXT MENU
///
void Table::createContextMenu()
{
    spreadSheet->addAction(menuGroup->action_cut);
    spreadSheet->addAction(menuGroup->action_copy);
    spreadSheet->addAction(menuGroup->action_paste);
    spreadSheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}
///////////////////////////////


///////////////////////////////
/// STATUS BAR
///
void Table::updateStatusBar()
{
    locationLabel->setText(spreadSheet->currentLocation());
    formulaLabel->setText(spreadSheet->currentFormula());
}

void Table::createStatusBar()
{
    locationLabel = new QLabel{"W999"};
    locationLabel->setAlignment(Qt::AlignCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar = new QStatusBar{this};
    statusBar->addWidget(locationLabel);
    statusBar->addWidget(formulaLabel, 1);

    connect(spreadSheet, &QTableWidget::currentCellChanged, this, &Table::updateStatusBar);
    connect(spreadSheet, &SpreadSheet::modified, this, &Table::spreadSheetModified);

    updateStatusBar();
}
///////////////////////////////


///////////////////////////////
/// UTILITY
///
bool Table::okToContinue()
{
    if (!isWindowModified())
        return true;

    int pressedOption = QMessageBox::warning
    (
        this,
        tr("SpreadSheet"),
        tr("The document has been modified.\nDo you want to save your changes?"),
        {QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel},
        QMessageBox::Yes
    );

    if (pressedOption == QMessageBox::Yes)
        return save();

    if (pressedOption == QMessageBox::Cancel)
        return false;

    return true;
}

QString Table::strippedName(const QString& fullFileName)
{
    return QFileInfo{fullFileName}.fileName();
}
///////////////////////////////


///////////////////////////////
/// FILE SLOTS
///
void Table::newFile()
{
    qDebug() << "New File";
    if (okToContinue())
    {
        spreadSheet->clear();
        setCurrentFile("");
    }
}

void Table::open()
{
    qDebug() << "Open";

    if (!okToContinue()) return;

    QString file = QFileDialog::getOpenFileName
    (
        this,
        tr("Select file to open"),
        ".",
        tr("SpreadSheet files (*.sp)")
    );

    if (!file.isEmpty())
        loadFile(file);
}

bool Table::save()
{
    qDebug() << "save";
    if (currentFile.isEmpty())
        return saveAs();
    else return saveFile(currentFile);

    return true;
}

bool Table::saveAs()
{
    qDebug() << "save As";

    QString file = QFileDialog::getSaveFileName
    (
        this,
        tr("Save SpreadSheet"),
        ".",
        tr("SpreadSheet files (*.sp")
    );

    if (file.isEmpty())
        return false;

    return saveFile(file);
}
///////////////////////////////


///////////////////////////////
/// EDIT SLOTS
///
void Table::cut()
{
    qDebug() << "cut";
}

void Table::copy()
{
    qDebug() << "copied";
}

void Table::paste()
{
    qDebug() << "paste";
}

void Table::del()
{
    qDebug() << "deleted";
}

void Table::find()
{
    qDebug() << "find";
    findDialog = new FindDialog{this};

    connect(findDialog, &FindDialog::findNext, spreadSheet, &SpreadSheet::findNext);
    connect(findDialog, &FindDialog::findPrev, spreadSheet, &SpreadSheet::findPrev);

    findDialog->show();

    findDialog->activateWindow();
}

void Table::goToCell()
{
    qDebug() << "goToCell";
}
///////////////////////////////


///////////////////////////////
/// TOOLS SLOTS
///
void Table::recalc()
{
    qDebug() << "recalc";
}

void Table::sort()
{
    qDebug() << "sort";
}
///////////////////////////////


///////////////////////////////
/// OPTIONS SLOTS
///
void Table::showGrid()
{
    qDebug() << "show Grid";
}

void Table::recalcAuto()
{
    qDebug() << "auto recalc";
}
///////////////////////////////


///////////////////////////////
/// HELP SLOTS
///
void Table::about()
{
    qDebug() << "about";
}
///////////////////////////////


///////////////////////////////
/// OTHER
///
void Table::closeEvent(QCloseEvent* event)
{
    if (okToContinue())
    {
        writeSettings();
        event->accept();
    }
    else event->ignore();
}

void Table::writeSettings()
{
    qDebug() << "writeSettings()";
}
///////////////////////////////
