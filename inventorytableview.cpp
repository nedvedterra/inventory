#include "inventorytableview.h"

InventoryTableView::InventoryTableView(QWidget *parent) : QTableView(parent) {
    //empty
}

void InventoryTableView::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::RightButton) {
        emit rightClicked(indexAt(event->pos()));
    }
    else {
        QTableView::mousePressEvent(event);
    }
}
