LapMCP23017 is a simple library to support the MCP23017 I2C I/O expander chip. It treats the MCP23017's two 8-bit ports a one 16-bit port, which makes it easier
to use. It enables bit by bit access to reading and writing, through **digitalRead()**
and **digitalWrite()**, and 16-bit read and writes with **read()** and **write()**.
Likewise it has **pinMode()** to set the mode of a pin, and **portMode()** to set the mode of all 16 I/O pins.

The constructors are:

###	LapMCP23017();
This will use the default I2C address of 0x20, and will use the Wire interface.

###	LapMCP23017(uint8_t address);
This will use the specified I2C address, and will use the Wire interface.

###	LapMCP23017(TwoWire *wire);
This will use the default I2C address of 0x20, and will use the specified I2C interface.

###	LapMCP23017(uint8_t address, TwoWire *wire);
This will use the specified I2C address, and will use the specified I2C interface.

The functions are:

###	void begin();
This initialises the LapMCP23017 driver. All pins are set to be inputs. It can be called at any time to reset everything.

###	void pinMode(uint8_t pin, uint8_t mode);
This is equivalent to the standard Arduino pinMode() function. *pin* is 0-15.

###  void portMode(uint16_t direction, uint16_t pullup);
**portMode** is like **pinMode**, but it sets the mode for all 16 bits. The *direction* parameter sets each pin to input or output. A 1 in a bit
position sets that pin to be an input, a 0 sets it to be an output.
The *pullup* parameter turns pullup on or off. A 1 in a bit position sets that pin to have pullup, a 0 sets it to not have pullup.

###	uint8_t digitalRead(uint8_t pin);
This is equivalent to the standard Arduino digitalRead() function. *pin* is 0-15.

###	void digitalWrite(uint8_t pin, uint8_t value);
This is equivalent to the standard Arduino digitalWrite() function. *pin* is 0-15.

###	uint16_t read();
This reads a 16-bit value. The low byte is read from port A, and the high byte from Port B.

###	void write(uint16_t value);
This writes a 16-bit value. The low byte is written to port A, and the high byte to Port B.

