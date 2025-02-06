/*
 * TinyFilmFestival - Button Control Example
 * 
 * This example shows how to switch between two animations using a button.
 * 
 * Animations:
 * - idle: 4-frame idle animation (plays when button is NOT pressed)
 * - go: 9-frame go animation (plays when button IS pressed)
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - Pushbutton connected to pin 2 and ground
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation objects
Animation idleAnim = idle;
Animation goAnim = go;

// Button pin
int buttonPin = 2;
boolean buttonState;

void setup() {
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Setup button pin with internal pullup resistor
    pinMode(buttonPin, INPUT_PULLUP);
    
    // Start with idle animation
    film.startAnimation(idleAnim, LOOP);
}

void loop() {
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
        film.startAnimation(goAnim, LOOP);
        Serial.println("Playing Go");
    } else {
        film.startAnimation(idleAnim, LOOP);
        Serial.println("Playing Idle");
    }

    film.update();
}