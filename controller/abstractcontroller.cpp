#include "abstractcontroller.h"

AbstractController::AbstractController()
{

}

AbstractController::~AbstractController()
{

}

void AbstractController::registerView(unique_ptr<AbstractView>view)
{
    this->view = std::move(view);
}







