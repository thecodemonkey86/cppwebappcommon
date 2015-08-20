#include "postdata.h"
#include "requestdata.h"

PostData::PostData()
{

}

QString PostData::string(const QString &name)
{
    return RequestData::postString(name);
}

int PostData::integer(const QString &name)
{
    return RequestData::postInt(name);
}

double PostData::dbl(const QString &name)
{
    return RequestData::postDouble(name);
}

