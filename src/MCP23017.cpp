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

LapMCP23017::LapMCP23017(uint8_t address, TwoWire *wire) {
  _addr = address;
  _wire = wire;
}

/*
 * Public
 */

void LapMCP23017::begin() {
  writeReg(IOCON, 0x20);
  writeReg(GPPU_A, 0xFF);
  writeReg(GPPU_B, 0xFF);
  writeReg(IPOL_A, 0);
  writeReg(IPOL_B, 1);
}

void LapMCP23017::portMode(uint8_t port, uint8_t dir, uint8_t pullup) {
  writeReg(IODIR_A + port, dir);
  writeReg(GPPU_A + port, pullup);
}

void LapMCP23017::pinMode(uint8_t pin, uint8_t mode) {
  uint8_t dir;
  uint8_t pullup;
  uint8_t port = 0;#include "LapMCP23017.h"

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

LapMCP23017::LapMCP23017(uint8_t address, TwoWire *wire) {
  _addr = address;
  _wire = wire;
}

/*
 * Public
 */

void LapMCP23017::begin() {
  writeReg(IOCON, 0x20);
  writeReg(GPPU_A, 0xFF);
  writeReg(GPPU_B, 0xFF);
  writeReg(IPOL_A, 0);
  writeReg(IPOL_B, 1);
}

void LapMCP23017::portMode(uint16_t dir, uint16_t pullup) {
  writeReg(IODIR_A, lowByte(dir));
  writeReg(IODIR_B, highByte(dir));
  writeReg(GPPU_A, lowByte(pullup));
  writeReg(GPPU_B, highByte(pullup));
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
  dir = readReg(IODIR_A + port);
  if(mode == INPUT || mode == INPUT_PULLUP)
    bitSet(dir, pin);
  else
    bitClear(dir, pin);
  writeReg(IODIR_A + port, dir);
  pullup = readReg(GPPU_A + port);
  if(mode == INPUT_PULLUP)
    bitSet(pullup, pin);
  else
    bitClear(pullup, pin);
  writeReg(GPPU_A + port, pullup);
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
  io = readReg(GPIO_A + port);
  if(val == HIGH)
    bitSet(io, pin);
  else 
    bitClear(io, pin);
  writeReg(GPIO_A + port, io);
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
  io = readReg(GPIO_A + port);
  if(bitRead(io, pin)) 
    return HIGH;
  else
    return LOW;
}

void LapMCP23017::write(uint16_t value) {
  writeReg(GPIO_A, lowByte(value));
  writeReg(GPIO_B, highByte(value));
}

uint16_t LapMCP23017::read() {
  return readReg(GPIO_A) | (readReg(GPIO_B) << 8);
}

/*
 * Private
 */

void LapMCP23017::writeReg(uint8_t reg, uint8_t val) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(val);
  _wire->endTransmission();
}

uint8_t LapMCP23017::readReg(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->endTransmission();
  _wire->requestFrom((uint16_t) _addr, (uint16_t) 1);
  return _wire->read();
}


  if(pin > 15)
    return;
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  dir = readReg(IODIR_A + port);
  if(mode == INPUT || mode == INPUT_PULLUP)
    bitSet(dir, pin);
  else
    bitClear(dir, pin);
  writeReg(IODIR_A + port, dir);
  pullup = readReg(GPPU_A + port);
  if(mode == INPUT_PULLUP)
    bitSet(pullup, pin);
  else
    bitClear(pullup, pin);
  writeReg(GPPU_A + port, pullup);
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
  io = readReg(GPIO_A + port);
  if(val == HIGH)
    bitSet(io, pin);
  else 
    bitClear(io, pin);
  writeReg(GPIO_A + port, io);
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
  io = readReg(GPIO_A + port);
  if(bitRead(io, pin)) 
    return HIGH;
  else
    return LOW;
}

void LapMCP23017::write(uint8_t port, uint8_t val) {
  writeReg(GPIO_A + port, val);
}

void LapMCP23017::write16(uint16_t value) {
  writeReg(GPIO_A, lowByte(value));
  writeReg(GPIO_B, highByte(value));
}

uint8_t LapMCP23017::read(uint8_t port) {
  return readReg(GPIO_A + port);
}

uint16_t LapMCP23017::read16() {
  return readReg(GPIO_A) | (readReg(GPIO_B) << 8);
}

/*
 * Private
 */

void LapMCP23017::writeReg(uint8_t reg, uint8_t val) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(val);
  _wire->endTransmission();
}

uint8_t LapMCP23017::readReg(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->endTransmission();
  _wire->requestFrom((uint16_t) _addr, (uint16_t) 1);
  return _wire->read();
}
