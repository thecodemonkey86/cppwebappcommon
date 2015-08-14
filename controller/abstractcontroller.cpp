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



