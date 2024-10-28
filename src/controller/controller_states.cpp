#include "controller_states.h"
#include <application.h>

/*  MOCKSTATE   */

MockState *MockState::get_state_instance()
{
    static MockState mock_state;
    return &mock_state;
}

StatusCodes MockState::start()
{
    Serial.printf("Started %s\n", this->state_name);
    return StatusCodes();
}

StatusCodes MockState::run()
{
    Serial.printf("Running %s\n", this->state_name);
    return StatusCodes();
}

StatusCodes MockState::stop()
{
    Serial.printf("Stopped %s\n", this->state_name);
    return StatusCodes();
}

/*  BOOTING */

StatusCodes BootingState::start()
{
    return StatusCodes();
}

StatusCodes BootingState::run()
{
    Error error = can_system->start_service();
    if (error.error_code != ErrCode::NONE)
        ErrorHandler::handle_error(error);

    return StatusCodes::STATE_OK;
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
