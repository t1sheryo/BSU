#include "mainwindow.h"

#include <QApplication>
#include <qlabel>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <QWidget>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.resize(500, 500);
    window.setWindowTitle("Icon");
    window.show();

    window.setWindowIcon(QIcon("C:\Users\ilayz\OneDrive\Рабочий стол\proga\QT"));

    return a.exec();
}
