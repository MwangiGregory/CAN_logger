#include <Arduino.h>
#include "controller/controller.h"
#include "controller/controller_states.h"

Controller *controller = nullptr;

void setup()
{
  Serial.begin(115200);
  controller = Controller::get_instance();
  controller->set_controller_state(BootingState::get_state_instance());
  controller->start();
}

void loop()
{
  controller->run();
}