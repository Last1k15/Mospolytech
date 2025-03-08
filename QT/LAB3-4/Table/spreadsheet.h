#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>
#include <QTableWidgetSelectionRange>
#include <QApplication>
#include <algorithm>
#include <QFile>
#include <QMessageBox>
#include <QClipboard>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class SpreadSheet;
}
QT_END_NAMESPACE

class Cell;
class SpreadSheetCompare;

class SpreadSheet : public QTableWidget
{
    Q_OBJECT

public:

    explicit SpreadSheet(QWidget* parent = nullptr);
    ~SpreadSheet();

    bool autoRecalculate() const {return autoRecalc;}

    QString currentLocation() const;
    QString currentFormula() const;

    QTableWidgetSelectionRange selectedRange() const;

    void clear();
    bool readFile(const QString& fileName);
    bool writeFile(const QString& fileName);
    void sort(const SpreadSheetCompare& compare);
    QString value(int row, int col) const;


public slots:
    void cut();
    void copy();
    void paste();
    void del();
    void selectCurrentRow();
    void selectCurrentColumn();
    void recalculate();
    void setAutoRecalculate(bool on);
    void findNext(const QString& str, Qt::CaseSensitivity cs);
    void findPrev(const QString& str, Qt::CaseSensitivity cs);

signals:

    void modified();

private slots:
    void somethingChanged();

private:

    enum { MagicNumber = 0x7F51C882, ROW_COUNT = 999, COL_COUNT = 26 };

    Cell* cell(int row, int col) const;

    void setFormula(int row, int col, const QString &formula);
    QString formula(int row, int col) const;

    bool autoRecalc;

    inline void moveRight(int& row, int& column)
    {
        if (column == COL_COUNT - 1)
        {
            if (row == ROW_COUNT - 1) return;
            column = 0;
            row++;
        }
        else column++;
    }

    inline void moveLeft(int& row, int& column)
    {
        if (column == 0)
        {
            if (row == 0) return;
            column = COL_COUNT - 1;
            row--;
        }
        else column--;
    }

    inline void moveUp(int& row)
    {
        if (row == 0) return;
        row--;
    }

    inline void moveDown(int& row)
    {
        if (row == ROW_COUNT - 1) return;
        else row++;
    }
};

class SpreadSheetCompare
{
    public:
    bool operator()(const QStringList &row1, const QStringList &row2) const;

    enum { NumKeys = 3 };

    int keys[NumKeys];

    bool ascending[NumKeys];
};

#endif // SPREADSHEET_H
