#include "cell.h"

///////////////////////////////////////////////////////
/// LIFETIME
///

Cell::Cell()
{
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
    // static const QRegularExpression cell_regExp {"[A-Za-z][1-9][0-9]{0,2}"};
    // const QRegularExpressionMatch matches {cell_regExp.match(str)};
    // if (!matches.hasMatch()) return INVALID;
    // for (int i = 0; i <= matches.lastCapturedIndex(); i++)
    // {

    // }

    qDebug() << "EMPTY FUNC!";
    return QVariant{};
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
        if (expr[pos] != QChar::Null)
            cachedValue = INVALID;
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


///////////////////////////////////////////////////////
/// FORMULA
///

void Cell::setFormula(const QString& formula)
{
    setData(Qt::EditRole, formula);
}

QString Cell::formula() const
{
    return data(Qt::EditRole).toString();
}
///////////////////////////////////////////////////////
/// DIRTY
///

void Cell::setDirty()
{
    cacheIsDirty = true;
}

bool Cell::Dirty() const
{
    return cacheIsDirty;
}
