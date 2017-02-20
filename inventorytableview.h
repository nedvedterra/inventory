#ifndef INVENTORYTABLEVIEW_H
#define INVENTORYTABLEVIEW_H

#include <QtWidgets>

class InventoryTableView : public QTableView {
    Q_OBJECT
public:
    InventoryTableView(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
signals:
    void rightClicked(const QModelIndex &index);
};

#endif // INVENTORYTABLEVIEW_H
