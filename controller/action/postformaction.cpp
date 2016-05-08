#include "postformaction.h"
#include "view/formview.h"

PostFormAction::PostFormAction(const QString&submitFieldName) : FormPost(submitFieldName)
{
}


MvcMessage& PostFormAction::run()
{

    bool submitted = isSubmitted();
    if (submitted) {
        return onSubmit();
    } else {
        return onNonSubmit();
    }
}

AbstractAction *PostFormAction::setRequestData(RequestData *value)
{
    FormPost::setRequestData(value);
    return AbstractAction::setRequestData(value);
}

AbstractAction *PostFormAction::setServerData(ServerData *value)
{
    FormPost::setServerData(value);
    return AbstractAction::setServerData(value);
}


AbstractAction *PostFormAction::setSessionData(SessionData *value)
{
    FormPost::setSessionData(value);
    return AbstractAction::setSessionData(value);
}

