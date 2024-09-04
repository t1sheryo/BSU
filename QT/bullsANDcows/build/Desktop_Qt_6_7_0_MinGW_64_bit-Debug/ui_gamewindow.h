/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gameWindow)
    {
        if (gameWindow->objectName().isEmpty())
            gameWindow->setObjectName("gameWindow");
        gameWindow->resize(800, 600);
        centralwidget = new QWidget(gameWindow);
        centralwidget->setObjectName("centralwidget");
        gameWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gameWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        gameWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(gameWindow);
        statusbar->setObjectName("statusbar");
        gameWindow->setStatusBar(statusbar);

        retranslateUi(gameWindow);

        QMetaObject::connectSlotsByName(gameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *gameWindow)
    {
        gameWindow->setWindowTitle(QCoreApplication::translate("gameWindow", "gameWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameWindow: public Ui_gameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
