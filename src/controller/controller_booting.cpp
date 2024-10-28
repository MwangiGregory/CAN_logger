#include "controller_states.h"

StatusCodes BootingState::start()
{
    Error error = can_system->start_service();
    if (error.error_code != ErrCode::NONE)
        ErrorHandler::handle_error(error);

    error = rtc_system->start_service();
    if (error.error_code != ErrCode::NONE)
        ErrorHandler::handle_error(error);

    Serial.println(rtc_system->get_timestamp());
    return StatusCodes::STATE_OK;
}

StatusCodes BootingState::run()
{
    return StatusCodes();
}

StatusCodes BootingState::stop()
{
    return StatusCodes();
}

BootingState *BootingState::get_state_instance()
{
    static BootingState booting_state;
    return &booting_state;
}