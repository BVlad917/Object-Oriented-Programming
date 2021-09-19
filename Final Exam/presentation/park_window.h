//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_PARK_WINDOW_H
#define E2_BVLAD917_PARK_WINDOW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QAbstractTableModel>
#include "../business/service.h"

class ParkWindow: public QWidget {
private:
    Service& srv;
    QVBoxLayout* mainLayout{};
    QTableView* buildingsTableView{};
    QAbstractTableModel* buildingsModel;

    void initGUI();

public:
    ParkWindow(Service& srv, QAbstractTableModel* buildingsModel);


};


#endif //E2_BVLAD917_PARK_WINDOW_H
