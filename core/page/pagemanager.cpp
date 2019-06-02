#include "pagemanager.h"

#include <exception/qtexception.h>

using namespace QtCommon2;


void PageManager::runController(const QString&page, FCGX_Stream * outStream, RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader *httpHeader, const QSqlDatabase & sqlCon)
{
    if (this->pages.contains(page)) {
        this->pages[page]->run(requestData,sessionData,serverData,httpHeader,sqlCon,outStream);
    } else {
        throw QtException(QStringLiteral("page not found: %1").arg(page));
    }
}
