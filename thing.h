#ifndef THING_H
#define THING_H

#include <QString>

class Thing {
public:
    enum class Type {None, Apple, Pear};
    static const size_t IMAGE_SIZE = 100;

    Thing(Type type = Type::None, const QString &pathToImage = "",
          const QString &pathToSound = "");
    Type type() const;
    const QString& pathToImage() const;
    const QString& pathToSound() const;

private:
    Type m_type;
    QString m_pathToImage;
    QString m_pathToSound;
};

#endif // THING_H
