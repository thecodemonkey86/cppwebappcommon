#include "htmlselect.h"
using namespace QtCommon2;

HtmlSelect::HtmlSelect() : HtmlTag(QStringLiteral("select"))
{

}

HtmlSelect::~HtmlSelect()
{

}

HtmlSelect &HtmlSelect::option(const QString &value, const QString &display)
{
    selectOptions.push_back(HtmlSelectOption(value,display));
    return *this;
}

HtmlSelect &HtmlSelect::options(const vector<QPair<QString, QString> > &options)
{
    for(const QPair<QString, QString>&o:options) {
        selectOptions.push_back(HtmlSelectOption(o.first,o.second));
    }
    return *this;
}

HtmlSelect &HtmlSelect::options(const QVector<HtmlSelectOption> &options)
{
    for(const HtmlSelectOption&o:options) {
        selectOptions.push_back(o);
    }
    return *this;
}

HtmlSelect &HtmlSelect::options(const QStringList &values, const QStringList &display)
{
    if (values.size() != display.size()) {
        throw QtException(QStringLiteral("illegal argument"));
    }
    for(int i=0;i<values.size();i++) {
        selectOptions.push_back(HtmlSelectOption(values[i],display[i]));
    }
    return *this;
}

HtmlSelect &HtmlSelect::options(const QHash<QString, QString> &options)
{
    for(auto it=options.begin();it != options.end(); ++it) {
        selectOptions.push_back(HtmlSelectOption(it.key(),it.value()));
    }
     return *this;
}

HtmlSelect &HtmlSelect::options(const QMap<QString, QString> &options)
{
    for(auto it=options.begin();it != options.end(); ++it) {
        selectOptions.push_back(HtmlSelectOption(it.key(),it.value()));
    }
     return *this;
}





void HtmlSelect::renderChildren() const
{
    for(const HtmlSelectOption&o:selectOptions) {
        o.render();
    }
}
