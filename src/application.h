#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>
#include <Wire.h>

#include <mcp_can.h>
#include <SPI.h>

#include "FS.h"
#include "SD.h"

#include <TinyGPS++.h>

#include "RTClib.h"

#define BAUD_RATE 115200
#define GPS_BAUD 9600
#define GPS_SERIAL_DEVICE 2

// PINS
#define MCP_CS 27   // SPI Chip Select/Slave Select pin connected to mcp2515
#define MCP_SCK 33  // SPI clock pin connected to mcp2515
#define MCP_MISO 26 // SPI MISO pin connected to mcp2515
#define MCP_MOSI 25 // SPI MOSI pin connected to mcp2515
#define MCP_INT_PIN 2

#define SD_CS 13   // SPI Chip Select/Slave Select pin connected to sd card
#define SD_SCK 14  // SPI clock pin connected to sd card
#define SD_MISO 21 // SPI MISO pin connected to sd card
#define SD_MOSI 19 // SPI MOSI pin connected to sd card

#define RTC_SDA 23
#define RTC_SCL 22

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

struct CAN_message
{
    uint32_t can_id = 0;
    uint8_t can_data_length = 0;
    bool extended = false;
    bool rtr = false;
    uint8_t can_data[8] = {0};
};

void CAN_init(MCP_CAN &can, SPIClass &can_spi);
void SD_init(SDFS &sd, SPIClass &sd_spi);
void RTC_init(RTC_DS3231 &rtc, TwoWire &wire);
void GPS_init(HardwareSerial &gps_serial);

#endif /* APPLICATION_H */