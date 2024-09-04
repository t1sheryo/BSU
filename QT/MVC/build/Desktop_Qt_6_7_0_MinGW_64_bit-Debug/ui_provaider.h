/********************************************************************************
** Form generated from reading UI file 'provaider.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVAIDER_H
#define UI_PROVAIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Provaider
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Provaider)
    {
        if (Provaider->objectName().isEmpty())
            Provaider->setObjectName("Provaider");
        Provaider->resize(800, 600);
        centralwidget = new QWidget(Provaider);
        centralwidget->setObjectName("centralwidget");
        Provaider->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Provaider);
        menubar->setObjectName("menubar");
        Provaider->setMenuBar(menubar);
        statusbar = new QStatusBar(Provaider);
        statusbar->setObjectName("statusbar");
        Provaider->setStatusBar(statusbar);

        retranslateUi(Provaider);

        QMetaObject::connectSlotsByName(Provaider);
    } // setupUi

    void retranslateUi(QMainWindow *Provaider)
    {
        Provaider->setWindowTitle(QCoreApplication::translate("Provaider", "Provaider", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Provaider: public Ui_Provaider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVAIDER_H
