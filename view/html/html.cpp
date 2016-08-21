#include "html.h"

Html::Html()
{

}

HtmlSelect Html::select()
{
    return HtmlSelect();
}

HtmlSelectOption Html::option(const QString &value, const QString &display)
{
    return HtmlSelectOption(value,display);
}
