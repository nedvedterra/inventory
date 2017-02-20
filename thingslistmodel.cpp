#include "thingslistmodel.h"
#include "thing.h"

ThingsListModel::ThingsListModel(size_t size, QObject *parent) :
    QAbstractListModel(parent), m_size(size), m_db(InventoryDb::getInstance()) {
    //empty
}

int ThingsListModel::rowCount(const QModelIndex &) const {
    return static_cast<int>(m_size);
}

QVariant ThingsListModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }
    if(index.row() >= static_cast<int>(m_size)) {
        return QVariant();
    }

    int type = index.row() + 1;
    QString pathToImage = m_db.getPathToImage(static_cast<Thing::Type>(type));
    if(role == Qt::BackgroundRole) {
        return QVariant(QPixmap(pathToImage).scaled(QSize(Thing::IMAGE_SIZE, Thing::IMAGE_SIZE)));
    }
    return QVariant();
}

Qt::ItemFlags ThingsListModel::flags(const QModelIndex &index) const {
    if(!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled;
}

QMimeData* ThingsListModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if(index.isValid()) {
            stream << (index.row() + 1);
        }
    }

    mimeData->setData("application/thing", encodedData);
    return mimeData;
}

