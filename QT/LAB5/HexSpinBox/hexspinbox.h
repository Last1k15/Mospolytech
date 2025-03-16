#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class HexSpinBox;
}
QT_END_NAMESPACE

class HexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    HexSpinBox(QWidget *parent = nullptr);
    ~HexSpinBox();
protected:
    QString textFromValue(const int) const;
    int valueFromText(const QString&) const;
    QValidator::State validate (QString& text, int& pos) const;

private:
    QRegularExpressionValidator* validator;
    Ui::HexSpinBox *ui;
};
#endif // HEXSPINBOX_H
