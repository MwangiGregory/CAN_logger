#ifndef SERVICE_H
#define SERVICE_H

#include "application.h"

class Service
{
public:
    virtual ErrorCode StartService() = 0;
    virtual ErrorCode StopService() = 0;
};

class CAN_Service : public Service
{
public:
    CAN_Service(uint8_t spi_bus = VSPI, uint8_t cs_pin = MCP_CS);
    ErrorCode StartService();
    ErrorCode StopService();
    ErrorCode ReadMsg(CAN_message *can_msg);
    ErrorCode SendMsg(CAN_message *can_msg);
    static void PrintCanMessage(CAN_message *can_msg);

private:
    SPIClass CAN_SPI;
    MCP_CAN CAN0;
};
#endif