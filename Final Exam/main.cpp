//
// Created by VladB on 22-Jun-21.
//

#include <iostream>
#include <QApplication>
#include "persistency/ethnologists_repo.h"
#include "persistency/buildings_repo.h"
#include "business/service.h"
#include "presentation/all_windows.h"

int main(int argc, char* argv[]) {
    QApplication app{argc, argv};

    EthnologistsRepo er{"../ethnologists.txt"};
    BuildingsRepo br{"../buildings.txt"};
    Service srv{er, br};

    AllWindows allWindows{srv};
    allWindows.showAllWindows();

    return app.exec();
}