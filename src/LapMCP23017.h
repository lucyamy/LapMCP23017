#ifndef LAPMCP23017_H
#define LAPMCP23017_H

#include <Arduino.h>
#include <Wire.h>

#define IODIR_A 0x00
#define IODIR_B 0x01
#define IPOL_A 0x02
#define IPOL_B 0x03
#define IOCON 0x0A 
#define GPPU_A 0x0C
#define GPPU_B 0x0D
#define GPIO_A 0x12
#define GPIO_B 0x13

class LapMCP23017 {
public:
  LapMCP23017();
  LapMCP23017(uint8_t);
  LapMCP23017(TwoWire *);
  LapMCP23017(uint8_t, TwoWire *);
  void begin();
  void pinMode(uint8_t, uint8_t);
  void portMode(uint16_t, uint16_t);
  uint8_t digitalRead(uint8_t);
  void digitalWrite(uint8_t, uint8_t);
  uint16_t read();
  void write(uint16_t);

private:
  TwoWire* _wire;
  uint8_t _addr;
  uint8_t _read(uint8_t);
  void _write(uint8_t, uint8_t);
};
#endif
