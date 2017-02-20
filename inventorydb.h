#ifndef DB_H
#define DB_H

#include <QtSql>
#include "thing.h"
#include "thingcount.h"

class InventoryDb {
public:
    static InventoryDb& getInstance();
    ThingCount getThingFromInventory(const QPoint &index);
    bool addThingToInventory(const QPoint &index, const Thing::Type &type,
                             size_t count);
    bool removeThingFromInventory(const QPoint &index);
    bool moveThing(const QPoint &oldIndex, const QPoint &newIndex);
    bool changeThingCount(const QPoint &index, size_t newCount);

    bool addNewThingType(const Thing::Type &type, const QString &pathToImage,
                         const QString &pathToSound);
    size_t getTypesCount();
    QString getPathToImage(const Thing::Type &type);

private:
    InventoryDb();
    QSqlDatabase m_db;
};

#endif // DB_H
