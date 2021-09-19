//
// Created by VladB on 02-Jun-21.
//

#ifndef A10_BVLAD917_1_PICTURE_DELEGATE_H
#define A10_BVLAD917_1_PICTURE_DELEGATE_H


#include <QStyledItemDelegate>

class PictureDelegate: public QStyledItemDelegate {
public:
    explicit PictureDelegate(QWidget* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};


#endif //A10_BVLAD917_1_PICTURE_DELEGATE_H
