#include "inventorydb.h"

InventoryDb& InventoryDb::getInstance() {
    static InventoryDb instance;
    return instance;
}

InventoryDb::InventoryDb() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(":memory:");
    if (!m_db.open()) {
        qDebug() << m_db.lastError();
    }

    QSqlQuery query;
    if(!query.exec("create table thing("
                   "type int primary key, "
                   "pathToImage varchar(255), "
                   "pathToSound varchar(255))")) {
        qDebug() << query.lastError();
    }

    if(!query.exec("create table inventory("
               "row int, "
               "column int, "
               "count int, "
               "type int, "
               "constraint pkIneventory primary key (row, column), "
               "foreign key (type) references thing(type))")) {
        qDebug() << query.lastError();
    }

    addNewThingType(static_cast<Thing::Type>(1), ":/images/apple.jpg", ":/sound/biteoff.mp3");
    addNewThingType(static_cast<Thing::Type>(2), ":/images/pear.jpg", ":/sound/biteoff.mp3");
}

ThingCount InventoryDb::getThingFromInventory(const QPoint &index) {
    QSqlQuery query;
    query.prepare("select type, count, pathToImage, pathToSound from"
                  "(select * from inventory join thing on thing.type = inventory.type)"
                  "where row = :row and column = :column");
    query.bindValue(":row", index.x());
    query.bindValue(":column", index.y());

    ThingCount thingcount;
    if(!query.exec()) {
        qDebug() << query.lastError();
        return thingcount;
    }

    query.next();
    if(query.isValid()) {
        Thing::Type type = static_cast<Thing::Type>(query.value("type").toInt());
        QString pathToImage = query.value("pathToImage").toString();
        QString pathToSound = query.value("pathToSound").toString();
        size_t count = query.value("count").toInt();
        thingcount = ThingCount(Thing(type, pathToImage, pathToSound), count);
    }

    return thingcount;
}

bool InventoryDb::addThingToInventory(const QPoint &index, const Thing::Type &type,
                                      size_t count) {
    QSqlQuery query;
    query.prepare("insert into inventory values((:row), (:column),"
                                                "(:count), (:type))");
    query.bindValue(":row", index.x());
    query.bindValue(":column", index.y());
    query.bindValue(":count", static_cast<unsigned>(count));
    query.bindValue(":type", static_cast<int>(type));

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool InventoryDb::removeThingFromInventory(const QPoint &index) {
    QSqlQuery query;
    query.prepare("delete from inventory where row = (:row) and column = (:column)");
    query.bindValue(":row", index.x());
    query.bindValue(":column", index.y());

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool InventoryDb::moveThing(const QPoint &oldIndex, const QPoint &newIndex) {
    QSqlQuery query;
    query.prepare("update inventory set row = :newRow, column = :newColumn where row = :oldRow and column = :oldColumn");
    query.bindValue(":oldRow", oldIndex.x());
    query.bindValue(":oldColumn", oldIndex.y());
    query.bindValue(":newRow", newIndex.x());
    query.bindValue(":newColumn", newIndex.y());

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool InventoryDb::changeThingCount(const QPoint &index, size_t newCount) {
    QSqlQuery query;
    query.prepare("update inventory set count = :newCount where row = :row and column = :column");
    query.bindValue(":row", index.x());
    query.bindValue(":column", index.y());
    query.bindValue(":newCount", static_cast<unsigned>(newCount));

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool InventoryDb::addNewThingType(const Thing::Type &type, const QString &pathToImage,
                                  const QString &pathToSound) {
    QSqlQuery query;
    query.prepare("insert into thing values((:type), (:pathToImage), (:pathToSound))");
    query.bindValue(":type", static_cast<int>(type));
    query.bindValue(":pathToImage", pathToImage);
    query.bindValue(":pathToSound", pathToSound);

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

size_t InventoryDb::getTypesCount() {
    QSqlQuery query;
    query.prepare("select count(*) from thing");

    size_t count = 0;
    if(!query.exec()) {
        qDebug() << query.lastError();
        return count;
    }
    query.next();
    if(query.isValid()) {
        count = query.value(0).toInt();
    }
    return count;
}

QString InventoryDb::getPathToImage(const Thing::Type &type) {
    QSqlQuery query;
    query.prepare("select pathToImage from thing where type = :type");
    query.bindValue(":type", static_cast<int>(type));

    QString result = "";
    if(!query.exec()) {
        qDebug() << query.lastError() << "InventoryDb::getPathToImage";
        return result;
    }
    query.next();
    if(query.isValid()) {
        result = query.value("pathToImage").toString();
    }
    return result;
}
