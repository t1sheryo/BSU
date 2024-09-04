#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <vector>
#include <QPushButton>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class ShopWindow;
}
QT_END_NAMESPACE

class ShopWindow : public QMainWindow
{
    Q_OBJECT

public:
    ShopWindow(QWidget *parent = nullptr);
    ~ShopWindow();

private:
    Ui::ShopWindow *ui;
    QLineEdit inputPrice;
    QWidget* wind;
};
#endif // SHOPWINDOW_H
