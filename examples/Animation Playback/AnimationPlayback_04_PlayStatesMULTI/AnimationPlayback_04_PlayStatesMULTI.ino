/*
 * TinyFilmFestival - Simple Two State Example
 * 
 * This example shows how to select between two animations using a variable.
 * 
 * Animations:
 * - idle: 4-frame idle animation
 * - go: 9-frame go animation
 * 
 * Set useIdleAnimation to:
 * true - plays idle animation
 * false - plays go animation
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

// Create Animation objects
Animation idleAnim = idle;
Animation goAnim = go;

// Animation selection
bool useIdleAnimation = true;  // Set to false to use go animation

void setup() {
    // Initialize the LED matrix
    film.begin();
    
    // Start the selected animation
    if (useIdleAnimation) {
        film.startAnimation(idleAnim, BOOMERANG);
    } else {
        film.startAnimation(goAnim, BOOMERANG);
    }
}

void loop() {
    // Update the animation frame
    film.update();
}