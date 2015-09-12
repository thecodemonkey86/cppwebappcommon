#include "abstractcontroller.h"

AbstractController::AbstractController()
{

}

AbstractController::~AbstractController()
{

}

void AbstractController::registerView(const shared_ptr<AbstractView>&view)
{
    this->view = view;
}

shared_ptr<AbstractView> AbstractController::getView() const
{
    return view;
}




