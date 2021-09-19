//
// Created by VladB on 22-Jun-21.
//

#include "ethnologist_window.h"

#include <utility>
#include <QHeaderView>
#include <sstream>
#include <QMessageBox>

EthnologistWindow::EthnologistWindow(Service &srv, QAbstractTableModel *buildingsModel, QAbstractTableModel* parkModel, std::string name, QColor color)
        : srv{srv}, buildingsModel{buildingsModel}, ethnologistName{std::move(name)}, color{std::move(color)}, parkModel{parkModel} {
    this->initEthnologistWindow();

    this->setWindowTitle(QString::fromStdString(this->ethnologistName));
    this->buildingsTableView->setModel(this->buildingsModel);
    this->buildingsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, this->color);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    this->connectSignalsAndSlots();
}

void EthnologistWindow::initEthnologistWindow() {
    this->mainLayout = new QVBoxLayout{this};
    this->buildingsTableView = new QTableView{};
    this->mainLayout->addWidget(this->buildingsTableView);

    this->rightLayout = new QGridLayout{};
    this->mainLayout->addLayout(this->rightLayout);

    this->idLabel = new QLabel{"ID: "};
    this->descriptionLabel = new QLabel{"Description: "};
    this->locationLabel = new QLabel{"Location: "};

    this->idLineEdit = new QLineEdit{};
    this->descriptionLineEdit = new QLineEdit{};
    this->locationLineEdit = new QLineEdit{};

    this->addButton = new QPushButton{"Add"};
    this->updateButton = new QPushButton{"Update"};

    this->rightLayout->addWidget(this->idLabel, 0, 0);
    this->rightLayout->addWidget(this->idLineEdit, 0, 1);

    this->rightLayout->addWidget(this->descriptionLabel, 1, 0);
    this->rightLayout->addWidget(this->descriptionLineEdit, 1, 1);

    this->rightLayout->addWidget(this->locationLabel, 2, 0);
    this->rightLayout->addWidget(this->locationLineEdit, 2, 1);

    this->rightLayout->addWidget(this->addButton, 3, 0, 1, 2);
    this->rightLayout->addWidget(this->updateButton, 4, 0, 1, 2);
}

void EthnologistWindow::connectSignalsAndSlots() {
    QObject::connect(this->addButton, &QPushButton::clicked, this, &EthnologistWindow::guiAddBuilding);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &EthnologistWindow::guiUpdateBuilding);

}

std::vector<std::string> third_tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

void EthnologistWindow::guiAddBuilding() {
    int id = this->idLineEdit->text().toInt();
    std::string description = this->descriptionLineEdit->text().toStdString();
    std::string thematicSector = this->srv.findEthnologistByName(this->ethnologistName).getThematicArea();
    std::string locationStr = this->locationLineEdit->text().toStdString();
    std::vector<std::string> locationVec = third_tokenize(locationStr, ';');
    try {
        emit this->buildingsModel->layoutAboutToBeChanged();
        emit this->parkModel->layoutChanged();
        this->srv.addBuilding(id, description, thematicSector, locationVec);
        emit this->buildingsModel->layoutChanged();
        emit this->parkModel->layoutChanged();
    }
    catch (std::runtime_error& re) {
        QMessageBox::critical(this, "Error", re.what());
    }

}

void EthnologistWindow::guiUpdateBuilding() {
    int id = this->idLineEdit->text().toInt();
    std::string description = this->descriptionLineEdit->text().toStdString();
    std::string thematicSector = this->srv.findEthnologistByName(this->ethnologistName).getThematicArea();
    std::string locationStr = this->locationLineEdit->text().toStdString();
    std::vector<std::string> locationVec = third_tokenize(locationStr, ';');

    Building foundBuilding = this->srv.srvFindBuildingById(id);
    Ethnologist foundEthnologist = this->srv.findEthnologistByName(this->ethnologistName);

    if (foundBuilding.getThematicArea() != foundEthnologist.getThematicArea()) {
        QMessageBox::critical(this, "Error", "You can only update your own buildings!");
        return;
    }

    try {
        emit this->buildingsModel->layoutAboutToBeChanged();
        emit this->parkModel->layoutAboutToBeChanged();
        this->srv.updateBuilding(id, description, thematicSector, locationVec);
        emit this->buildingsModel->layoutChanged();
        emit this->parkModel->layoutChanged();
    }
    catch (std::runtime_error& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}
