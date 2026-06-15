LapMCP23017 is a simple library to drive the MCP23017 I2C I/O expander chip.

The constructors are:

###	LapMCP23017();
This will use the default I2C address of 0x20, and will use the Wire interface.

###	LapMCP23017(uint8_t address);
This will use the specified I2C address, and will use the Wire interface.

###	LapMCP23017(uint8_t address, TwoWire *wire);
This will use the specified I2C address, and will use the specified I2C interface.

The functions are:

###	void begin();
This initialises the LapMCP23017 driver. All pins are set to be inputs.

###	void pinMode(uint8_t pin, uint8_t mode);
This is equivalent to the standard Arduino pinMode() function. *pin* is 0-15.

###  void portMode(uint8_t port, uint8_t direction, uint8_t pullup);
**portMode** is like **pinMode**, but it sets the mode for all 8 bits of port A or B. The *port* parameter, which is 0 or 1, is used to select the MCP23017's
port A or port B. The *direction* parameter sets each pin to input or output. A 1 in a bit position sets that pin to be an input, a 0 sets it to be an output.
The *pullup* parameter turns pullup on or off. A 1 in a bit position sets that pin to have pullup, a 0 sets it to not have pullup.

###	uint8_t digitalRead(uint8_t pin);
This is equivalent to the standard Arduino digitalRead() function. *pin* is 0-15.

###	void digitalWrite(uint8_t pin, uint8_t value);
This is equivalent to the standard Arduino digitalWrite() function. *pin* is 0-15.

###	uint8_t read(uint8_t port);
This reads a byte from a port. *port*, which is 0 or 1, is used to select the MCP23017's port A or port B.

###	void write(uint8_t port, uint8_t value;
This writes a byte to a port. *port*, which is 0 or 1, is used to select the MCP23017's port A or port B. *value* is the byte to be written.

###	uint16_t read16();
This reads a 16-bit value. The low byte is read from port A, and the high byte from Port B.

###	void write16(uint16_t value);
This writes a 16-bit value. The low byte is written to port A, and the high byte to Port B.

