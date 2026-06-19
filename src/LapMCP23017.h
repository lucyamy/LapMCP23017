#ifndef LAPMCP23017_H
#define LAPMCP23017_H

#include <Arduino.h>
#include <Wire.h>

#define IODRA 0x00
#define IODRB 0x01
#define IPOLA 0x02
#define IPOLB 0x03
#define IOCON 0x0A 
#define GPPUA 0x0C
#define GPPUB 0x0D
#define GPIOA 0x12
#define GPIOB 0x13

class LapMCP23017 {
public:
  LapMCP23017();
  LapMCP23017(uint8_t address);
  LapMCP23017(uint8_t address1, uint8_t address2);
  LapMCP23017(uint8_t address1, uint8_t address2, uint8_t address3);
  LapMCP23017(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4);
  LapMCP23017(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5);
  LapMCP23017(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5, uint8_t address6);
  LapMCP23017(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5, uint8_t address6, uint8_t address7);
  LapMCP23017(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5, uint8_t address6, uint8_t address7, uint8_t address8);
  LapMCP23017(TwoWire *wire);
  LapMCP23017(uint8_t address, TwoWire *wire);
  void begin();
  void pinMode(uint8_t pin, uint8_t mode);
  void portMode(uint8_t chip, uint16_t direction, uint16_t pullup);
  uint8_t digitalRead(uint8_t pin);
  void digitalWrite(uint8_t pin, uint8_t value);
  uint16_t read(uint8_t chip);
  void write(uint8_t chip, uint16_t value);

private:
  TwoWire* _wire;
  uint8_t _addr[8];
  uint8_t _count;
  uint8_t _read(uint8_t, uint8_t);
  void _write(uint8_t, uint8_t, uint8_t);
};
#endif
