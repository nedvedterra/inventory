#include "inventorytablemodel.h"
#include "thing.h"

InventoryTableModel::InventoryTableModel(const QSize &size, QObject *parent) :
    QAbstractTableModel(parent), m_size(size), m_db(InventoryDb::getInstance()) {
    //empty
}

int InventoryTableModel::rowCount(const QModelIndex&) const {
    return m_size.width();
}

int InventoryTableModel::columnCount(const QModelIndex&) const {
    return m_size.height();
}

QVariant InventoryTableModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
       return QVariant();
    }
    if(index.row() >= m_size.height() || index.column() >= m_size.width()) {
        return QVariant();
    }

    QPoint point(index.row(), index.column());
    ThingCount thingcount(m_db.getThingFromInventory(point));
    if(thingcount.isEmpty())
        return QVariant();
    else {
        if(role == Qt::TextAlignmentRole) {
            return QVariant(Qt::AlignBottom | Qt::AlignRight);
        }
        else if(role == Qt::DisplayRole) {
            return static_cast<unsigned>(thingcount.count());
        }
        else if(role == Qt::BackgroundRole) {
            QString pathToImage = thingcount.thing().pathToImage();
            return QVariant(QPixmap(pathToImage).scaled(QSize(Thing::IMAGE_SIZE, Thing::IMAGE_SIZE)));
        }
        else {
            return QVariant();
        }
    }
}

Qt::ItemFlags InventoryTableModel::flags(const QModelIndex &index) const {
    if(!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QStringList InventoryTableModel::mimeTypes() const {
    return QStringList() << "application/table";
}
bool InventoryTableModel::canDropMimeData(const QMimeData *data, Qt::DropAction,
                                          int, int, const QModelIndex&) const {
    if(data->hasFormat("application/thing")
       || data->hasFormat("application/table")) {
        return true;
    }
    return false;
}

bool InventoryTableModel::dropMimeData(const QMimeData *data, Qt::DropAction,
                                       int rowDest, int columnDest, const QModelIndex &parent) {
    if(rowDest == -1)
        rowDest = parent.row();
    if(columnDest == -1)
        columnDest = parent.column();

    if(data->hasFormat("application/table")) {
        QByteArray encoded = data->data("application/table");
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        while(!stream.atEnd()) {
            int rowSrc, columnSrc;
            QMap<int, QVariant> roleDataMap;
            stream >> rowSrc >> columnSrc >> roleDataMap;
            return internalMoveProcess(QPoint(rowSrc, columnSrc),
                                       QPoint(rowDest, columnDest));
        }
    }
    else if(data->hasFormat("application/thing")) {
        QByteArray encoded = data->data("application/thing");
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        while(!stream.atEnd()) {
            int type;
            stream >> type;
            return outsideDropProcess(QPoint(rowDest, columnDest),
                                      static_cast<Thing::Type>(type));
        }
    }
    return false;
}

bool InventoryTableModel::internalMoveProcess(const QPoint &source,
                                              const QPoint &destination) {
    if(source == destination) {
        return false;
    }
    ThingCount thingInDest = m_db.getThingFromInventory(destination);
    ThingCount thingInSrc = m_db.getThingFromInventory(source);

    if(thingInDest.isEmpty()) {
        m_db.moveThing(source, destination);
        return true;
    }
    else if (thingInSrc.isTypesMatch(thingInDest.thing().type())) {
        m_db.removeThingFromInventory(source);
        size_t newCount = thingInDest.count() + thingInSrc.count();
        m_db.changeThingCount(destination, newCount);
        return true;
    }
    return false;
}

bool InventoryTableModel::outsideDropProcess(const QPoint &destination,
                                             const Thing::Type &type) {
    ThingCount thingInDest = m_db.getThingFromInventory(destination);
    if(thingInDest.isEmpty()) {
        m_db.addThingToInventory(destination, type, 1);
    }
    else if(thingInDest.isTypesMatch(type)) {
        size_t newCount = thingInDest.count() + 1;
        m_db.changeThingCount(destination, newCount);
        return true;
    }
    return false;
}

void InventoryTableModel::onRightClick(const QModelIndex &index) {
    if(index.isValid()) {
        QPoint destination = QPoint(index.row(), index.column());
        ThingCount thingInDest = m_db.getThingFromInventory(destination);
        size_t newCount = thingInDest.count() - 1;
        QString pathToSound = thingInDest.thing().pathToSound();

        if(!pathToSound.isEmpty()) {
            //TODO: check if file exist
            m_mp.setMedia(QUrl("qrc" + pathToSound));
            m_mp.play();
        }
        if(newCount > 0) {
            m_db.changeThingCount(destination, newCount);
        }
        else if(newCount == 0) {
            m_db.removeThingFromInventory(destination);
        }
    }
    emit dataChanged(index, index);
}
