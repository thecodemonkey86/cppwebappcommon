#include "abstracttemplate.h"
#include <iostream>

using namespace std;

AbstractTemplate::AbstractTemplate()
{



}

AbstractTemplate::~AbstractTemplate()
{

}

void AbstractTemplate::update()
{
    this->render();
}

// QFile* AbstractTemplate::f=new QFile("D:\\Temp\\test.html");

 QtCout * AbstractTemplate::outStream = new QtCout();
