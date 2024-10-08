#include "application.h"
#include "service.h"

SPIClass SD_SPI(HSPI);
HardwareSerial gpsSerial(GPS_SERIAL_DEVICE);

RTC_DS3231 rtc;
TinyGPSPlus gps;

CAN_Service can_service;
CAN_message can_msg;

ErrorCode code;

void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.println();

  code = can_service.StartService();
  if (code == ErrorCode::CAN_SERVICE_FAIL)
    Serial.println("CAN Service Initialization Failed\n");

  SD_init(SD, SD_SPI);
  RTC_init(rtc, Wire);
  GPS_init(gpsSerial);

  can_msg.can_id = 0x1805FA20;
  can_msg.extended = true;
  can_msg.can_data_length = 8;
  for (int i = 0; i < 8; i++)
    can_msg.can_data[i] = 0x00;
}

void loop()
{
  // code = can_service.SendMsg(&can_msg);
  // if (code == ErrorCode::CAN_MSG_SEND_SUCCESS)
  //   Serial.println("Message sent successfully");

  if (can_service.ReadMsg(&can_msg) == ErrorCode::NONE)
    CAN_Service::PrintCanMessage(&can_msg);

  delay(500);
}