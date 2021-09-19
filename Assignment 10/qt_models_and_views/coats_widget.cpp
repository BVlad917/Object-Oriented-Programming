//
// Created by VladB on 02-Jun-21.
//

#include <QGuiApplication>
#include <QScreen>
#include "coats_widget.h"
#include "picture_delegate.h"

CoatsWidget::CoatsWidget(QAbstractItemModel *model): table_model{model} {
    this->init_coats_widget();

    this->coats_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->coats_table_view->setModel(this->table_model);
    this->coats_table_view->setItemDelegate(new PictureDelegate{});
    // A few commands to improve the look of the table
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize((int) ((double) (width / 1.6)), (int) ((double) (height / 1.7)));
}

void CoatsWidget::init_coats_widget() {
    this->setWindowTitle("Shopping Basket");
    this->widget_layout = new QVBoxLayout{this};
    this->coats_table_view = new QTableView{};
    this->widget_layout->addWidget(this->coats_table_view);
}

void CoatsWidget::update_table_columns_width() {
    this->coats_table_view->resizeColumnsToContents();
    this->coats_table_view->resizeRowsToContents();
}
