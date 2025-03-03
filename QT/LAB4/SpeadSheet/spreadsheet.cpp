#include "spreadsheet.h"
#include "cell.h"
// #include "ui_spreadsheet.h"

//////////////////////////////////////////////
/// LIFETIME
///

SpreadSheet::SpreadSheet(QWidget* parent)
    : QTableWidget(parent)
    // , ui(new Ui::SpeadSheet)
{
    // ui->setupUi(this);
    autoRecalc = true;
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this, &SpreadSheet::itemChanged, &SpreadSheet::somethingChanged);
    clear();
}

SpreadSheet::~SpreadSheet()
{
    // delete ui;
}


void SpreadSheet::clear()
{
    setRowCount(0);
    setColumnCount(0);

    setRowCount(ROW_COUNT);
    setColumnCount(COL_COUNT);

    for (int i = 0; i < columnCount(); i++){

        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0, 0);
}

Cell* SpreadSheet::cell(int row, int col) const
{
    return dynamic_cast<Cell*>(item(row, col));
}

QString SpreadSheet::formula(int row, int col) const
{
    Cell* cellPtr = cell(row, col);
    return cellPtr ? cellPtr->formula() : "";
}

void SpreadSheet::setFormula(int row, int col, const QString& formula)
{
    Cell* cellPtr = cell(row, col);
    if (cellPtr)
    {
        cellPtr->setFormula(formula);
        // updateCell(row, col);
    }
    else setItem(row, col, new Cell{formula});

}

QString SpreadSheet::currentLocation() const
{
    return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

void SpreadSheet::somethingChanged()
{
    if (autoRecalc)
        recalculate();

    emit modified();
}
