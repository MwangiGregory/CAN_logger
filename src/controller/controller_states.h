#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "controller/controller.h"
#include "../services/can_service.h"
#include "../services/rtc_service.h"

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

/* ==================== BootingState Class ==================== */

class BootingState : public ControllerState
{
private:
    BootingState()
    {
        this->state_name = "BootingState";
        this->can_system = CAN_Service::get_service_instance();
        this->rtc_system = RTC_service::get_service_instance();
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static BootingState *get_state_instance();

private:
    CAN_Service *can_system = nullptr;
    RTC_service *rtc_system = nullptr;
};

/* ==================== RunningState Class ==================== */

class RunningState : public ControllerState
{
private:
    RunningState()
    {
        this->state_name = "RunningState";
        this->can_system = CAN_Service::get_service_instance();
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static RunningState *get_state_instance();

private:
    CAN_Service *can_system = nullptr;
    RTC_service *rtc_system = nullptr;
};

/* ==================== ErrorState Class ==================== */

class ErrorState : public ControllerState
{
private:
    ErrorState()
    {
        this->state_name = "ErrorState";
        this->can_system = CAN_Service::get_service_instance();
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static ErrorState *get_state_instance();

private:
    CAN_Service *can_system = nullptr;
    RTC_service *rtc_system = nullptr;
};

/* ==================== ShutdownState Class ==================== */

class ShutdownState : public ControllerState
{
private:
    ShutdownState()
    {
        this->state_name = "ShutdownState";
        this->can_system = CAN_Service::get_service_instance();
    }

public:
    StatusCodes start() override;
    StatusCodes run() override;
    StatusCodes stop() override;
    static ShutdownState *get_state_instance();

private:
    CAN_Service *can_system = nullptr;
    RTC_service *rtc_system = nullptr;
};

#endif /* CONTROLLER_STATE_H */