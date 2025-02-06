/*
 * TinyFilmFestival - State Machine Example
 * 
 * This example demonstrates how to combine animation control with a simple
 * state machine to create different playback effects. The example shows:
 *   - How to declare and use the Animation type
 *   - Basic state machine implementation
 *   - Timer-based state transitions
 *   - How animation parameters change with states
 *   - Different playback modes (ONCE, LOOP, BOOMERANG)
 * 
 * 
 * State 0: Normal speed (100ms), plays once
 * State 1: Fast speed (50ms), loops
 * State 2: Slow speed (200ms), boomerang
 * State 3: Original speed from animation data, loops
 * State 4: Paused
 * 
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "animation.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object from the imported frame data
Animation myAnimation = frameAnimation;

// State machine variables
int currentState = 0;            // Tracks which state we're in (0-4)


// Speed settings for different states
int normalSpeed = 100;  // Normal playback speed (milliseconds)
int fastSpeed = 50;     // Fast playback speed
int slowSpeed = 200;    // Slow playback speed

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
            // Handle state transition
        switch (currentState) 
        {
            case 0:
                // Normal speed, play once
                film.startAnimation(myAnimation, ONCE);
                film.setSpeed(normalSpeed);
                Serial.println("State 0: Normal speed, Play Once");
                break;
                
            case 1:
                // Fast speed, looping
                film.startAnimation(myAnimation, LOOP);
                film.setSpeed(fastSpeed);
                Serial.println("State 1: Fast speed, Looping");
                break;
                
            case 2:
                // Slow speed, boomerang
                film.startAnimation(myAnimation, BOOMERANG);
                film.setSpeed(slowSpeed);
                Serial.println("State 2: Slow speed, Boomerang");
                break;
                
            case 3:
                // Original timing from animation data, looping
                film.startAnimation(myAnimation, LOOP);
                film.restoreOriginalSpeed();
                Serial.println("State 3: Original speed from animation, Looping");
                break;
                
            case 4:
                // Paused state
                film.pause();
                Serial.println("State 4: Paused");
                break;
        }
}

void loop() {
    // Update the animation frame
    film.update();
    
 
        

    
}