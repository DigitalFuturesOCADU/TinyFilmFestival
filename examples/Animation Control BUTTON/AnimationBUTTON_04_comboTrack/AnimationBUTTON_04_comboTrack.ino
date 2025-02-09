/*
 * TinyFilmFestival - Example 3
 * Button-Triggered Animation with Background
 * 
 * This example shows how to:
 *   - Play a continuous looping background animation
 *   - Trigger a second animation with a button press
 *   - Combine multiple animations using CombinedFilmFestival
 *   - Show/hide animations using stop()
 * 
 * Animation Files:
 *   - landscape.h -> Continuous background animation
 *   - fiz.h -> Button-triggered effect
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - Pushbutton connected to pin 2 and ground
 * 
 * Circuit:
 *   - Button between pin 2 and ground (uses internal pullup)
 * 
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "landscape.h"    // Background animation
#include "fiz.h"         // Effect animation

// Create TinyFilmFestival objects for each animation
TinyFilmFestival backgroundFilm;
TinyFilmFestival effectFilm;

// Create a CombinedFilmFestival to merge the animations
CombinedFilmFestival combinedFilm;

// Create Animation objects from the frame data
Animation landscapeAnim = landscape;
Animation fizAnim = fiz;

// Animation control settings
int backgroundSpeed = 100;    // Speed for landscape (milliseconds)
int effectSpeed = 50;         // Speed for fiz effect (milliseconds)

// Button pin
const int buttonPin = 2;
boolean buttonState;


void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("Starting button-controlled animation demo");
    
    // Setup button pin with internal pullup resistor
    pinMode(buttonPin, INPUT_PULLUP);
    
    // Start the LED matrix
    combinedFilm.begin();
    
    // Configure background animation (continuous loop)
    backgroundFilm.startAnimation(landscapeAnim, LOOP);
    backgroundFilm.setSpeed(backgroundSpeed);
    
    // Configure effect animation (starts stopped)
    effectFilm.startAnimation(fizAnim, LOOP);
    effectFilm.setSpeed(effectSpeed);
    effectFilm.stop();
    
    // Add animations to the combiner
    // Order matters - first added appears "behind" later ones
    combinedFilm.addFilm(backgroundFilm);  // Landscape in background
    combinedFilm.addFilm(effectFilm);      // Effect in foreground
}

void loop() {
    // Read button state
    buttonState = digitalRead(buttonPin);
    
    // Check for button press/release
   
        if (buttonState == LOW) {
            // Button pressed - start effect
            effectFilm.startAnimation(fizAnim, LOOP);
            Serial.println("Effect started");
        } else {
            // Button released - stop effect
            effectFilm.stop();
            Serial.println("Effect stopped");
        }
       
    
    
    // Update the combined animation
    combinedFilm.update();
}