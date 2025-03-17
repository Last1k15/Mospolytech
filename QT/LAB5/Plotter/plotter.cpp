#include "plotter.h"

#include <QTGui>
#include <cmath>

Plotter::Plotter(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);

    rubberBandIsShown = false;

    zoomInButton = new QToolButton{this};
    zoomInButton->setIcon(QIcon{":/ico/icons/zoomin.png"});
    zoomInButton->adjustSize();
    connect(zoomInButton, &QToolButton::clicked, this, &Plotter::zoomIn);

    zoomOutButton = new QToolButton{this};
    zoomOutButton->setIcon(QIcon{":/ico/icons/zoomout.png"});
    zoomOutButton->adjustSize();
    connect(zoomOutButton, &QToolButton::clicked, this, &Plotter::zoomOut);

    setPlotSettings(PlotSettings{});
}

Plotter::~Plotter() {}

void Plotter::setPlotSettings(const PlotSettings& settings)
{
    zoomStack.clear();
    zoomStack.append(settings);
    zoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();
    refreshPixmap();
}

void Plotter::zoomOut()
{
    if (zoom <= 0) return;

    zoom--;
    zoomOutButton->setEnabled(zoom > 0);

    zoomInButton->setEnabled(true);
    zoomInButton->show();

    refreshPixmap();
}

void Plotter::zoomIn()
{
    if (zoom >= zoomStack.count() - 1) return;

    zoom++;
    zoomInButton->setEnabled(zoom < zoomStack.count() - 1);

    zoomOutButton->setEnabled(true);
    zoomOutButton->show();

    refreshPixmap();
}

void Plotter::setCurveData(int id, QVector<QPointF> data)
{
    curveMap[id] = data;
    refreshPixmap();
}

void Plotter::clearCurve(int id)
{
    curveMap.remove(id);
    refreshPixmap();
}

void Plotter::paintEvent(QPaintEvent*)
{
    QStylePainter painter{this};
    painter.drawPixmap(0,0, pixmap);

    if (rubberBandIsShown)
    {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect.normalized().adjusted(0, 0, -1, -1));
    }

    if (hasFocus())
    {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}

void Plotter::resizeEvent(QResizeEvent*)
{
    int x = width() - zoomInButton->width() - zoomOutButton->width() - 10;
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5, 5);
    refreshPixmap();
}

void Plotter::mousePressEvent(QMouseEvent* event)
{
    QRect rect {Margin, Margin, width() - 2*Margin, height() - 2*Margin};
    QPoint mousePos = event->pos();

    if (event->button() != Qt::LeftButton || !rect.contains(mousePos)) return;

    rubberBandIsShown = true;
    rubberBandRect.setTopLeft(mousePos);
    rubberBandRect.setBottomRight(mousePos);
    updateRubberBandRegion();

    setCursor(Qt::CrossCursor);
}

void Plotter::mouseMoveEvent(QMouseEvent* event)
{
    if (!rubberBandIsShown) return;

    updateRubberBandRegion();
    rubberBandRect.setBottomRight(event->pos());
    updateRubberBandRegion();
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)

{
    if (event->button() != Qt::LeftButton) return;

    rubberBandIsShown = false;
    updateRubberBandRegion();
    unsetCursor();

    QRect rect = rubberBandRect.normalized();

    if (rect.width() < 4 || rect.height() < 4)
        return;

    rect.translate(-Margin, -Margin);

    PlotSettings prevSettings = zoomStack[zoom];
    PlotSettings settings;

    double dx = prevSettings.spanX() / (width() - 2 * Margin);
    double dy = prevSettings.spanY() / (height() - 2 * Margin);

    settings.minX = prevSettings.minX + dx * rect.left();
    settings.maxX = prevSettings.minX + dx * rect.right();
    settings.minY = prevSettings.maxY - dy * rect.bottom();
    settings.maxY = prevSettings.maxY - dy * rect.top();
    settings.adjust();



    zoomStack.resize(zoom + 1);
    zoomStack.append(settings);
    zoomIn();
}

void Plotter::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Plus:
        case Qt::Key_Equal:
        {
            zoomIn();
            break;
        }
        case Qt::Key_Minus:
        {
            zoomOut();
            break;
        }
        case Qt::Key_Left:
        {
            zoomStack[zoom].scroll(-1 ,0);
            refreshPixmap();
            break;
        }
        case Qt::Key_Right:
        {
            zoomStack[zoom].scroll(1, 0);
            refreshPixmap();
            break;
        }
        case Qt::Key_Down:
        {
            zoomStack[zoom].scroll(0, -1);
            refreshPixmap();
            break;
        }
        case Qt::Key_Up:
        {
            zoomStack[zoom].scroll(0, 1);
            refreshPixmap();
            break;
        }
        default:
            QWidget::keyPressEvent(event);
    }
}

