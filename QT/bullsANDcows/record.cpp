#include "record.h"

Record::Record(QWidget *parent){
    scoreTable = new QTableWidget(parent);
}

void Record::refill(){
    scoreTable->show();
    scoreTable->setRowCount(11);
    scoreTable->setColumnCount(2);
    scoreTable->setItem(0, 0, new QTableWidgetItem("Попытки"));
    scoreTable->setItem(0, 1, new QTableWidgetItem("Имя"));
    size_t i = 1;
    for(auto it = records.begin(); i < 12, it != records.end(); ++i, ++it){
        QString number = QString::number(it->first);
        scoreTable->setItem(i, 0, new QTableWidgetItem(QString(number)));
        scoreTable->setItem(i, 1, new QTableWidgetItem(QString(it->second)));
    }
}

bool Record::isTop(int score) {
    int i = 0;
    for (auto it = records.begin(); it != records.end(); ++it) {
        if (i > 10)
            return false;
        if (it->first > score)
            return true;
        ++i;
    }
    return true;
}

void Record::add(QString name, int steps){
    records.insert({steps, name});
}
