#include "abstractcontroller.h"

AbstractController::AbstractController()
{

}

AbstractController::~AbstractController()
{

}

void AbstractController::registerView(AbstractView *view)
{
    this->view = view;
}

AbstractView *AbstractController::getView() const
{
    return view;
}




