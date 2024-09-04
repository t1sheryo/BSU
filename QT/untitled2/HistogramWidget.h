#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QColor>
#include <QPen>

class HistogramWidget : public QWidget {
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = nullptr);
    void setValues(const QVector<int>& values);
    QVector<int> getValues() const; // добавляем метод getValues

    void setPenColor(const QColor &color);
    QColor getPenColor() const;

    void setBrushColor(const QColor &color);
    QColor getBrushColor() const;

    void setPenWidth(int width);
    int getPenWidth() const;

    void setPenStyle(Qt::PenStyle style);
    Qt::PenStyle getPenStyle() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:

    QVector<int> values;
    QColor penColor;
    QColor brushColor;
    int penWidth;
    Qt::PenStyle penStyle;
};

#endif // HISTOGRAMWIDGET_H
