#include <Arduino.h>

#include <Bounce2.h>
#include <Keyboard.h>

#define MIC_MUTE_BUTTON_PIN 5
#define LED_PIN 7

int ledState = LOW;
Bounce mic_mute = Bounce();

void setup() {
  
  mic_mute.attach(MIC_MUTE_BUTTON_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  mic_mute.interval(25); // Use a debounce interval of 25 milliseconds
  
  
  pinMode(LED_PIN,OUTPUT); // Setup the LED
  digitalWrite(LED_PIN,ledState); // Turn off the LED
  Keyboard.begin();
}

void loop() {

   mic_mute.update(); // Update the Bounce instance
   
   if ( mic_mute.rose() ) {           // Call code if button transitions from HIGH to LOW
     ledState = !ledState;            // Toggle LED state
     digitalWrite(LED_PIN,ledState);  // Apply new LED state
     Keyboard.press(0x80);            // Ctrl
     Keyboard.press(0x81);            // Shift
     Keyboard.press(0xFA);            // F23 or TouchPadOff or something equally unused
     delay(100);
     Keyboard.releaseAll();
   }
}