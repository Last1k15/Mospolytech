#include "table.h"
#include "spreadsheet.h"
#include "ui_Table.h"
#include "menugroup.h"
#include "finddialog.h"
#include "gotocell.h"
#include "sort.h"

///////////////////////////////
/// LIFETIME
///
Table::Table(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Table)
{
    ui->setupUi(this);

    setWindowTitle("Table");
    setWindowIcon(QIcon{":/visual/ico/windowIcon.png"});
    setToolTipDuration(120000);
    setAttribute(Qt::WA_DeleteOnClose);

    mainWidget = new QWidget{this};
    mainWidget->setAutoFillBackground(true);
    setCentralWidget(mainWidget);
    mainWidget->setPalette(palette().mid().color());

    spreadSheet = new SpreadSheet{mainWidget};
    spreadSheet->setPalette(palette());

    QVBoxLayout* mainLayout = new QVBoxLayout{mainWidget};
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    createMenus();
    createToolBar();
    createStatusBar();
    createContextMenu();
    createRecentFileActions();

    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(statusBar);
    mainLayout->addWidget(spreadSheet);

    setCurrentFile("");
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

    connect(menuGroup->action_new, &QAction::triggered, this, &Table::newFile);
    connect(menuGroup->action_open, &QAction::triggered, this, &Table::open);
    connect(menuGroup->action_save, &QAction::triggered, this, &Table::save);
    connect(menuGroup->action_saveAs, &QAction::triggered, this, &Table::saveAs);

    connect(menuGroup->action_close, &QAction::triggered, this, &Table::closeAll);
    connect(menuGroup->action_exit, &QAction::triggered, this, &Table::close);

    connect(menuGroup->action_cut, &QAction::triggered, spreadSheet, &SpreadSheet::cut);
    connect(menuGroup->action_copy, &QAction::triggered, spreadSheet, &SpreadSheet::copy);
    connect(menuGroup->action_paste, &QAction::triggered, spreadSheet, &SpreadSheet::paste);
    connect(menuGroup->action_delete, &QAction::triggered, spreadSheet, &SpreadSheet::del);
    connect(menuGroup->action_find, &QAction::triggered, this, &Table::find);
    connect(menuGroup->action_select, &QAction::triggered, this, &Table::goToCell);
        connect(menuGroup->action_row, &QAction::triggered, spreadSheet, &SpreadSheet::selectCurrentRow);
        connect(menuGroup->action_col, &QAction::triggered, spreadSheet, &SpreadSheet::selectCurrentColumn);
        connect(menuGroup->action_all, &QAction::triggered, spreadSheet, &QAbstractItemView::selectAll);

    connect(menuGroup->action_recalc, &QAction::triggered, spreadSheet, &SpreadSheet::recalculate);
    connect(menuGroup->action_sort, &QAction::triggered, this, &Table::sort);

    connect(menuGroup->action_showGrid, &QAction::toggled, spreadSheet, &QTableView::setShowGrid);
    connect(menuGroup->action_recalc_auto, &QAction::toggled, spreadSheet, &SpreadSheet::setAutoRecalculate);

    connect(menuGroup->action_about, &QAction::triggered, this, &Table::about);
    connect(menuGroup->action_aboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}
///////////////////////////////


//////////////////////////////////
/// TOOLBAR
///
void Table::createToolBar()
{
    toolBar = new QToolBar{this};

    toolBar->setIconSize(QSize{toolbarIconSize, toolbarIconSize});
    toolBar->setPalette(palette().dark().color());

    toolBar->addAction(menuGroup->action_new);
    toolBar->addAction(menuGroup->action_open);
    toolBar->addAction(menuGroup->action_save);

    toolBar->addSeparator();

    toolBar->addAction(menuGroup->action_cut);
    toolBar->addAction(menuGroup->action_copy);
    toolBar->addAction(menuGroup->action_paste);
    toolBar->addAction(menuGroup->action_delete);
    toolBar->addAction(menuGroup->action_find);
    toolBar->addAction(menuGroup->action_select);

    toolBar->addSeparator();

    toolBar->addAction(menuGroup->action_sort);
}
//////////////////////////////////

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
    bool savedCorrectly = spreadSheet->writeFile(file);

    if (!savedCorrectly)
    {
        statusBar->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(file);
    writeSettings();
    statusBar->showMessage(tr("File saved"), 2000);
    return true;
}

bool Table::loadFile(const QString& file)
{
    bool readCorrectly = spreadSheet->readFile(file);

    if (!readCorrectly)
    {
        statusBar->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(file);
    readSettings();
    statusBar->showMessage(tr("File loaded"), 2000);
    return true;
}

void Table::openRecentFile()
{
    if (!okToContinue()) return;

    QAction *action = qobject_cast<QAction *>(sender());
    for (int i = 0; i < recentFiles.count(); i++)
    if (action) loadFile(action->data().toString());
}
///////////////////////////////


///////////////////////////////
/// SETTINGS
///
void Table::writeSettings()
{
    QSettings settings{"Software Inc.", "SpreadSheet"};

    settings.setValue("geometry", geometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", menuGroup->action_showGrid->isChecked());
    settings.setValue("autoRecalc", menuGroup->action_recalc_auto->isChecked());
}

void Table::readSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");

    // No need if all files inside one window

    // QRect rect = settings.value("geometry", QRect(0, 0, 600, 600)).toRect();
    // move(rect.topLeft());
    // resize(rect.size());

    QStringList prevRecentFiles = settings.value("recentFiles").toStringList();
    for (const QString& prevRecentFile : prevRecentFiles)
        if (prevRecentFile != currentFile && !recentFiles.contains(prevRecentFile))
        {
            recentFiles.append(prevRecentFile);
            if (recentFiles.count() == maxRecentFiles) break;
        }

    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", false).toBool();
    menuGroup->action_showGrid->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", false).toBool();
    menuGroup->action_recalc_auto->setChecked(autoRecalc);
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
    locationLabel = new QLabel{"Z999"};
    locationLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar = new QStatusBar{this};
    statusBar->setPalette(palette());
    statusBar->addWidget(locationLabel);
    statusBar->addWidget(formulaLabel, 1);
    statusBar->setSizeGripEnabled(false);

    connect(spreadSheet, &QTableWidget::currentCellChanged, this, &Table::updateStatusBar);
    connect(spreadSheet, &SpreadSheet::modified, this, &Table::spreadSheetModified);

    updateStatusBar();
}
///////////////////////////////


///////////////////////////////
/// ACTIONS
///
void Table::createRecentFileActions()
{
    for (int i = 0; i <= maxRecentFiles; i++)
    {
        recentFilesActions[i] = new QAction{this};
        recentFilesActions[i]->setIcon(QIcon{":/visual/ico/recentFile.png"});
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

    for (int j = 0; j <= maxRecentFiles; j++)
    {
        if(j < recentFiles.count() && recentFiles[j] != currentFile)
        {
            QString text = tr("&%2").arg(strippedName(recentFiles[j]));

            recentFilesActions[j]->setText(text);
            recentFilesActions[j]->setData(recentFiles[j]);
            recentFilesActions[j]->setVisible(true);
        }
        else recentFilesActions[j]->setVisible(false);
    }
    menuGroup->updateRecentFilesMenu();
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
    Table* table = new Table;
    table->show();
}

void Table::open()
{
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
    if (currentFile.isEmpty())
        return saveAs();
    else return saveFile(currentFile);

    return true;
}

bool Table::saveAs()
{
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

void Table::closeAll()
{
    QApplication::quit();
}
///////////////////////////////


///////////////////////////////
/// EDIT SLOTS
///
void Table::find()
{
    FindDialog* findDialog = new FindDialog{this};

    connect(findDialog, &FindDialog::findNext, spreadSheet, &SpreadSheet::findNext);
    connect(findDialog, &FindDialog::findPrev, spreadSheet, &SpreadSheet::findPrev);

    findDialog->show();
    findDialog->activateWindow();
}

void Table::goToCell()
{
    GoToCell* dialog = new GoToCell{this};
    if(dialog->exec() == QDialog::Accepted)
    {
        QString str = dialog->getText();
        spreadSheet->setCurrentCell(str.mid(1).toInt()-1, str[0].unicode()-'A');
    }
}
///////////////////////////////


///////////////////////////////
/// TOOLS SLOTS
///
void Table::sort()
{
    Sort* sort = new Sort{this};
    QTableWidgetSelectionRange range = spreadSheet->selectedRange();

    QChar first {'A' + range.leftColumn()};
    QChar last {'A' + range.rightColumn()};

    sort->setColumnRange(first, last);

    if (sort->exec() == QDialog::Rejected) return;

    SpreadSheetCompare comp;

    comp.keys[0] = sort->getIndexFirst() - 1;
    comp.keys[1] = sort->getIndexSecond() - 1;
    comp.keys[2] = sort->getIndexThird() - 1;

    comp.ascending[0] = (sort->getFirstOrder() == 0);
    comp.ascending[1] = (sort->getSecondOrder() == 0);
    comp.ascending[2] = (sort->getThirdOrder() == 0);

    spreadSheet->sort(comp);
}
///////////////////////////////


///////////////////////////////
/// HELP SLOTS
///
void Table::about()
{
    QMessageBox::about
    (
        this,
        tr("About SpreadSheet"),
        tr
        (
            "<h2>SpreadSheet 1.1</h2>"
            "<p>Copyright &copy; 2003 Software Inc."
            "<p>Spreadsheet is a small application that "
            "demonstrates <b>QAction</b>, <b>QMainWindow</b>, "
            "<b>QMenuBar</b>, <b>QStatusBar</b>, "
            "<b>QToolBar</b>, and many other Qt classes."
        )
    );
}
///////////////////////////////


///////////////////////////////
/// EVENT OVERLOAD
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
///////////////////////////////
