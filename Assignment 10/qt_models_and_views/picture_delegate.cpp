//
// Created by VladB on 02-Jun-21.
//

#include <QPainter>
#include "picture_delegate.h"

PictureDelegate::PictureDelegate(QWidget *parent): QStyledItemDelegate(parent) {}

void PictureDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() != 0) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    QString coat = index.model()->data(index, Qt::EditRole).toString();
    if (coat.contains("_")) {
        std::string location = "images/" + coat.toStdString() + ".jpg";
        QPixmap pix_map(QString::fromStdString(location));
        painter->drawPixmap(option.rect, pix_map);
    }
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 0) {
        return {200,200};    // <=> return QSize(32, 32) or return QSize{32, 32}
    }
    return QStyledItemDelegate::sizeHint(option, index);
}
