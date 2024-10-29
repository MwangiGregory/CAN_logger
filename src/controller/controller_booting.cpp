#include "controller_states.h"

// Definition of static variables inherited from ControllerState
CAN_Service *ControllerState::can_system = nullptr;
RTC_service *ControllerState::rtc_system = nullptr;
GPS_Service *ControllerState::gps_system = nullptr;

void BootingState::create_services()
{
    ControllerState::can_system = CAN_Service::get_service_instance();
    ControllerState::rtc_system = RTC_service::get_service_instance();
    ControllerState::gps_system = GPS_Service::get_service_instance();
}

StatusCodes BootingState::start()
{
    started = true;
    create_services();
    create_controller_states();

    // maybe allocate an array to store service pointers for initialization, then destroy it when switching
    // to another state

    Error error = can_system->start_service();
    if (error.error_code != ErrCode::NONE)
        ErrorHandler::handle_error(error);

    error = rtc_system->start_service();
    if (error.error_code != ErrCode::NONE)
        ErrorHandler::handle_error(error);

    error = gps_system->start_service();
    if (error.error_code != ErrCode::NONE)
        ErrorHandler::handle_error(error);

    if (error.error_code != ErrCode::NONE)
        this->controller->set_controller_state(ErrorState::get_state_instance());

    Serial.println(rtc_system->get_timestamp());
    return StatusCodes::STATE_OK;
}

StatusCodes BootingState::run()
{
    if (started == false)
    {
        this->start();
        started = true;
    }

    // transition to the RunningState
    this->controller->set_controller_state(RunningState::get_state_instance());
    return StatusCodes();
}

StatusCodes BootingState::stop()
{
    if (started == false)
        run();
    return StatusCodes();
}

BootingState *BootingState::get_state_instance()
{
    static BootingState booting_state;
    return &booting_state;
}

void BootingState::create_controller_states()
{
    RunningState::get_state_instance();
    ErrorState::get_state_instance();
    ShutdownState::get_state_instance();
}
