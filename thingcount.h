#ifndef THINGCOUNT_H
#define THINGCOUNT_H

#include "thing.h"
#include <QPair>

class ThingCount {
public:
    ThingCount(const Thing &thing = Thing(), size_t count = 0);

    const Thing& thing() const;
    size_t count() const;
    bool isTypesMatch(const Thing::Type &type) const;
    bool isEmpty() const;
private:
    QPair<Thing, size_t> m_thingCount;
};

#endif // THINGCOUNT_H
