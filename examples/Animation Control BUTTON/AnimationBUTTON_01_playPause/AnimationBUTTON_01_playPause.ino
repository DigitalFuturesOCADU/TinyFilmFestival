/*
 * TinyFilmFestival - Simple Play/Pause Example
 * 
 * This example demonstrates using a button to toggle play/pause state
 * of an animation. The animation starts playing automatically,
 * and each button press toggles between playing and paused states.
 * 
 * The state management is handled internally by the library, so
 * no external state tracking is needed.
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
void setup() {
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Setup button pin with internal pullup resistor
    pinMode(buttonPin, INPUT_PULLUP);
    
    // Start with animation playing in loop mode
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Animation started");
}

void loop() {
    // Check for button press (LOW when pressed due to INPUT_PULLUP)
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
        // Toggle play/pause state
       
      film.pause();
      Serial.println("Animation paused");
                      
    }
    else {
            film.resume();
            Serial.println("Animation resumed");
        }
    
    // Update the animation frame
    film.update();
}
