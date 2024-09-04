#include "figure.h"
#include "ui_figure.h"

Figure::Figure(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Figure)
{
    ui->setupUi(this);
}

Figure::~Figure()
{
    delete ui;
}
