#include "formpost.h"

FormPost::FormPost(const QString&submitFieldName) : Form(submitFieldName)
{

}

FormPost::FormPost() : Form("submit")
{

}

QString FormPost::stringValue(const QString &name)
{
    return RequestData::postString(name);
}


int FormPost::intValue(const QString &name)
{
    return RequestData::postInt(name);
}

bool FormPost::isSubmitted()
{
    return RequestData::isPostParamSet(submitFieldName) && !RequestData::postString(submitFieldName).isEmpty();
}

