#ifndef FIGURE_H
#define FIGURE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Figure;
}
QT_END_NAMESPACE

class Figure : public QMainWindow
{
    Q_OBJECT

public:
    Figure(QWidget *parent = nullptr);
    ~Figure();

private:
    Ui::Figure *ui;
};
#endif // FIGURE_H
