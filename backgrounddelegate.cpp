#include "backgrounddelegate.h"

BackgroundDelegate::BackgroundDelegate(QObject *parent): QStyledItemDelegate(parent) {
    //empty
}
void BackgroundDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    QVariant background = index.data(Qt::BackgroundRole);
    if (background.canConvert<QBrush>())
        painter->fillRect(option.rect, background.value<QBrush>());
    QStyledItemDelegate::paint(painter, option, index);
}
