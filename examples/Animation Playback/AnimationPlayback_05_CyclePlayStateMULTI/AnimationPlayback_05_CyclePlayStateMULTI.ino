/*
 * TinyFilmFestival - Multiple Animation State Machine Example
 * 
 * This example demonstrates managing multiple animations with a state machine.
 * It uses two animations:
 * - idle: A 4-frame animation with varied timing (150-300ms)
 * - go: A 9-frame animation with varied timing (66-300ms)
 * 
 * States cycle every 5 seconds:
 * State 0: Idle animation, normal speed, plays once
 * State 1: Go animation, fast speed, loops
 * State 2: Idle animation, slow speed, boomerang
 * State 3: Go animation, original timing, loops
 * State 4: Idle animation, paused
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation objects from the imported frame data
Animation idleAnim = idle;
Animation goAnim = go;

// State machine variables
int currentState = 0;            // Tracks which state we're in (0-4)
unsigned long lastStateChange;    // Timestamp of last state change
unsigned long stateDuration = 5000;  // Duration of each state (5 seconds)

// Speed settings for different states
int normalSpeed = 100;  // Normal playback speed (milliseconds)
int fastSpeed = 50;     // Fast playback speed
int slowSpeed = 200;    // Slow playback speed

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the LED matrix
    film.begin();

    // Record the start time
    lastStateChange = millis();

    // Start with initial animation in ONCE mode
    film.startAnimation(idleAnim, ONCE);

    // Print initial state information
    Serial.println("Starting Two-Animation State Machine Demo");
    Serial.println("State 0: Idle animation, Normal speed, Play Once");
}

void loop() {
    // Update the animation frame
    film.update();

    // Check if it's time to change state (every 5 seconds)
    if (millis() - lastStateChange >= stateDuration) {
        // Move to next state (0-4)
        currentState = (currentState + 1) % 5;
        lastStateChange = millis();

        // Handle state transition
        switch (currentState) {
            case 0:
                // Idle animation, normal speed, play once
                film.startAnimation(idleAnim, ONCE);
                film.setSpeed(normalSpeed);
                Serial.println("State 0: Idle animation, Normal speed, Play Once");
                break;

            case 1:
                // Go animation, fast speed, looping
                film.startAnimation(goAnim, LOOP);
                film.setSpeed(fastSpeed);
                Serial.println("State 1: Go animation, Fast speed, Looping");
                break;

            case 2:
                // Idle animation, slow speed, boomerang
                film.startAnimation(idleAnim, BOOMERANG);
                film.setSpeed(slowSpeed);
                Serial.println("State 2: Idle animation, Slow speed, Boomerang");
                break;

            case 3:
                // Go animation, original timing, looping
                film.startAnimation(goAnim, LOOP);
                film.restoreOriginalSpeed();
                Serial.println("State 3: Go animation, Original timing, Looping");
                break;

            case 4:
                // Idle animation, paused
                film.startAnimation(idleAnim, LOOP);
                film.pause();
                Serial.println("State 4: Idle animation, Paused");
                break;
        }
    }
}