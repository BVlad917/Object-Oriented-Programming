//
// Created by VladB on 02-Jun-21.
//

#ifndef A10_BVLAD917_1_COATS_TABLE_MODEL_H
#define A10_BVLAD917_1_COATS_TABLE_MODEL_H


#include <QAbstractTableModel>
#include <service.h>

class CoatsTableModel: public QAbstractTableModel{
private:
    Service& srv;

public:
    explicit CoatsTableModel(Service& srv);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
};


#endif //A10_BVLAD917_1_COATS_TABLE_MODEL_H
