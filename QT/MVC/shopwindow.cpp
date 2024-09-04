#include "shopwindow.h"
#include "ui_shopwindow.h"
#include <QDoubleValidator>

ShopWindow::ShopWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShopWindow)
{
    ui->setupUi(this);
    inputPrice.setValidator(new QDoubleValidator(this));
    QGridLayout *layer = new QGridLayout;
    this->centralWidget()->window()->setLayout(layer);
    layer->addWidget(&inputPrice, 0, 0);
}

ShopWindow::~ShopWindow()
{
    delete ui;
}
