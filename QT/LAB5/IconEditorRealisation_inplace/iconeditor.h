#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QWheelEvent>

namespace Ui {
class IconEditor;
}

class IconEditor
    : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit IconEditor(QWidget *parent = 0);
    ~IconEditor();

    void setPenColor(const QColor &newColor);
    QColor penColor() const {return curColor;}

    void setZoomFactor(int newZoom);
    inline int zoomFactor() const {return zoom;}
    inline void resetZoomFactor() {zoom = 1;}

    void setIconImage(QImage newImage);
    QImage iconImage() const {return image;}

    QSize sizeHint() const override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::IconEditor *ui;

    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    QColor curColor;
    QImage image;
    int zoom;
};

#endif // ICONEDITOR_H
