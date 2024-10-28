#include "controller_states.h"

StatusCodes ShutdownState::start()
{
    return StatusCodes::STATE_OK;
}

StatusCodes ShutdownState::run()
{
    return StatusCodes::STATE_OK;
}

StatusCodes ShutdownState::stop()
{
    return StatusCodes::STATE_OK;
}

ShutdownState *ShutdownState::get_state_instance()
{
    static ShutdownState instance;
    return &instance;
}
