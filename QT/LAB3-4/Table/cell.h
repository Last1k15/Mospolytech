#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QRegularExpression>

class SpreadSheet;

QT_BEGIN_NAMESPACE
namespace Ui {
class Cell;
}
QT_END_NAMESPACE

class Cell : public QTableWidgetItem
{

public:
    explicit Cell(SpreadSheet* parent = nullptr);
    explicit Cell(QString formula);

    ~Cell();

    Cell* clone() const override;

    void setData(int role, const QVariant& value) override;
    QVariant data(int role) const override;

    inline void setFormula(const QString &formula)
    {
        setData(Qt::EditRole, formula);
    }

    inline QString formula() const
    {
        return data(Qt::EditRole).toString();
    };

    inline void setDirty()
    {
        cacheIsDirty = true;
    };

    inline bool Dirty() const
    {
        return cacheIsDirty;
    };


private:
    Ui::Cell *ui;

    QVariant value() const;

    QVariant evalExpression(const QString &str, int &pos) const;

    QVariant evalTerm(const QString &str, int &pos) const;

    QVariant evalFactor(const QString &str, int &pos) const;

    const QVariant INVALID;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;

    SpreadSheet* parent;
};
#endif // CELL_H
