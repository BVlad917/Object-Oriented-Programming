//
// Created by VladB on 02-Jun-21.
//

#include "coats_table_model.h"

CoatsTableModel::CoatsTableModel(Service &srv): srv{srv} {

}

int CoatsTableModel::rowCount(const QModelIndex &parent) const {
    return (int) this->srv.get_all_trenches_from_shopping_cart().size();
}

int CoatsTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant CoatsTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    if (row >= this->srv.get_all_trenches_from_shopping_cart().size()) {
        return QVariant();
    }
    TrenchCoat current_coat = this->srv.get_all_trenches_from_shopping_cart()[row];
    std::string size = current_coat.get_trench_size();
    std::string colour = current_coat.get_trench_colour();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
            case 0:
                return QString::fromStdString(size + "_" + colour);
            case 1:
                return QString::fromStdString(current_coat.get_trench_size());
            case 2:
                return QString::fromStdString(current_coat.get_trench_colour());
            case 3:
                return QString::number(current_coat.get_trench_price());
            case 4:
                return QString::number(current_coat.get_trench_quantity());
            case 5:
                return QString::fromStdString(current_coat.get_trench_photograph());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant CoatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Coat Picture");
                case 1:
                    return QString("Size");
                case 2:
                    return QString("Colour");
                case 3:
                    return QString("Price");
                case 4:
                    return QString("Quantity");
                case 5:
                    return QString("Store link");
                default:
                    break;
            }
        } else if (orientation == Qt::Vertical) {
            return QString::number(section + 1);
        }
    }
    return QVariant();
}

Qt::ItemFlags CoatsTableModel::flags(const QModelIndex &index) const {
    int row = index.row();
    int column = index.column();
    if (column >= 1) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    } else {
        return Qt::ItemIsEnabled;
    }
}
