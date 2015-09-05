#include "postformaction.h"
#include "view/formview.h"

PostFormAction::PostFormAction(const QString&submitFieldName) : FormPost(submitFieldName)
{
}


MvcMessage *PostFormAction::run()
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
    request = value;
    return AbstractAction::setRequestData(value);
}

