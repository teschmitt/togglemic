#include <Arduino.h>

#include <Bounce2.h>
#include <Keyboard.h>

#define BUTTON_PIN 5
#define LED_PIN 7
#define MUTE_CODE 0xD2

int ledState = LOW;
Bounce b = Bounce();

void setup() {
  
  b.attach(BUTTON_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  b.interval(25); // Use a debounce interval of 25 milliseconds
  
  
  pinMode(LED_PIN,OUTPUT); // Setup the LED
  digitalWrite(LED_PIN,ledState); // Turn off the LED
  Keyboard.begin();
}

void loop() {

   b.update(); // Update the Bounce instance
   
   if ( b.rose() ) {  // Call code if button transitions from HIGH to LOW
     ledState = !ledState; // Toggle LED state
     digitalWrite(LED_PIN,ledState); // Apply new LED state
     Keyboard.press(KEY_HOME);
     delay(100);
     Keyboard.releaseAll();
   }
}