void Plotter::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;
    int numTicks = numDegrees / 15;

    bool VerticalWheelMovement {event->angleDelta().x() == 0};

    if (VerticalWheelMovement)
        zoomStack[zoom].scroll(0, numTicks);

    else zoomStack[zoom].scroll(numTicks, 0);

    refreshPixmap();
}

void Plotter::updateRubberBandRegion()
{
    QRect rect = rubberBandRect.normalized();

    update(rect.left(), rect.top(), rect.width(), 1);
    update(rect.left(), rect.top(), 1, rect.height());
    update(rect.left(), rect.bottom(), rect.width(), 1);
    update(rect.right(), rect.top(), 1, rect.height());
}

void Plotter::drawCurves(QPainter *painter)
{
    static const QColor colorForIds[6]
    {
        Qt::red,
        Qt::green,
        Qt::blue,
        Qt::cyan,
        Qt::magenta,
        Qt::yellow
    };

    PlotSettings settings = zoomStack[zoom];

    QRect rect (Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);

    if (!rect.isValid())
        return;

    painter->setClipRect(rect.adjusted(1, 1, -1, -1));

    QMapIterator<int, QVector<QPointF>> i(curveMap);

    while (i.hasNext())
    {
        i.next();

        int id = i.key();
        const QVector<QPointF> &data = i.value();
        QPolygonF polyline(data.count());

        for (int j = 0; j < data.count(); ++j)
        {
            double dx = data[j].x() - settings.minX;
            double dy = data[j].y() - settings.minY;
            double x = rect.left() + (dx * (rect.width() - 1) / settings.spanX());
            double y = rect.bottom() - (dy * (rect.height() - 1) / settings.spanY());

            polyline[j] = QPointF(x, y);
        }

        painter->setPen(colorForIds[uint(id) % 6]);
        painter->drawPolyline(polyline);
    }
}

void Plotter::drawGrid(QPainter *painter)
{
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);

    if (!rect.isValid())
        return;

    PlotSettings settings = zoomStack[zoom];
    QPen quiteDark = palette().dark().color().lighter();
    QPen light = palette().light().color();

    for (int i = 0; i <= settings.numXTicks; ++i)
    {
        int x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks);
        double label = settings.minX + (i * settings.spanX() / settings.numXTicks);

        painter->setPen(quiteDark);
        painter->drawLine(x, rect.top(), x, rect.bottom());

        painter->setPen(light);
        painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
        painter->drawText(x - 50, rect.bottom() + 5, 100, 15, Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
    }

    for (int j = 0; j <= settings.numYTicks; ++j)
    {
        int y = rect.bottom() - (j * (rect.height() - 1) / settings.numYTicks);
        double label = settings.minY + (j * settings.spanY() / settings.numYTicks);

        painter->setPen(quiteDark);
        painter->drawLine(rect.left(), y, rect.right(), y);

        painter->setPen(light);
        painter->drawLine(rect.left() - 5, y, rect.left(), y);
        painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20, Qt::AlignRight | Qt::AlignVCenter, QString::number(label));
    }

    painter->drawRect(rect.adjusted(0, 0, -1, -1));
}

void Plotter::refreshPixmap()
{
    pixmap = QPixmap{size()};
    pixmap.fill(palette().dark().color());

    QPainter painter(&pixmap);

    drawGrid(&painter);
    drawCurves(&painter);

    update();
}

PlotSettings::PlotSettings(double _minX, double _maxX, double _minY, double _maxY)
    :   minX{_minX}, maxX{_maxX},
        minY{_minY}, maxY{_maxY}
{
    adjust();
}

void PlotSettings::scroll(int dx, int dy)
{
    double stepX = spanX() / numXTicks;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = spanY() / numYTicks;
    minY += dy * stepY;
    maxY += dy * stepY;
}

void PlotSettings::adjust()

{
    adjustAxis(minX, maxX, numXTicks);
    adjustAxis(minY, maxY, numYTicks);
}

void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    constexpr int MinTicks = 4;
    double grossStep = (max - min) / MinTicks;
    double step = pow(10.0, floor(log10(grossStep)));

    if (5 * step < grossStep)
        step *= 5;
    else if (2 * step < grossStep)
        step *= 2;

    numTicks = int(ceil(max / step) - floor(min / step));

    if (numTicks < MinTicks)
       numTicks = MinTicks;

    min = floor(min / step) * step;
    max = ceil(max / step) * step;
}
