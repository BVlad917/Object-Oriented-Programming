//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_PARK_MODEL_H
#define E2_BVLAD917_PARK_MODEL_H

#include <QAbstractTableModel>
#include "../business/service.h"

class ParkModel: public QAbstractTableModel {
private:
    Service& srv;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
public:
    explicit ParkModel(Service& srv);
};


#endif //E2_BVLAD917_PARK_MODEL_H
