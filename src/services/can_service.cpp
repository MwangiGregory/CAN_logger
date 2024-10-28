#include "service.h"
#include "application.h"

CAN_Service::CAN_Service(uint8_t spi_bus, uint8_t cs_pin)
    : CAN_SPI{spi_bus}, CAN0{&CAN_SPI, cs_pin}
{
}

Error CAN_Service::start_service()
{
    CAN_SPI.begin(MCP_SCK, MCP_MISO, MCP_MOSI, MCP_CS);
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    {
        CAN0.setMode(MCP_NORMAL);
        pinMode(MCP_INT_PIN, INPUT);
        return Error();
    }
    return Error(ErrCode::INIT_ERROR, ErrLevel::LEVEL_HIGH, "start_service", "can init failed");
}

Error CAN_Service::stop_service()
{
    CAN_SPI.end();
    return Error();
}

// find way to detect message read error
Error CAN_Service::read_can_message(CAN_message *can_msg)
{
    unsigned long can_id;
    bool extended;
    unsigned char can_data_len;
    unsigned char data[8];

    if (!digitalRead(MCP_INT_PIN))
    {
        if (CAN0.readMsgBuf(&can_id, &can_data_len, data) == CAN_NOMSG)
            return Error();

        if ((can_id & 0x80000000) == 0x80000000)
        {
            can_msg->can_id = (uint32_t)(can_id & 0x1FFFFFFF);
            can_msg->extended = true;
        }
        else
        {
            can_msg->can_id = (uint32_t)can_id;
            can_msg->extended = false;
        }

        if ((can_id & 0x40000000) == 0x40000000)
        {
            can_msg->rtr = true;
            memset(can_msg->can_data, 0, 8);
            return Error();
        }
        else
            can_msg->rtr = false;

        can_msg->can_data_length = (uint8_t)can_data_len;
        memcpy(can_msg->can_data, data, can_data_len);

        return Error();
    }

    return Error();
}

Error CAN_Service::send_can_message(CAN_message *can_msg)
{
    digitalWrite(MCP_CS, LOW);

    byte send_status = CAN0.sendMsgBuf(can_msg->can_id, can_msg->extended, can_msg->can_data_length, can_msg->can_data);
    if (send_status == CAN_OK)
        return Error();
    else
        return Error(ErrCode::WRITE_ERROR, ErrLevel::LEVEL_LOW, "send_can_message", "can send failed");
}

CAN_Service *CAN_Service::get_service_instance()
{
    static CAN_Service can_system;
    return &can_system;
}

void CAN_Service::pretty_print_can_message(CAN_message *can_msg)
{
    char msgString[128] = {0};

    if (can_msg->extended == true)
        sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", can_msg->can_id, can_msg->can_data_length);
    else if (can_msg->extended == false)
        sprintf(msgString, "Standard ID: 0x%.3lX  DLC: %1d  Data:", can_msg->can_id, can_msg->can_data_length);

    Serial.print(msgString);
    for (byte i = 0; i < can_msg->can_data_length; i++)
    {
        sprintf(msgString, " 0x%.2X", can_msg->can_data[i]);
        Serial.print(msgString);
    }
    Serial.println();
}
