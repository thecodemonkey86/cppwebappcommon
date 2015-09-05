/*#include "view/template/formhtmltemplate.h"
#include "view/formview.h"
#include "view/template/formtemplate.h"
#include "exception/qtexception.h"


FormHtmlTemplate::FormHtmlTemplate()
{

}

void FormHtmlTemplate::updateSubmitted(MvcMessage*updateMsg)
{
        renderHeader();
        FormTemplate * body = dynamic_cast<FormTemplate *>(bodyTemplate);
        if (body == NULL)
            throw new QtException("invalid form template");
        body->updateSubmitted(updateMsg);
        renderFooter();

}

void FormHtmlTemplate::update(MvcMessage*updateMsg)
{
    renderHeader();
    FormTemplate * body = dynamic_cast<FormTemplate *>(bodyTemplate);
    if (body == NULL)
        throw new QtException("invalid form template");
    body->update(updateMsg);
    renderFooter();
}

*/
