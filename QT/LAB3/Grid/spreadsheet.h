#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>
#include <QTableWidgetSelectionRange>
#include <QApplication>

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
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void sort(const SpreadSheetCompare &compare);


public slots:

    void cut();
    void copy();
    void paste();
    void del();
    void selectRow();
    void selectColumn();
    void selectAll();
    void recalculate();
    void setAutoRecalculate(bool on);
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrev(const QString &str, Qt::CaseSensitivity cs);

signals:

    void modified();

private slots:

    void somethingChanged();

private:

    enum { MagicNumber = 0x7F51C882, ROW_COUNT = 999, COL_COUNT = 26 };

    Cell* cell(int row, int col) const;

    void setFormula(int row, int col, const QString &formula);
    QString formula(int row, int col) const;
    QString value(int row, int col) const;

    bool autoRecalc;
};

class SpreadSheetCompare
{
    bool operator()(const QStringList &row1, const QStringList &row2) const;

    enum { NumKeys = 3 };

    int keys[NumKeys];

    bool ascending[NumKeys];
};

#endif // SPREADSHEET_H
