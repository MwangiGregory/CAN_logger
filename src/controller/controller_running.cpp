#include "controller_states.h"

StatusCodes RunningState::start()
{
    started = true;
    return StatusCodes::STATE_OK;
}

StatusCodes RunningState::run()
{
    if (!started)
        start();

    Serial.print(rtc_system->get_timestamp().c_str());
    Serial.print(" ");

    CAN_message msg;
    can_system->read_can_message(&msg);
    CAN_Service::pretty_print_can_message(&msg);
    Serial.println();

    delay(1000U);
    return StatusCodes::STATE_OK;
}

StatusCodes RunningState::stop()
{
    return StatusCodes::STATE_OK;
}

RunningState *RunningState::get_state_instance()
{
    static RunningState instance;
    return &instance;
}
