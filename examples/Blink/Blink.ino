/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  The LED and resistor should be connected to port A, bit 0.
  
  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 15 Jun 2026
  by Lucy Amanda Berry

  This example code is in the public domain.

*/
#include <LapMCP23017.h>

#define ADDRESS 0x20
#define LED 0

LapMCP23017 io = LapMCP23017(ADDRESS);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialise the driver
  io.begin();
  // initialize digital pin LED_BUILTIN as an output.
  io.pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  io.digitalWrite(LED, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                 // wait for a second
  io.digitalWrite(LED, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(1000);                 // wait for a second
}
