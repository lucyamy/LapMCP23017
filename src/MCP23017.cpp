#include "LapMCP23017.h"

/*
 * Constructors
 */
LapMCP23017::LapMCP23017() {
  _addr = 0x20;
  _wire = &Wire;
}

LapMCP23017::LapMCP23017(uint8_t address) {
  _addr = address;
  _wire = &Wire;
}

LapMCP23017::LapMCP23017(TwoWire *wire) {
  _addr = 0x20;
  _wire = wire;
}

LapMCP23017::LapMCP23017(uint8_t address, TwoWire *wire) {
  _addr = address;
  _wire = wire;
}

/*
 * Public
 */

void LapMCP23017::begin() {
  _write(IOCON, 0x20);
  _write(GPPU_A, 0xFF);
  _write(GPPU_B, 0xFF);
  _write(IPOL_A, 0);
  _write(IPOL_B, 1);
}


void LapMCP23017::portMode(uint16_t dir, uint16_t pullup) {
  _write(IODIR_A, lowByte(dir));
  _write(IODIR_B, highByte(dir));
  _write(GPPU_A, lowByte(pullup));
  _write(GPPU_B, highByte(pullup));
}

void LapMCP23017::pinMode(uint8_t pin, uint8_t mode) {
  uint8_t dir;
  uint8_t pullup;
  uint8_t port = 0;

  if(pin > 15)
    return;
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  dir = _read(IODIR_A + port);
  if(mode == INPUT || mode == INPUT_PULLUP)
    bitSet(dir, pin);
  else
    bitClear(dir, pin);
  _write(IODIR_A + port, dir);
  pullup = _read(GPPU_A + port);
  if(mode == INPUT_PULLUP)
    bitSet(pullup, pin);
  else
    bitClear(pullup, pin);
  _write(GPPU_A + port, pullup);
}

void LapMCP23017::digitalWrite(uint8_t pin, uint8_t val) {
  uint8_t io;
  uint8_t port = 0;

  if(pin > 15)
    return;
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  io = _read(GPIO_A + port);
  if(val == HIGH)
    bitSet(io, pin);
  else 
    bitClear(io, pin);
  _write(GPIO_A + port, io);
}

uint8_t LapMCP23017::digitalRead(uint8_t pin) {
  uint8_t io;
  uint8_t port = 0;

  if(pin > 15)
    return LOW;
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  io = _read(GPIO_A + port);
  if(bitRead(io, pin)) 
    return HIGH;
  else
    return LOW;
}

void LapMCP23017::write(uint16_t value) {
  _write(GPIO_A, lowByte(value));
  _write(GPIO_B, highByte(value));
}

uint16_t LapMCP23017::read() {
  return _read(GPIO_A) | (_read(GPIO_B) << 8);
}

/*
 * Private
 */

void LapMCP23017::_write(uint8_t reg, uint8_t val) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(val);
  _wire->endTransmission();
}

uint8_t LapMCP23017::_read(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->endTransmission();
  _wire->requestFrom((uint16_t) _addr, (uint16_t) 1);
  return _wire->read();
}



