#include "TRNG.h"

#define ATECC608B_ADDRESS 0x60
#define ATECC608B_WAKEUP_FREQ 100000
#define ATECC608B_NORMAL_FREQ 1000000

TRNG::TRNG() {
  Wire.begin();
}

uint8_t TRNG::getRandomInRange(uint8_t minValue, uint8_t maxValue) {
  if (minValue > maxValue) {
    return 0;
  }

  uint32_t fullRandomNumber;
  uint8_t result;
  uint8_t range = maxValue - minValue + 1;
  uint32_t maxValidValue = UINT32_MAX - (UINT32_MAX % range);

  do {
    result = getRandom((byte*)&fullRandomNumber, sizeof(fullRandomNumber));
    if (!result) {
      return 0;
    }
  } while (fullRandomNumber > maxValidValue);

  return (fullRandomNumber % range) + minValue;
}

uint8_t TRNG::getRandom(byte* data, size_t length) {
  if (!wakeup()) {
    return 0;
  }

  while (length) {
    if (!sendCommand(0x1B, 0x00, 0x0000)) {
      return 0;
    }

    delay(23);

    byte response[32];

    if (!receiveResponse(response, sizeof(response))) {
      return 0;
    }

    int copyLength = min(32, (int)length);
    memcpy(data, response, copyLength);

    length -= copyLength;
    data += copyLength;
  }

  delay(1);

  idle();

  return 1;
}

uint8_t TRNG::wakeup() {
  Wire.setClock(ATECC608B_WAKEUP_FREQ);
  Wire.beginTransmission(0x00);
  Wire.endTransmission();

  delayMicroseconds(1500);

  byte response;

  if (!receiveResponse(&response, sizeof(response)) || response != 0x11) {
    return 0;
  }

  Wire.setClock(ATECC608B_NORMAL_FREQ);

  return 1;
}

uint8_t TRNG::idle() {
  Wire.beginTransmission(ATECC608B_ADDRESS);
  Wire.write(0x02);

  if (Wire.endTransmission() != 0) {
    return 0;
  }

  delay(1);

  return 1;
}

uint8_t TRNG::sendCommand(uint8_t opcode, uint8_t param1, uint16_t param2) {
  int commandLength = 8; // 1 for type, 1 for length, 1 for opcode, 1 for param1, 2 for param2, 2 for crc
  byte command[commandLength];

  command[0] = 0x03;
  command[1] = sizeof(command) - 1;
  command[2] = opcode;
  command[3] = param1;
  memcpy(&command[4], &param2, sizeof(param2));

  uint16_t crc = crc16(&command[1], commandLength - 3);
  memcpy(&command[6], &crc, sizeof(crc));

  Wire.beginTransmission(ATECC608B_ADDRESS);
  Wire.write(command, commandLength);
  if (Wire.endTransmission() != 0) {
    return 0;
  }

  return 1;
}

uint8_t TRNG::receiveResponse(byte* response, size_t length) {
  int retries = 20;
  size_t responseSize = length + 3;
  byte responseBuffer[responseSize];
  while (Wire.requestFrom((uint16_t)ATECC608B_ADDRESS, (uint8_t)responseSize, (bool)true) != responseSize && retries--);
  responseBuffer[0] = Wire.read();
  if (responseBuffer[0] != responseSize) return 0;
  for (size_t i = 1; Wire.available(); i++) {
    responseBuffer[i] = Wire.read();
  }
  uint16_t responseCrc = responseBuffer[length + 1] | (responseBuffer[length + 2] << 8);
  if (responseCrc != crc16(responseBuffer, responseSize - 2)) {
    return 0;
  }
  memcpy(response, &responseBuffer[1], length);
  return 1;
}

uint16_t TRNG::crc16(const byte data[], size_t length) {
  if (data == NULL || length == 0) {
    return 0;
  }

  uint16_t crc = 0;

  while (length) {
    byte b = *data;

    for (uint8_t shift = 0x01; shift > 0x00; shift <<= 1) {
      uint8_t dataBit = (b & shift) ? 1 : 0;
      uint8_t crcBit = crc >> 15;

      crc <<= 1;

      if (dataBit != crcBit) {
        crc ^= 0x8005;
      }
    }

    length--;
    data++;
  }

  return crc;
}
