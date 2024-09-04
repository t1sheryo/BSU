#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QMessageBox>
#include <QComboBox>
#include <QColor>
#include <QPixmap>
#include <QRadioButton>
#include <QButtonGroup>
#include <QActionGroup>
#include <QContextMenuEvent>
#include <QStatusBar>
#include <QLabel>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QFileDialog>
#include <QTextStream>
#include <sstream>
#include <string>
#include <QShortcut>
#include <QCloseEvent>

class Histogram {
public:
    //Histogram();
    Histogram(){
        int size = rand() % 10;
        size_ = size;
       // data_ = new QVector<int>();
        for(int i = 0; i < size; i++){
            int rand_num = rand() % 10;
            data_.push_back(rand_num);
        }
    }
    //Histogram(const Histogram &other);
    //Histogram &operator=(const Histogram &other);

    void setData(QVector<int> data) {
        for(int i = 0; i < data.size(); ++i){
            data_.push_back(data[i]);
        }
    };
    QVector<int> getData() { return data_; };

    void setPenColor(const QColor &color);
    QColor getPenColor() const { return penColor_; }

    void setBrushColor(const QColor &color);
    QColor getBrushColor() const { return brushColor_; }

    void setPenWidth(int width);
    int getPenWidth() const { return penWidth_; }

    //void draw(QPainter &painter, const QRect &rect);

    //int getSize() const { return size_; }

    ~Histogram();

private:
    QVector<int> data_;
    QColor penColor_;
    QColor brushColor_;
    int penWidth_;
    int size_;
};

#endif // HISTOGRAM_H
