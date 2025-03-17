#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QMap>
#include <QVector>
#include <QStack>
#include <QWidget>
#include <QToolButton>
#include <QStylePainter>
#include <QStyleOptionFocusRect>

class PlotSettings;

class Plotter
    : public QWidget
{
    Q_OBJECT

public:
    Plotter(QWidget *parent = nullptr);
    ~Plotter();

    void setPlotSettings(const PlotSettings& settings);
    void setCurveData(int id, const QVector<QPointF> data);
    void clearCurve(int id);
    void resetZoom();
    inline QSize minimumSizeHint() const override
    {
        return QSize{6 * Margin, 6 * Margin};
    }

    static inline constexpr unsigned int CURVE_LIMIT {6};

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    void updateRubberBandRegion();
    void refreshPixmap();
    void drawGrid(QPainter* painter);
    void drawCurves(QPainter* painter);

    enum {Margin = 50};

    QToolButton* zoomInButton;
    QToolButton* zoomOutButton;
    QMap<int, QVector<QPointF>> curveMap;
    QStack<PlotSettings> zoomStack;
    PlotSettings* prefferedSettings;
    int zoom;
    bool rubberBandIsShown;
    QRect rubberBandRect;
    QPixmap pixmap;
    QPainter painter;
};

class PlotSettings
{
public:
    PlotSettings()
        :   PlotSettings(0, 10, 0, 10){}
    PlotSettings(double minValue, double maxValue)
        :   PlotSettings(minValue, maxValue, minValue, maxValue){};
    PlotSettings(double minX, double maxX, double, double maxY);

    void scroll(int dx, int dy);
    void adjust();

    inline double spanX() const {return maxX - minX;}
    inline double spanY() const {return maxY - minY;}

    double minX;
    double maxX;
    int numXTicks;

    double minY;
    double maxY;
    int numYTicks;

private:
    static void adjustAxis(double& min, double& max, int& numTicks);

};

#endif // PLOTTER_H
