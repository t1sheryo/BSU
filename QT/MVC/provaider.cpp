#include "provaider.h"

provaider::provaider(QString _person, QList <QString> _times)
    : person(_person), times(_times){
    int sum = 0;
    int index = 2;
    for(index; index < _times.size(); index += 3){
        QString value = _times[index];
        int val = value.toInt();
        sum += val;
    }
    time = sum;
}

QString provaider::getperson() const { return person; }
//QVector <QVector<QString>> provaider::getTimes() const { return times; }
double provaider::getTime() const { return time; }
