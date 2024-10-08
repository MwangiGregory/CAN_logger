#include "application.h"

void RTC_init(RTC_DS3231 &rtc, TwoWire &wire)
{
    wire.setPins(RTC_SDA, RTC_SCL);

    while (!rtc.begin(&wire))
    {
        Serial.println("RTC init failed");
        // Serial.flush();
        delay(1000);
    }

    Serial.println("RTC init successful");
}

void GPS_init(HardwareSerial &gps_serial)
{
    gps_serial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
}

void SD_init(SDFS &sd, SPIClass &sd_spi)
{
    sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

    while (!sd.begin(SD_CS, sd_spi))
    {
        Serial.println("Card init failed");
        delay(1000);
    }

    Serial.println("Card init successful");
}

void CAN_init(MCP_CAN &can, SPIClass &can_spi)
{
    can_spi.begin(MCP_SCK, MCP_MISO, MCP_MOSI, MCP_CS);

    if (can.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
        Serial.println("MCP2515 init successful!");
    else
    {
        while (true)
        {
            Serial.println("MCP2515 init failed");
            delay(1000);
        }
    }

    can.setMode(MCP_NORMAL);
    pinMode(MCP_CS, OUTPUT);
    digitalWrite(MCP_CS, LOW);
}