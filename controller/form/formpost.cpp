#include "formpost.h"

FormPost::FormPost(const QString&submitFieldName) : Form(submitFieldName)
{

}


QString FormPost::stringValue(const QString &name)
{
    return request->postString(name);
}


int FormPost::intValue(const QString &name)
{
    return request->postInt(name);
}

float FormPost::doubleValue(const QString &name)
{
    return request->postDouble(name);
}

bool FormPost::isSubmitted()
{
    return request->isPostParamSet(submitFieldName) && !request->postString(submitFieldName).isEmpty();
}

FormPost::~FormPost()
{

}

