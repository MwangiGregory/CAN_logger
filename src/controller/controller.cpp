#include "controller.h"
#include "controller_states.h"

ControllerErrorCode Controller::run()
{
    this->controller_state->run();
    return ControllerErrorCode::CONTROLLER_OK;
}

ControllerErrorCode Controller::start()
{
    this->controller_state->start();
    return ControllerErrorCode::CONTROLLER_OK;
}

ControllerErrorCode Controller::stop()
{
    this->controller_state->stop();
    return ControllerErrorCode::CONTROLLER_OK;
}

void Controller::set_controller_state(ControllerState *new_state)
{
    if (new_state == nullptr)
    {
        // TODO: print debug message
        return;
    }
    this->controller_state = new_state;
    this->controller_state->set_controller(this);

    return;
}

Controller *Controller::get_instance()
{
    static Controller controller{};
    return &controller;
}