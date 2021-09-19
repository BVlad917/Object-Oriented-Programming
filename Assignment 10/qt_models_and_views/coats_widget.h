//
// Created by VladB on 02-Jun-21.
//

#ifndef A10_BVLAD917_1_COATS_WIDGET_H
#define A10_BVLAD917_1_COATS_WIDGET_H


#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>

class CoatsWidget: public QWidget {
Q_OBJECT

private:
    QVBoxLayout* widget_layout{};
    QTableView* coats_table_view{};
    QAbstractItemModel* table_model{};

    void init_coats_widget();

public:
    explicit CoatsWidget(QAbstractItemModel* model);

    void update_table_columns_width();

};


#endif //A10_BVLAD917_1_COATS_WIDGET_H
