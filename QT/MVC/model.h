#ifndef model_H
#define model_H

#include <QList>
#include "provaider.h"

class model {
public:
    model(const QString &filename);
    // void addprovaider(const provaider &provaider);
    QList<provaider> getprovaidersInPriceRange(double minPrice, double maxPrice) const;

private:
    QList<provaider> Provaiders;
    void loadFromFile(const QString &filename);
};

#endif // model_H
