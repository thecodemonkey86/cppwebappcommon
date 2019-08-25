#include "pagemanager.h"

#include <exception/qtexception.h>

using namespace QtCommon2;


void PageManager::runController(const QString&page, FCGX_Stream * outStream, RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader *httpHeader, const QSqlDatabase & sqlCon)
{
     this->pages[page]->run(requestData,sessionData,serverData,httpHeader,sqlCon,outStream);
}

bool PageManager::hasPageForPath(const QString &path) const
{
    return this->pages.contains(path);
}
