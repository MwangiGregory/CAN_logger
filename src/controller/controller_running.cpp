#include "controller_states.h"
#define UPDATE_INTERVAL 1000U

StatusCodes RunningState::start()
{
    started = true;
    return StatusCodes::STATE_OK;
}

StatusCodes RunningState::run()
{
    static unsigned long prev_execute_time = millis();
    if (!started)
        start();

    gps_system->feed_gps();

    if (millis() - prev_execute_time > UPDATE_INTERVAL)
    {
        String rtc_res = rtc_system->get_timestamp();
        Serial.print(rtc_res.c_str());
        Serial.print(" ");

        String gps_loc = gps_system->get_location_str();
        Serial.print(gps_loc.c_str());
        Serial.print(" ");

        CAN_message msg;
        can_system->read_can_message(&msg);
        CAN_Service::pretty_print_can_message(&msg);
        Serial.println();

        prev_execute_time = millis();
    }

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
