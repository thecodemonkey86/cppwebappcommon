#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QMap>
#include "controller/action/action.h"

#include "controller/pagecontroller.h"

class MultiActionController : public PageController
{
protected:
    QMap<QString, Action*> actions;

public:
    MultiActionController();
    virtual void run();

    void addAction(QString actionName, Action*action);
};

#endif // MULTIACTIONCONTROLLER_H
