#ifndef MULTIACTIONCONTROLLER_H
#define MULTIACTIONCONTROLLER_H

#include <QMap>
#include "controller/action/action.h"

class MultiActionController
{
protected:
    QMap<QString, Action*> actions;

public:
    MultiActionController();
    void addAction(QString actionName, Action*action);
};

#endif // MULTIACTIONCONTROLLER_H
