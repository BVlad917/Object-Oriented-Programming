//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_ALL_WINDOWS_H
#define E2_BVLAD917_ALL_WINDOWS_H


#include <vector>
#include "ethnologist_window.h"
#include "park_window.h"
#include "park_model.h"

class AllWindows {
private:
    Service& srv;
    QAbstractTableModel* buildingsModel;
    std::vector<EthnologistWindow*> allWindows;
    std::vector<QColor> colors{QColor(Qt::red), QColor(Qt::green), QColor(Qt::yellow), QColor(Qt::blue)};
    ParkWindow* parkWindow{};
    ParkModel* parkModel{};

public:
    explicit AllWindows(Service& srv);

    void showAllWindows();
};


#endif //E2_BVLAD917_ALL_WINDOWS_H
