#ifndef CONTROLLER_H
#define CONTROLLER_H

class ControllerState;

enum class ControllerErrorCode
{
    CONTROLLER_OK,
    CONTROLLER_INIT_ERROR
};

class Controller
{
private:
    Controller() {}

public:
    ~Controller() {}
    ControllerErrorCode start();
    ControllerErrorCode stop();
    ControllerErrorCode run();
    static Controller *get_instance();
    void set_controller_state(ControllerState *new_state);

private:
    ControllerState *controller_state;
};

#endif /* CONTROLLER_H */