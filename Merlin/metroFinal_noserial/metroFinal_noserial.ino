/*  Title:       Merlin Keypad Matrix
 *  Description: Read key pressed from Parker Brothers Merlin handheld game.
 *  Author:      Colin Travis
 *  Version:     1.0
 *  Modified:    11/19/2017
 */

#include <SPI.h>
#include "RF24.h"

// LED on keyboard to blink
#define ledPin 18

// Used to track LED state
int ledState = LOW;

// will store last time LED was updated
unsigned long previousMillis = 0;

// interval at which to blink (milliseconds)
const long interval = 500;

const int buttonPin = 2;     // the number of the pushbutton pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// Hardware configuration: Set up nRF24L01 radio on SPI bus
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  Serial.println("Test send message");

  radio.begin();
  // the following statements improve transmission range
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address

}

void loop() {
  char key = "F";
    buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH){
    Serial.println("button is down");

    radio.powerUp();
    Serial.println("Power up");
    radio.write(&key, sizeof(key));
    Serial.println("Radio send");
    radio.powerDown();
    Serial.println("Radio power down");
   // Serial.println(key-0x30);
	} else {
    Serial.println("button is up");
  }
}
