//
// Created by VladB on 24-May-21.
//

#include <QApplication>
#include "persistency/repository.h"
#include "business/service.h"
#include "interface/gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Repository repo{"../input.txt"};
    Service srv{repo};
    GUI gui{srv};
    gui.show();

    return app.exec();
}