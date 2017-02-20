#ifndef BACKGROUNDDELEGATE_H
#define BACKGROUNDDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class BackgroundDelegate : public QStyledItemDelegate
{
public:
    BackgroundDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
};

#endif // BACKGROUNDDELEGATE_H
