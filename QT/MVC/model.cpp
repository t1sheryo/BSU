#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
model::model(const QString &filename) : Provaiders() {
    loadFromFile(filename);
}

QList<provaider> model::getprovaidersInPriceRange(double minTime, double maxTime) const {
    QList<provaider> result;
    for (const provaider &Provaider : Provaiders) {
        if (Provaider.getTime() >= minTime && Provaider.getTime() <= maxTime) {
            result.append(Provaider);
        }
    }
    return result;
}

void model::loadFromFile(const QString &filename) {
    QFile file(filename);
    QList c1({QString("13:00"), QString("18:00"), QString("300")});
    QList c2({QString("11:05"), QString("23:00"), QString("705")});
    // QList v1(c1);
    // QList v2(c2);
    provaider Provaider(QString("Petya"), QList(c1));
    Provaiders.append(Provaider);
    provaider Provaider1(QString("Vasya"), QList(c2));
    Provaiders.append(Provaider1);
}
