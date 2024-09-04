#ifndef view_H
#define view_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "controller.h"

class view : public QWidget {
    Q_OBJECT

public:
    view(controller *_controller, QWidget *parent = nullptr);
    void updateView(const QList<provaider> &provaiders);

private slots:
    void onQueryButtonClicked();


private:
    QLineEdit *minTimeLineEdit;
    QLineEdit *maxTimeLineEdit;
    QPushButton *queryButton;
    QTableWidget *tableWidget;
    controller *Controller;
};

#endif // view_H
