#ifndef provaider_H
#define provaider_H

#include <QString>
#include <QVector>
#include <QList>

class provaider {
public:
    provaider(QString _person, QList<QString> _times);
    QString getperson() const;
    //QVector <QVector<QString>>& getTimes() const;
    double getTime() const;

private:
    QString person;
    QList <QString> times;
    int time;
};

#endif // provaider_H
