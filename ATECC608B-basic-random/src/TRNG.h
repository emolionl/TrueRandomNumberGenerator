//#ifndef TRNG_H
//#define TRNG_H
//
//#include <Arduino.h>
//
//class TRNG {
//public:
//  TRNG();
//  uint8_t singleDigit();
//  uint8_t getRandom(byte* data, size_t length);
//
//private:
//  uint8_t wakeup();
//  uint8_t idle();
//  uint8_t sendCommand(uint8_t opcode, uint8_t param1, uint16_t param2);
//  uint8_t receiveResponse(byte* response, size_t length);
//  uint16_t crc16(const byte data[], size_t length);
//};
//
//#endif
#ifndef TRNG_H
#define TRNG_H

#include <Arduino.h>
#include <Wire.h>

class TRNG {
public:
  TRNG();
  uint8_t getRandomInRange(uint8_t minValue, uint8_t maxValue);

private:
  uint8_t getRandom(byte* data, size_t length);
  uint8_t wakeup();
  uint8_t idle();
  uint8_t sendCommand(uint8_t opcode, uint8_t param1, uint16_t param2);
  uint8_t receiveResponse(byte* response, size_t length);
  uint16_t crc16(const byte data[], size_t length);
};

#endif
