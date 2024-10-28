#include "controller_states.h"

StatusCodes ErrorState::start()
{
    return StatusCodes::STATE_OK;
}

StatusCodes ErrorState::run()
{
    return StatusCodes::STATE_OK;
}

StatusCodes ErrorState::stop()
{
    return StatusCodes::STATE_OK;
}

ErrorState *ErrorState::get_state_instance()
{
    static ErrorState instance;
    return &instance;
}
