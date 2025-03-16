#include "cell.h"
#include "spreadsheet.h"

///////////////////////////////////////////////////////
/// LIFETIME
///

Cell::Cell(SpreadSheet* _parent)
{
    parent = _parent;
    setDirty();
}

Cell::Cell(const QString formula)
{
    setDirty();
    setFormula(formula);
}

Cell::~Cell(){}

Cell* Cell::clone() const
{
    return new Cell{*this};
}

///////////////////////////////////////////////////////
/// EXPRESSION
///
QVariant Cell::evalExpression(const QString& str, int& pos) const
{
    return INVALID;
}


///////////////////////////////////////////////////////
/// VALUE
///

QVariant Cell::value() const
{
    if (!cacheIsDirty) return cachedValue;

    cacheIsDirty = false;

    QString formulaStr = formula();

    if (formulaStr.startsWith('\''))
        cachedValue = formulaStr.mid(1);

    else if(formulaStr.startsWith('='))
    {
        cachedValue = INVALID;

        QString expr = formulaStr.mid(1);
        expr.replace(" ", "");
        expr.append(QChar::Null);

        int pos = 0;
        cachedValue = evalExpression(expr, pos);
    }
    else{
        bool ok;
        double d = formulaStr.toDouble(&ok);

        if (ok) cachedValue = d;
        else cachedValue = formulaStr;
    }

    return cachedValue;
}


///////////////////////////////////////////////////////
/// DATA
///
void Cell::setData(int role, const QVariant& value)
{
    QTableWidgetItem::setData(role, value);
    if (role == Qt::EditRole) setDirty();
}

QVariant Cell::data(int role) const
{
    QVariant cellValue = value();

    if (role == Qt::DisplayRole)
        return (cellValue.isValid() ? cellValue.toString() : "####");

    if (role == Qt::TextAlignmentRole)
    {
        bool isStr {cellValue.typeId() == QMetaType::QString};
        return int{isStr ? Qt::AlignLeft : Qt::AlignRight} | Qt::AlignVCenter;
    }

    else return QTableWidgetItem::data(role);
}
