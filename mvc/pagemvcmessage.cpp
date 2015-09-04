#include "pagemvcmessage.h"


PageMvcMessage * PageMvcMessage::setSource(AbstractPageController *value)
{
    source = value;
    return this;
}

AbstractPageController *PageMvcMessage::getSource() const
{
    return source;
}
PageMvcMessage::PageMvcMessage()
{

}

