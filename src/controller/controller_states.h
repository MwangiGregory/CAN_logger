#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "../services/service.h"
#include "controller/controller.h"

enum class StatusCodes
{
    STATE_OK,
    // STATE_STOPPED, // stopped
    STATE_ERROR, // error condition
    STATE_CAN_ERROR
};

class ControllerState
{
public:
    virtual StatusCodes start();
    virtual StatusCodes run();
    virtual StatusCodes stop();
    void set_controller(Controller *new_controller)
    {
        if (new_controller == nullptr)
        {
            // TODO: use some debug print statements
            return;
        }
        this->controller = new_controller;
        return;
    }

protected:
    Controller *controller;
    const char *state_name = "";
};

class MockState : public ControllerState
{
private:
    MockState()
    {
        this->state_name = "MockState";
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static MockState *get_state_instance();
};

class BootingState : public ControllerState
{
private:
    BootingState()
    {
        this->state_name = "BootingState";
        this->can_system = CAN_Service::get_service_instance();
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static BootingState *get_state_instance();

private:
    CAN_Service *can_system = nullptr;
};

#endif /* CONTROLLER_STATE_H */