#ifndef controller_H
#define controller_H

#include "model.h"

class controller {
public:
    controller(model *model);
    QList<provaider> onPriceRangeQuery(double minTime, double maxTime);

private:
    model *Model;
};

#endif // controller_H
