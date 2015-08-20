#ifndef ACTION_H
#define ACTION_H
#include "controller/multiactioncontroller.h"

#include <QUrl>

class MultiActionController;

class Action
{
protected:
    MultiActionController*parent;
public:
    Action();
    virtual QString getName()=0;
    virtual void run()=0;
    MultiActionController *getParent() const;
    Action* setParent(MultiActionController *value);
    QUrl getUrl();
};

#endif // ACTION_H
