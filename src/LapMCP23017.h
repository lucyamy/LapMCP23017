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
  LapMCP23017(uint8_t);
  LapMCP23017(uint8_t, uint8_t);
  LapMCP23017(uint8_t, uint8_t, uint8_t);
  LapMCP23017(uint8_t, uint8_t, uint8_t, uint8_t);
  LapMCP23017(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  LapMCP23017(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  LapMCP23017(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  LapMCP23017(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  LapMCP23017(TwoWire *);
  LapMCP23017(uint8_t, TwoWire *);
  void begin();
  void pinMode(uint8_t, uint8_t);
  void portMode(uint8_t, uint16_t, uint16_t);
  uint8_t digitalRead(uint8_t);
  void digitalWrite(uint8_t, uint8_t);
  uint16_t read(uint8_t);
  void write(uint8_t, uint16_t);

private:
  TwoWire* _wire;
  uint8_t _addr[8];
  uint8_t _count;
  uint8_t _read(uint8_t, uint8_t);
  void _write(uint8_t, uint8_t, uint8_t);
};
#endif
