#include "thingcount.h"

ThingCount::ThingCount(const Thing &thing, size_t count) : m_thingCount(thing, count) {
    //empty
}

const Thing& ThingCount::thing() const {
    return m_thingCount.first;
}

size_t ThingCount::count() const {
    return m_thingCount.second;
}

bool ThingCount::isTypesMatch(const Thing::Type &type) const {
    return m_thingCount.first.type() == type;
}

bool ThingCount::isEmpty() const {
    return m_thingCount.second == 0;
}
