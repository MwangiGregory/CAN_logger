#ifndef SERVICE_H
#define SERVICE_H

#include "application.h"

class Service
{
public:
    virtual ErrorCode start_service() = 0;
    virtual ErrorCode stop_service() = 0;
};

class CAN_Service : public Service
{
private:
    CAN_Service(uint8_t spi_bus = VSPI, uint8_t cs_pin = MCP_CS);

public:
    ErrorCode start_service();
    ErrorCode stop_service();
    ErrorCode read_can_message(CAN_message *can_msg);
    ErrorCode send_can_message(CAN_message *can_msg);
    static CAN_Service *get_service_instance();
    static void pretty_print_can_message(CAN_message *can_msg);

private:
    SPIClass CAN_SPI;
    MCP_CAN CAN0;
};

#endif /* SERVICE_H */