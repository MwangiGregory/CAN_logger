// CAN Send Example

#include <mcp_can.h>
#include <SPI.h>

/*
 * Arduino Uno
 * CS 10
 * SO 12
 * SI 11
 * SCK 13
 * INT 2
 */

// #define MCP_CS 27
// #define MCP_MISO 26
// #define MCP_MOSI 25
// #define MCP_SCK 33

#define MCP_CS 10
// #define MCP_MISO 12
// #define MCP_MOSI 11
// #define MCP_SCK 13

// SPIClass can_spi(VSPI);

// MCP_CAN CAN0(&can_spi, MCP_CS);
MCP_CAN CAN0(MCP_CS);

void setup()
{
  Serial.begin(115200);

  // can_spi.begin(MCP_SCK, MCP_MISO, MCP_MOSI, MCP_CS);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL); // Change to normal mode to allow messages to be transmitted

  // pinMode(MCP_CS, OUTPUT);
  // digitalWrite(MCP_CS, LOW);
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void loop()
{
  digitalWrite(MCP_CS, LOW);

  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  // byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  byte sndStat = CAN0.sendMsgBuf(0x10234567, 1, 8, data);
  if (sndStat == CAN_OK)
  {
    Serial.println("Message Sent Successfully!");
  }
  else
  {
    Serial.println("Error Sending Message...");
  }
  delay(100); // send data per 100ms
}
