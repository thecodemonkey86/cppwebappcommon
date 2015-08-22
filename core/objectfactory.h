#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QString>
#include "abstractobjectfactory.h"

template<class T>
class ObjectFactory : public AbstractObjectFactory
{
public:
    ObjectFactory();
    T* create() {
        return new T();
    }

    QString getName() {
        return T::getName();
    }
};

#endif // OBJECTFACTORY_H
