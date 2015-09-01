#include "formpost.h"

FormPost::FormPost(const QString&submitFieldName) : Form(submitFieldName)
{

}

FormPost::FormPost() : Form(QString("submit"))
{

}

QString FormPost::stringValue(const QString &name)
{
    return requestData->postString(name);
}


int FormPost::intValue(const QString &name)
{
    return requestData->postInt(name);
}

float FormPost::doubleValue(const QString &name)
{
    return requestData->postDouble(name);
}

bool FormPost::isSubmitted()
{
    return requestData->isPostParamSet(submitFieldName) && !requestData->postString(submitFieldName).isEmpty();
}

FormPost::~FormPost()
{

}

