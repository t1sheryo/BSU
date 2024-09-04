/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *Nolik;
    QPushButton *Krestik;
    QWidget *widget_field;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(891, 542);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/OIP.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(159, 159, 159);\n"
"color: rgb(30, 30, 30);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMaximumSize(QSize(300, 400));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        Nolik = new QPushButton(widget);
        Nolik->setObjectName("Nolik");
        sizePolicy.setHeightForWidth(Nolik->sizePolicy().hasHeightForWidth());
        Nolik->setSizePolicy(sizePolicy);
        Nolik->setMinimumSize(QSize(20, 20));

        verticalLayout->addWidget(Nolik);

        Krestik = new QPushButton(widget);
        Krestik->setObjectName("Krestik");
        sizePolicy.setHeightForWidth(Krestik->sizePolicy().hasHeightForWidth());
        Krestik->setSizePolicy(sizePolicy);
        Krestik->setMinimumSize(QSize(20, 20));

        verticalLayout->addWidget(Krestik);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_field = new QWidget(centralwidget);
        widget_field->setObjectName("widget_field");
        widget_field->setMinimumSize(QSize(500, 500));
        widget_field->setMaximumSize(QSize(500, 500));

        gridLayout->addWidget(widget_field, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\265\321\201\321\202\320\270\320\272\320\270-\320\235\320\276\320\273\320\270\320\272\320\270", nullptr));
        Nolik->setText(QCoreApplication::translate("MainWindow", "\320\230\320\223\320\240\320\220\320\242\320\254 \320\235\320\236\320\233\320\230\320\232\320\220\320\234\320\230", nullptr));
        Krestik->setText(QCoreApplication::translate("MainWindow", "\320\230\320\223\320\240\320\220\320\242\320\254 \320\232\320\240\320\225\320\241\320\242\320\230\320\232\320\220\320\234\320\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
