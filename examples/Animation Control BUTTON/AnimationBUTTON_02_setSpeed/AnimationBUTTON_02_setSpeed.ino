/*
 * TinyFilmFestival - Simple Speed Control Example
 * 
 * This example demonstrates using a button to cycle through different
 * animation speeds. Each button press changes to the next speed in
 * the sequence:
 * 
 * Normal Speed (original timing) -> Fast (50ms) -> Slow (200ms) -> repeat
 * 
 * The speed control and state management is handled internally by
 * the library, so no external state tracking is needed.
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - Pushbutton connected to pin 2 and ground
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "idle.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object
Animation idleAnim = idle;

// Button pin
int buttonPin = 2;
boolean buttonState;

// Speed control
int SPEED_FAST = 50;    // Fast speed (50ms per frame)
int SPEED_SLOW = 200;   // Slow speed (200ms per frame)


void setup() {
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Setup button pin with internal pullup resistor

    pinMode(buttonPin, INPUT_PULLUP);
    
    // Start with animation playing in loop mode at original speed
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Animation started at normal speed");
}

void loop() {
    // Check for button press (LOW when pressed due to INPUT_PULLUP)
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {

                film.setSpeed(SPEED_FAST);
                Serial.println("Fast speed (50ms)");
      }
                
            else{
                film.setSpeed(SPEED_SLOW);
                Serial.println("Slow speed (200ms)");
               
        }
        

   
    
    // Update the animation frame
    film.update();
}