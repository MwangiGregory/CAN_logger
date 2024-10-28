#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "controller/controller.h"
#include "../services/can_service.h"
#include "../services/rtc_service.h"
#include <array>

enum class StatusCodes
{
    STATE_OK,
    // STATE_STOPPED, // stopped
    STATE_ERROR, // error condition
    STATE_CAN_ERROR
};

/* ==================== ControllerState Class ==================== */

class ControllerState
{
protected:
    ControllerState() {}

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
    bool started = false;
    const char *state_name = "";
    Controller *controller;

    // For now, add any new service pointer declaration here, then add a definition in the controller_booting.cpp
    // and then create the service in the BootingState::create_services() method
    static CAN_Service *can_system;
    static RTC_service *rtc_system;
};

/* ==================== BootingState Class ==================== */

class BootingState : public ControllerState
{
private:
    BootingState()
    {
        this->state_name = "BootingState";
    }

    void create_services();
    void create_controller_states();

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static BootingState *get_state_instance();
};

/* ==================== RunningState Class ==================== */

class RunningState : public ControllerState
{
private:
    RunningState()
    {
        this->state_name = "RunningState";
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static RunningState *get_state_instance();

    // private:
    //     CAN_message msg;
};

/* ==================== ErrorState Class ==================== */

class ErrorState : public ControllerState
{
private:
    ErrorState()
    {
        this->state_name = "ErrorState";
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static ErrorState *get_state_instance();
};

/* ==================== ShutdownState Class ==================== */

class ShutdownState : public ControllerState
{
private:
    ShutdownState()
    {
        this->state_name = "ShutdownState";
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static ShutdownState *get_state_instance();
};

#endif /* CONTROLLER_STATE_H */