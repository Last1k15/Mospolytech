#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui {
class Cell;
}
QT_END_NAMESPACE

class Cell : public QTableWidgetItem
{

public:
///////////////////

    explicit Cell();
    explicit Cell(QString formula);

    ~Cell();

///////////////////

    Cell* clone() const override;

    void setData(int role, const QVariant& value) override;

    QVariant data(int role) const override;

    void setFormula(const QString &formula);

    QString formula() const;

    void setDirty();
    bool Dirty() const;


private:
    Ui::Cell *ui;

    QVariant value() const;

    QVariant evalExpression(const QString &str, int &pos) const;

    QVariant evalTerm(const QString &str, int &pos) const;

    QVariant evalFactor(const QString &str, int &pos) const;

    const QVariant INVALID;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;
};
#endif // CELL_H
