#include "view.h"
#include <QVBoxLayout>

view::view(controller *_controller, QWidget *parent)
    : QWidget(parent), Controller(_controller) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    minTimeLineEdit = new QLineEdit(this);
    maxTimeLineEdit = new QLineEdit(this);
    queryButton = new QPushButton("Query", this);
    tableWidget = new QTableWidget(this);

    layout->addWidget(minTimeLineEdit);
    layout->addWidget(maxTimeLineEdit);
    layout->addWidget(queryButton);
    layout->addWidget(tableWidget);

    connect(queryButton, &QPushButton::clicked, this, &view::onQueryButtonClicked);
}

void view::updateView(const QList<provaider> &provaiders) {
    tableWidget->setRowCount(provaiders.size());
    tableWidget->setColumnCount(4);

    for (int i = 0; i < provaiders.size(); ++i) {
        const provaider &Provaider = provaiders[i];
        tableWidget->setItem(i, 0, new QTableWidgetItem(Provaider.getperson()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(Provaider.getTime())));
    }
}

void view::onQueryButtonClicked() {
    double minTime = minTimeLineEdit->text().toDouble();
    double maxTime = maxTimeLineEdit->text().toDouble();
    QList<provaider> boo = Controller->onPriceRangeQuery(minTime, maxTime);
    updateView(boo);
}


