#include "spreadsheet.h"
#include "cell.h"

//////////////////////////////////////////////
/// LIFETIME
///

SpreadSheet::SpreadSheet(QWidget* parent)
    : QTableWidget(parent)
{
    autoRecalc = true;
    setItemPrototype(new Cell{this});
    setSelectionMode(ContiguousSelection);
    connect(this, &SpreadSheet::itemChanged, this, &SpreadSheet::somethingChanged);
    clear();
}

SpreadSheet::~SpreadSheet()
{

}

//////////////////////////////////////////////
/// FILE
///

bool SpreadSheet::writeFile(const QString& filename)
{
    QFile file{filename};
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning
        (
            this,
            tr("SpreadSheet"),
            tr("Cannot write file %1:\n%2.")
            .arg(file.fileName(), file.errorString())
        );
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_8);
    out << quint32(MagicNumber);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    for(int row = 0; row < ROW_COUNT; ++row)
    {
        for (int column = 0; column < COL_COUNT; ++column)
        {
            QString str = formula(row, column);

            if (!str.isEmpty())
                out << quint16(row) << quint16(column) << str;
        }
    }

    QApplication::restoreOverrideCursor();

    return true;
}

bool SpreadSheet::readFile(const QString& filename)
{
    QFile file{filename};

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning
        (
            this,
            tr("SpreadSheet"),
            tr("Cannot read file %1:\n%2.")
            .arg(file.fileName(), file.errorString())
        );

        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_8);

    quint32 magic;
    in >> magic;

    if (magic != MagicNumber)
    {
        QMessageBox::warning
        (
            this,
            tr("SpreadSheet"),
            tr("The file is not a SpreadSheet file.")
        );

        return false;
    }

    clear();

    quint16 row;
    quint16 column;
    QString str;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    while(!in.atEnd())
    {
        in >> row >> column >> str;
        setFormula(row, column, str);
    }

    QApplication::restoreOverrideCursor();

    return true;
}
//////////////////////////////////////////////


//////////////////////////////////////////////
/// UPDATE SHEET
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

void SpreadSheet::recalculate()
{
    for (int row = 0; row < ROW_COUNT; row++)
        for (int col = 0; col < COL_COUNT; col++)
        {
            Cell* currentCell {cell(row,col)};
            if (!currentCell) continue;

            cell(row, col)->setDirty();
        }
    viewport()->update();
}


//////////////////////////////////////////////
/// SLOTS
///
void SpreadSheet::somethingChanged()
{
    if (autoRecalc)
        recalculate();

    emit modified();
}

void SpreadSheet::selectCurrentColumn()
{
    selectColumn(currentColumn());
}

void SpreadSheet::selectCurrentRow()
{
    selectRow(currentRow());
};

void SpreadSheet::cut()
{
    copy();
    del();
}

void SpreadSheet::copy()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    for (int i = 0; i < range.rowCount(); i++)
    {
        if (i > 0)
            str += "\n";

        for (int j = 0; j < range.columnCount(); j++)
        {
            if (j > 0)
                str += "\t";

            str += formula(range.topRow() + i, range.leftColumn() + j);
        }

    }

    QApplication::clipboard()->setText(str);
}

void SpreadSheet::paste()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');

    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    bool isSingleCell {range.rowCount() * range.columnCount() == 1};
    bool fitsInRange {range.rowCount() == numRows && range.columnCount() == numColumns};

    if (!isSingleCell && !fitsInRange)
    {
        QMessageBox::information
        (
            this,
            tr("SpreadSheet"),
            tr
            (
                "The information cannot be pasted because the copy "
                "and paste areas aren`t the same size."
            )
        );

        return;
    }

    for (int i = 0; i < numRows; i++)
    {
        QStringList columns = rows[i].split('\t');

        for (int j = 0; j < numColumns; ++j)
        {
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;

            bool outOfTable {row >= ROW_COUNT || column >= COL_COUNT};

            if (outOfTable) continue;
            else setFormula(row, column, columns[j]);
        }
    }
}

void SpreadSheet::del()
{
    foreach (QTableWidgetItem *item, selectedItems())
        delete item;
}

void SpreadSheet::setAutoRecalculate(bool state)
{
    if (state) recalculate();
}

void SpreadSheet::findNext(const QString& str, Qt::CaseSensitivity cs)
{
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


//////////////////////////////////////////////


//////////////////////////////////////////////
/// SPREADSHEET COMPARE
///
void SpreadSheet::sort(const SpreadSheetCompare& comp)
{
    QList<QStringList> rows;
    QTableWidgetSelectionRange range = selectedRange();
    int i;

    for (i = 0; i < range.rowCount(); ++i)
    {
        QStringList row;

        for (int j = 0; j < range.columnCount(); j++)
            row.append(formula(range.topRow()+i, range.leftColumn()+j));

        rows.append(row);
    }

    std::stable_sort(rows.begin(), rows.end(), comp);

    for (i = 0; i < range.rowCount(); ++i)
        for (int j = 0; j < range.columnCount(); ++j)
            setFormula(range.topRow() + i, range.leftColumn() + j, rows[i][j]);

    clearSelection();
    somethingChanged();
}
//////////////////////////////////////////////


//////////////////////////////////////////////
/// SPREADSHEET COMPARE
///
bool SpreadSheetCompare::operator()(const QStringList& row1, const QStringList& row2) const
{
    for (int i = 0; i < NumKeys; i++)
    {
        int column = keys[i];

        if (column == -1) break;
        if (row1[column] == row2[column]) break;

        if (ascending[i])
            return row1[column] < row2[column];

        return row1[column] > row2[column];
    }

    return false;
}
//////////////////////////////////////////////


//////////////////////////////////////////////
/// UTILITY
///
QTableWidgetSelectionRange SpreadSheet::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();

    if (ranges.isEmpty())
        return QTableWidgetSelectionRange{};

    return ranges.first();
}

QString SpreadSheet::currentLocation() const
{
    return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

QString SpreadSheet::currentFormula() const
{
    return formula(currentRow(), currentColumn());
}
//////////////////////////////////////////////
