/*
 * TinyFilmFestival - Example 1
 * Basic Animation Control
 * 
 * This example shows the simplest way to use the TinyFilmFestival library.
 * It demonstrates how to:
 *   - Load an animation from a header file
 *   - Set different playback modes
 *   - Control animation speed
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi
 * 
 */

#include "TinyFilmFestival.h"
#include "animation.h"     // Your animation file from LED Matrix Editor

// Create an instance of TinyFilmFestival
TinyFilmFestival film;

// Animation control settings
int playSpeed = 50;    // Animation speed in milliseconds


void setup() {
    // Start the LED matrix
    film.begin();
    
    //uncomment lines to try different playback methods

    // Method 1: Play animation once and stop
    //film.startAnimation(frameAnimation, PLAY_ONCE);
   
    
    // Method 2: Play animation in a continuous loop
    //film.startAnimation(frameAnimation, PLAY_LOOP);
   
    
    // Method 3: Play animation in boomerang mode (forward/backward)
    film.startAnimation(frameAnimation, PLAY_BOOMERANG);
    
    
    film.setSpeed(playSpeed);  // Set a custom speed
}

void loop() {
    // This is required to keep the animation running
    film.update();
}