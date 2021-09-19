//
// Created by VladB on 22-Jun-21.
//

#include "park_model.h"
#include <QColor>

ParkModel::ParkModel(Service &srv): srv{srv} {}

int ParkModel::rowCount(const QModelIndex &parent) const {
    return 5;
}

int ParkModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant ParkModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    if (row >= 5) {
        return QVariant();
    }
    char rowChar = 'A' + row;
    char columnChar = '1' + column;
    std::string theme = this->srv.findThemeForCell(rowChar, columnChar);
    if (role == Qt::BackgroundRole) {
        if (theme == "office") {
            return QColor(Qt::black);
        }
        else if (theme == "houses") {
            return QColor(Qt::red);
        }
        else if (theme == "botanical sector") {
            return QColor(Qt::yellow);
        }
        else if (theme == "workshops") {
            return QColor(Qt::green);
        }
        else if (theme == "farmstead") {
            return QColor(Qt::blue);
        }
    }
    return QVariant();
}
