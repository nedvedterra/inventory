#ifndef THINGSLISTMODEL_H
#define THINGSLISTMODEL_H

#include <QAbstractListModel>
#include "inventorydb.h"

class ThingsListModel : public QAbstractListModel {
public:
    ThingsListModel(size_t size, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;

private:
    size_t m_size;
    mutable InventoryDb m_db;
};

#endif // THINGSLISTMODEL_H
