//
// Created by VladB on 22-Jun-21.
//

#include "park_window.h"

ParkWindow::ParkWindow(Service &srv, QAbstractTableModel *buildingsModel): srv{srv}, buildingsModel{buildingsModel} {
    this->initGUI();

    this->buildingsTableView->setModel(this->buildingsModel);

}

void ParkWindow::initGUI() {
    this->mainLayout = new QVBoxLayout{this};
    this->buildingsTableView = new QTableView{};
    this->mainLayout->addWidget(this->buildingsTableView);

}
