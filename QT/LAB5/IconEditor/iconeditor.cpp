#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent ) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    curColor = Qt::black;
    resetZoomFactor();

    image = QImage(16, 16, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
}

IconEditor::~IconEditor()
{
}

QSize IconEditor::sizeHint() const
{
    QSize size = zoom*image.size();
    if (zoom >= 3)
        size += QSize(1,1);
    return size;
}

void IconEditor::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

void IconEditor::setIconImage(QImage newImage)
{
    if (newImage == image) return;

    image = newImage.convertToFormat(QImage::Format_ARGB32);
    resetZoomFactor();
    update();
    updateGeometry();
}

void IconEditor::setZoomFactor(int newZoom)
{
    if (newZoom == zoom) return;

    if (newZoom < 1)
        resetZoomFactor();
    else zoom = newZoom;

    update();
    updateGeometry();
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // draw grid
    if (zoom >= 3)
    {
        painter.setPen(palette().base().color());
        for (int i = 0; i <= image.width(); ++i) painter.drawLine(zoom*i, 0, zoom*i, zoom *image.height());
        for (int j = 0; j <= image.height(); ++j) painter.drawLine(0, zoom*j, zoom*image.width(), zoom*j);
    }


    // fill pixels
    for (int i = 0; i < image.width(); ++i)
        for (int j = 0; j < image.height(); ++j)
        {
            QRect rect = pixelRect(i,j);
            if (event->rect().intersects(rect)){
                QColor color = QColor::fromRgba(image.pixel(i, j));
                painter.fillRect(rect, color);
            }
        }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom >= 3)
        return QRect(zoom*i+1, zoom*j+1, zoom-1, zoom-1);

    return QRect(zoom*i,zoom*j, zoom, zoom);
}

void IconEditor::wheelEvent(QWheelEvent* event)
{
    int wheelRotateAngle {event->angleDelta().y()};

    bool forwardScroll {wheelRotateAngle > 0};
    bool backwardScroll {wheelRotateAngle < 0};

    if (forwardScroll)
        setZoomFactor(zoom + 1);

    else if (backwardScroll)
        setZoomFactor(zoom - 1);
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        setImagePixel(event->pos(), true);

    else if (event->button() == Qt::RightButton)
        setImagePixel(event->pos(), false);
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons()) return;


    Qt::MouseButtons activeBtns = event->buttons();

    if (activeBtns & Qt::LeftButton)
        setImagePixel(event->pos(), true);

    else if (activeBtns & Qt::RightButton)
        setImagePixel(event->pos(), false);
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    int i = pos.x()/zoom;
    int j = pos.y()/zoom;

    if (!image.rect().contains(i,j)) return;

    if (opaque)
        image.setPixel(i,j, penColor().rgba());
    else image.setPixel(i,j,qRgba(0,0,0,0));

    update(pixelRect(i,j));
}
