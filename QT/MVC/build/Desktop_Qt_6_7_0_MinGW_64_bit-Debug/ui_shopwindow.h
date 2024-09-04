/********************************************************************************
** Form generated from reading UI file 'shopwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOPWINDOW_H
#define UI_SHOPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShopWindow
{
public:
    QWidget *centralwidget;
    QWidget *window;
    QPushButton *outputButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ShopWindow)
    {
        if (ShopWindow->objectName().isEmpty())
            ShopWindow->setObjectName("ShopWindow");
        ShopWindow->resize(800, 600);
        ShopWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(159, 159, 159);\n"
"color: rgb(30, 30, 30);"));
        centralwidget = new QWidget(ShopWindow);
        centralwidget->setObjectName("centralwidget");
        window = new QWidget(centralwidget);
        window->setObjectName("window");
        window->setGeometry(QRect(9, 89, 751, 371));
        outputButton = new QPushButton(window);
        outputButton->setObjectName("outputButton");
        outputButton->setGeometry(QRect(90, 140, 80, 24));
        ShopWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ShopWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ShopWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ShopWindow);
        statusbar->setObjectName("statusbar");
        ShopWindow->setStatusBar(statusbar);

        retranslateUi(ShopWindow);

        QMetaObject::connectSlotsByName(ShopWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ShopWindow)
    {
        ShopWindow->setWindowTitle(QCoreApplication::translate("ShopWindow", "ShopWindow", nullptr));
        outputButton->setText(QCoreApplication::translate("ShopWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShopWindow: public Ui_ShopWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOPWINDOW_H
