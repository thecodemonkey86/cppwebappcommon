#include "formhtmltemplate.h"
#include "formtemplate.h"
#include "exception/qtexception.h"


FormHtmlTemplate::FormHtmlTemplate()
{

}

void FormHtmlTemplate::renderSubmitted()
{
        renderHeader();
        FormTemplate * body = dynamic_cast<FormTemplate *>(bodyTemplate);
        if (body == NULL)
            throw new QtException("invalid form template");
        body->renderSubmitted();
        renderFooter();

}

