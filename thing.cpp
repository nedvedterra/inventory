#include "thing.h"

Thing::Thing(Type type, const QString &pathToImage, const QString &pathToSound) :
    m_type(type), m_pathToImage(pathToImage), m_pathToSound(pathToSound) {}

Thing::Type Thing::type() const {
    return m_type;
}

const QString& Thing::pathToImage() const {
    return m_pathToImage;
}

const QString& Thing::pathToSound() const {
    return m_pathToSound;
}
