#include "spreadsheet.h"
#include "cell.h"
// #include "ui_spreadsheet.h"

//////////////////////////////////////////////
/// LIFETIME
///

SpreadSheet::SpreadSheet(QWidget* parent)
    : QTableWidget(parent)
    // , ui(new Ui::SpreadSheet)
{
    // ui->setupUi(this);
    autoRecalc = true;
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this, &SpreadSheet::itemChanged, this, &SpreadSheet::somethingChanged);
    clear();
}

SpreadSheet::~SpreadSheet()
{
    // delete ui;
}

//////////////////////////////////////////////
/// FILE
///
bool SpreadSheet::readFile(const QString& file)
{
    qDebug() << "readFile(" << file << ')';
    return false;
}

bool SpreadSheet::writeFile(const QString& file)
{
    qDebug() << "writeFile(" << file << ')';
    return false;
}

//////////////////////////////////////////////


//////////////////////////////////////////////
/// UTILITY
///
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


//////////////////////////////////////////////
/// SLOTS
///

void SpreadSheet::recalculate()
{

}

void SpreadSheet::somethingChanged()
{
    if (autoRecalc)
        recalculate();

    emit modified();
}

void SpreadSheet::selectColumn()
{

}

void SpreadSheet::selectRow()
{

};

void SpreadSheet::selectAll()
{

}

void SpreadSheet::cut()
{

}

void SpreadSheet::copy()
{

}

void SpreadSheet::paste()
{

}

void SpreadSheet::del()
{

}

void SpreadSheet::setAutoRecalculate(bool on)
{
    qDebug() << "setAutoRecalculate(" << on << ')';
}

void SpreadSheet::findNext(const QString& str, Qt::CaseSensitivity cs)
{
    qDebug() << "SpreadSheet->findNext(" << str << ", " << cs << ')';
    int row = currentRow();
    int column = currentColumn();

    if (column == COL_COUNT - 1)
    {
        if (row == ROW_COUNT - 1) return;
        column = 0;
        row++;
    }
    else column++;

    while(row < ROW_COUNT)
    {
        while(column < COL_COUNT)
        {
            if (value(row, column).contains(str, cs))
            {
                clearSelection();
                setCurrentCell(row, column);

                return;
            }

            column++;
        }
        column = 0;
        row++;
    }

    QApplication::beep();

}
void SpreadSheet::findPrev(const QString& str, Qt::CaseSensitivity cs)
{
    qDebug() << "SpreadSheet->findPrev(" << str << ", " << cs << ')';

    int row = currentRow();
    int column = currentColumn();

    if (column == 0)
    {
        if (row == 0) return;
        column = COL_COUNT - 1;
        row--;
    }
    else column--;

    while (row >= 0)
    {
        while (column >= 0)
        {
            if (value(row, column).contains(str, cs))
            {
                clearSelection();
                setCurrentCell(row, column);

                return;
            }
            column--;
        }
        column = COL_COUNT - 1;
        row--;
    }

    QApplication::beep();
}

//////////////////////////////////////////////
/// GETTERS
///

Cell* SpreadSheet::cell(int row, int col) const
{
    return dynamic_cast<Cell*>(item(row, col));
}

QString SpreadSheet::value(int row, int col) const
{
    Cell* cellPtr = cell(row, col);
    return cellPtr ? cellPtr->data(Qt::DisplayRole).toString() : "";
}

//////////////////////////////////////////////
/// FORMULA
///

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

QString SpreadSheet::currentFormula() const
{
    return formula(currentRow(), currentColumn());
}

