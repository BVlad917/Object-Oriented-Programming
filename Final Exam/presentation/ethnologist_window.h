//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_ETHNOLOGIST_WINDOW_H
#define E2_BVLAD917_ETHNOLOGIST_WINDOW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "../business/service.h"

class EthnologistWindow: public QWidget {
Q_OBJECT

private:
    Service& srv;
    std::string ethnologistName;
    QColor color;

    QVBoxLayout* mainLayout{};
    QTableView* buildingsTableView{};
    QAbstractTableModel* buildingsModel;
    QAbstractTableModel* parkModel;
    QGridLayout* rightLayout{};

    QLabel* idLabel{};
    QLabel* descriptionLabel{};
    QLabel* locationLabel{};

    QLineEdit* idLineEdit{};
    QLineEdit* descriptionLineEdit{};
    QLineEdit* locationLineEdit{};

    QPushButton* addButton{};
    QPushButton* updateButton{};

    void initEthnologistWindow();

    void connectSignalsAndSlots();

    void guiAddBuilding();

    void guiUpdateBuilding();

public:
    EthnologistWindow(Service& srv, QAbstractTableModel* buildingsModel, QAbstractTableModel* parkModel, std::string name, QColor color);
};


#endif //E2_BVLAD917_ETHNOLOGIST_WINDOW_H
