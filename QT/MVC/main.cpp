#include <QApplication>
#include "model.h"
#include "controller.h"
#include "view.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    model Model("provaiders.txt");
    controller Controller(&Model);
    view View(&Controller);

    View.show();

    return app.exec();
}
