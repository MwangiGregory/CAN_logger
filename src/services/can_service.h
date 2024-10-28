#ifndef CAN_SERVICE_H
#define CAN_SERVICE_H

#include "service.h"
#include "application.h"

struct CAN_message
{
    uint32_t can_id = 0;
    uint8_t can_data_length = 0;
    bool extended = false;
    bool rtr = false;
    uint8_t can_data[8] = {0};
};

class CAN_Service : public Service
{
private:
    CAN_Service(uint8_t spi_bus = VSPI, uint8_t cs_pin = MCP_CS);

public:
    Error start_service();
    Error stop_service();
    Error read_can_message(CAN_message *can_msg);
    Error send_can_message(CAN_message *can_msg);
    static CAN_Service *get_service_instance();
    static void pretty_print_can_message(CAN_message *can_msg);

private:
    SPIClass CAN_SPI;
    MCP_CAN CAN0;
};

#endif /* CAN_SERVICE_H */