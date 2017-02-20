#ifndef INVENTORYTABLEMODEL_H
#define INVENTORYTABLEMODEL_H

#include "inventorydb.h"

#include <QAbstractTableModel>
#include <QtWidgets>
#include <QMediaPlayer>

class InventoryTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    InventoryTableModel(const QSize &size, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                         int, int, const QModelIndex &) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                      int column, const QModelIndex &parent);
    bool internalMoveProcess(const QPoint &source, const QPoint &destination);
    bool outsideDropProcess(const QPoint &destination, const Thing::Type &type);
private slots:
    void onRightClick(const QModelIndex &index);
private:
    QSize m_size;
    mutable InventoryDb m_db;
    QMediaPlayer m_mp;
};

#endif // INVENTORYTABLE_H
