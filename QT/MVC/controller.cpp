#include "controller.h"

controller::controller(model *_model) : Model(_model) {}

QList<provaider> controller::onPriceRangeQuery(double minTime, double maxTime) {
    QList<provaider> Provaiders = Model->getprovaidersInPriceRange(minTime, maxTime);
    return Provaiders;
}
