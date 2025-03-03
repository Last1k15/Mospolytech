#include "Table.h"
#include "ui_Table.h"
#include "menugroup.h"

Table::Table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Table)
{
///////////////////////////////
/// MAIN
///
    ui->setupUi(this);
    setWindowTitle("Table");
    resize(1000, 1000);

    setToolTipDuration(120000);

    const QIcon windowIcon {":/img/ico/windowIcon.png"};

    setWindowIcon(windowIcon);

// ///////////////////////////////
/// MAIN WIDGET
///
    mainWidget = new QWidget{this};
    mainWidget->setAutoFillBackground(true);
    mainWidget->setPalette(palette().dark().color());
    setCentralWidget(mainWidget);

///////////////////////////////
/// MENU
///
    MenuGroup* menu = new MenuGroup{this};
    connect(menu->action_aboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(menu->action_new, &QAction::triggered, this, &Table::newFile);
    connect(menu->action_open, &QAction::triggered, this, &Table::open);
    connect(menu->action_save, &QAction::triggered, this, &Table::save);
    connect(menu->action_saveAs, &QAction::triggered, this, &Table::saveAs);
    connect(menu->action_exit, &QAction::triggered, this, &Table::close);

    connect(menu->action_cut, &QAction::triggered, this, &Table::cut);
    connect(menu->action_copy, &QAction::triggered, this, &Table::copy);
    connect(menu->action_paste, &QAction::triggered, this, &Table::paste);
    connect(menu->action_delete, &QAction::triggered, this, &Table::del);
    connect(menu->action_find, &QAction::triggered, this, &Table::find);
    connect(menu->action_select, &QAction::triggered, this, &Table::goToCell);
    connect(menu->action_row, &QAction::triggered, this, &Table::goToCell);
    connect(menu->action_col, &QAction::triggered, this, &Table::goToCell);
    connect(menu->action_all, &QAction::triggered, this, &Table::goToCell);

    connect(menu->action_recalc, &QAction::triggered, this, &Table::recalc);
    connect(menu->action_sort, &QAction::triggered, this, &Table::sort);

    connect(menu->action_showGrid, &QAction::triggered, this, &Table::showGrid);
    connect(menu->action_recalc_auto, &QAction::triggered, this, &Table::recalcAuto);
    connect(menu->action_about, &QAction::triggered, this, &Table::about);
}


///////////////////////////////
/// FILE
///
void Table::newFile()
{
    qDebug() << "New File";
}

void Table::open()
{
    qDebug() << "Open";
}

bool Table::save()
{
    qDebug() << "save";
    return true;
}

bool Table::saveAs()
{
    qDebug() << "save As";
    return true;
}

///////////////////////////////
/// EDIT
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
}

void Table::goToCell()
{
    qDebug() << "goToCell";
}

///////////////////////////////
/// TOOLS
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
/// OPTIONS
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
/// HELP
///

void Table::about()
{
    qDebug() << "about";
}

Table::~Table()
{
    delete ui;
}
