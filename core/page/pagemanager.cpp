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

QString PageManager::url(QUrl  currentUrl, const RequestParam &addOrUpdateParam)
{
  QChar ampersand('&');
  auto strparams = currentUrl.query();
  auto params = strparams.split(ampersand);
  QStringList newParams;
  newParams.reserve(params.size()+1);
  bool found = false;
  for(auto p : params)
  {
    auto parts = p.split(QChar('='));
    if(parts.length() == 2)
    {
      if(parts[0] == addOrUpdateParam.getName())
      {
        newParams  << QStringLiteral("%1=%2").arg(addOrUpdateParam.getName(),addOrUpdateParam.getPercentEscapedValue());
        found = true;
      } else {
        newParams << p;
      }

    }
  }
  if(!found) {
     newParams  << QStringLiteral("%1=%2").arg(addOrUpdateParam.getName(),addOrUpdateParam.getPercentEscapedValue());
  }
  currentUrl.setQuery(newParams.join(ampersand));
  return currentUrl.toString();
}
