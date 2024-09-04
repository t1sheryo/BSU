#include "HistogramWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QTime>

    HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget(parent),
    penColor(Qt::black),
    brushColor(Qt::green),
    penWidth(1),
    penStyle(Qt::SolidLine)
{
    srand(static_cast<uint>(QTime::currentTime().msec()));
    for (int i = 0; i < 10; ++i) {
        values.append(rand() % 100);
    }
}

void HistogramWidget::setValues(const QVector<int>& values) {
    this->values = values;
    update();
}

QVector<int> HistogramWidget::getValues() const {
    return values;
}

void HistogramWidget::setPenColor(const QColor &color) {
    penColor = color;
    update();
}

void HistogramWidget::setBrushColor(const QColor &color) {
    brushColor = color;
    update();
}

void HistogramWidget::setPenWidth(int width) {
    penWidth = width;
    update();
}

void HistogramWidget::setPenStyle(Qt::PenStyle style) {
    penStyle = style;
    update();
}

QColor HistogramWidget::getPenColor() const {
    return penColor;
}

QColor HistogramWidget::getBrushColor() const {
    return brushColor;
}

int HistogramWidget::getPenWidth() const {
    return penWidth;
}

Qt::PenStyle HistogramWidget::getPenStyle() const {
    return penStyle;
}

void HistogramWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawHistogram(painter);
}

void HistogramWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update();
}

void HistogramWidget::drawHistogram(QPainter &painter) {
    if (values.isEmpty()) return;

    int width = this->width();
    int height = this->height();
    int barWidth = width / values.size();

    painter.setPen(QPen(penColor, penWidth, penStyle));

    for (int i = 0; i < values.size(); ++i) {
        int barHeight = (values[i] * height) / 100;
        QRect barRect(i * barWidth, height - barHeight, barWidth - 1, barHeight);
        draw3DBar(painter, barRect);
        painter.drawText(barRect.bottomLeft() + QPoint(2, -2), QString::number(values[i]));
    }
}

void HistogramWidget::draw3DBar(QPainter &painter, const QRect &rect) {
    QPoint points[6] = {
        rect.bottomLeft(),
        rect.topLeft(),
        rect.topRight(),
        rect.bottomRight(),
        rect.bottomLeft() + QPoint(10, -10),
        rect.topLeft() + QPoint(10, -10)
    };

    QPoint sidePoints[4] = {
        rect.topRight(),
        rect.bottomRight(),
        rect.bottomRight() + QPoint(10, -10),
        rect.topRight() + QPoint(10, -10)
    };

    QPoint topPoints[4] = {
        rect.topLeft(),
        rect.topRight(),
        rect.topRight() + QPoint(10, -10),
        rect.topLeft() + QPoint(10, -10)
    };

    // Front face
    painter.setBrush(brushColor);
    painter.drawPolygon(points, 4);

    // Right face
    painter.setBrush(brushColor.darker(150));
    painter.drawPolygon(sidePoints, 4);

    // Top face
    painter.setBrush(brushColor.lighter(150));
    painter.drawPolygon(topPoints, 4);
}

void HistogramWidget::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("1 px", this);
    connect(&action1, &QAction::triggered, this, [this]() { setPenWidth(1); });
    contextMenu.addAction(&action1);

    QAction action2("3 px", this);
    connect(&action2, &QAction::triggered, this, [this]() { setPenWidth(3); });
    contextMenu.addAction(&action2);

    QAction action3("5 px", this);
    connect(&action3, &QAction::triggered, this, [this]() { setPenWidth(5); });
    contextMenu.addAction(&action3);

    contextMenu.exec(event->globalPos());
}
