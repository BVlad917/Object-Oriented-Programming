//
// Created by VladB on 22-Jun-21.
//

#include "buildings_model.h"

BuildingsModel::BuildingsModel(Service &srv): srv{srv} {}

int BuildingsModel::rowCount(const QModelIndex &parent) const {
    return (int) this->srv.srvGetAllBuildings().size();
}

int BuildingsModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant BuildingsModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    if (row >= this->srv.srvGetAllBuildings().size()) {
        return QVariant();
    }
    Building currentBuilding = this->srv.srvGetAllBuildings()[row];
    std::string location;
    for (const auto& loc: currentBuilding.getLocation()) {
        location += loc;
        location += ";";
    }
    location = location.substr(0, location.size()-1);
    if (role == Qt::DisplayRole) {
        switch (column) {
            case 0:
                return QString::number(currentBuilding.getId());
            case 1:
                return QString::fromStdString(currentBuilding.getDescription());
            case 2:
                return QString::fromStdString(currentBuilding.getThematicArea());
            case 3:
                return QString::fromStdString(location);
            default:
                break;
        }
    }
    return QVariant();
}

QVariant BuildingsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("ID");
                case 1:
                    return QString("Description");
                case 2:
                    return QString("Thematic Area");
                case 3:
                    return QString("Location");
                default:
                    break;
            }
        } else if (orientation == Qt::Vertical) {
            return section + 1;
        }
    }
    return QVariant();
}
