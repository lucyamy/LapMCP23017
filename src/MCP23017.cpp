#include "LapMCP23017.h"

/*
 * Constructors
 */
LapMCP23017::LapMCP23017() {
  _addr[0] = 0x20;
  _wire = &Wire;
  _count = 1;
}

LapMCP23017::LapMCP23017(uint8_t address) {
  _addr[0] = address;
  _wire = &Wire;
  _count = 1;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2) {
  _addr[0] = a1;
  _addr[1] = a2;
  _wire = &Wire;
  _count = 2;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2, uint8_t a3) {
  _addr[0] = a1;
  _addr[1] = a2;
  _addr[2] = a3;
  _wire = &Wire;
  _count = 3;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4) {
  _addr[0] = a1;
  _addr[1] = a2;
  _addr[2] = a3;
  _addr[3] = a4;
  _wire = &Wire;
  _count = 4;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5) {
  _addr[0] = a1;
  _addr[1] = a2;
  _addr[2] = a3;
  _addr[3] = a4;
  _addr[4] = a5;
  _wire = &Wire;
  _count = 5;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6) {
  _addr[0] = a1;
  _addr[1] = a2;
  _addr[2] = a3;
  _addr[3] = a4;
  _addr[4] = a5;
  _addr[5] = a6;
  _wire = &Wire;
  _count = 6;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7) {
  _addr[0] = a1;
  _addr[1] = a2;
  _addr[2] = a3;
  _addr[3] = a4;
  _addr[4] = a5;
  _addr[5] = a6;
  _addr[6] = a7;
  _wire = &Wire;
  _count = 7;
}

LapMCP23017::LapMCP23017(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7, uint8_t a8) {
  _addr[0] = a1;
  _addr[1] = a2;
  _addr[2] = a3;
  _addr[3] = a4;
  _addr[4] = a5;
  _addr[5] = a6;
  _addr[6] = a7;
  _addr[7] = a8;
  _wire = &Wire;
  _count = 8;
}

LapMCP23017::LapMCP23017(TwoWire *wire) {
  _addr[0] = 0x20;
  _wire = wire;
  _count = 1;
}

LapMCP23017::LapMCP23017(uint8_t address, TwoWire *wire) {
  _addr[0] = address;
  _wire = wire;
  _count = 1;
}

/*
 * Public
 */

void LapMCP23017::begin(uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(100);
  digitalWrite(pin, HIGH);
  begin();
}

void LapMCP23017::begin() {
  int i = _count;
  uint8_t addr;
  while(i) {
    addr = _addr[i];
    _write(IOCON, 0x20, addr);
    _write(IODRA, 0xFF, addr);
    _write(IODRB, 0xFF, addr);
    _write(GPPUA, 0x00, addr);
    _write(GPPUB, 0x00, addr);
    _write(IPOLA, 0x00, addr);
    _write(IPOLB, 0x00, addr);
    i--;
  }
}

void LapMCP23017::portMode(uint8_t chip, uint16_t dir, uint16_t pullup) {
  _write(IODRA, lowByte(dir), _addr[chip]);
  _write(IODRB, highByte(dir), _addr[chip]);
  _write(GPPUA, lowByte(pullup), _addr[chip]);
  _write(GPPUB, highByte(pullup), _addr[chip]);
}

void LapMCP23017::pinMode(uint8_t pin, uint8_t mode) {
  uint8_t dir;
  uint8_t pullup;
  uint8_t port = 0;
  uint8_t chip = 0;

  while(pin > 15) {
    chip++;
    pin -= 16;
  }
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  dir = _read(IODRA + port, _addr[chip]);
  if(mode == INPUT || mode == INPUT_PULLUP)
    bitSet(dir, pin);
  else
    bitClear(dir, pin);
  _write(IODRA + port, dir, _addr[chip]);
  pullup = _read(GPPUA + port, _addr[chip]);
  if(mode == INPUT_PULLUP)
    bitSet(pullup, pin);
  else
    bitClear(pullup, pin);
  _write(GPPUA + port, pullup, _addr[chip]);
}

void LapMCP23017::digitalWrite(uint8_t pin, uint8_t val) {
  uint8_t io;
  uint8_t port = 0;
  uint8_t chip = 0;

  while(pin > 15) {
    chip++;
    pin -= 16;
  }
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  io = _read(GPIOA + port, _addr[chip]);
  if(val == HIGH)
    bitSet(io, pin);
  else 
    bitClear(io, pin);
  _write(GPIOA + port, io, _addr[chip]);
}

uint8_t LapMCP23017::digitalRead(uint8_t pin) {
  uint8_t io;
  uint8_t port = 0;
  uint8_t chip = 0;

  while(pin > 15) {
    chip++;
    pin -= 16;
  }
  if(pin > 7) {
    pin -= 8;
    port = 1;
  }
  io = _read(GPIOA + port, _addr[chip]);
  if(bitRead(io, pin)) 
    return HIGH;
  else
    return LOW;
}

void LapMCP23017::write(uint8_t i, uint16_t value) {
  _write(GPIOA, lowByte(value), _addr[i]);
  _write(GPIOB, highByte(value), _addr[i]);
}

uint16_t LapMCP23017::read(uint8_t i) {
  return _read(GPIOA, _addr[i]) | (_read(GPIOB, _addr[i]) << 8);
}

/*
 * Private
 */

void LapMCP23017::_write(uint8_t reg, uint8_t val, uint8_t addr) {
  _wire->beginTransmission(addr);
  _wire->write(reg);
  _wire->write(val);
  _wire->endTransmission();
}

uint8_t LapMCP23017::_read(uint8_t reg, uint8_t addr) {
  _wire->beginTransmission(addr);
  _wire->write(reg);
  _wire->endTransmission();
  _wire->requestFrom((uint16_t) addr, (uint16_t) 1);
  return _wire->read();
}



