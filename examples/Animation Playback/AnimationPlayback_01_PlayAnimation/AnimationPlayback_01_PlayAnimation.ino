/*
 * TinyFilmFestival - Example 1
 * Basic Animation Control
 * 
 * This example shows the simplest way to use the TinyFilmFestival library.
 * It demonstrates how to:
 *   - Create an Animation object from frame data
 *   - Set different playback modes (ONCE, LOOP, BOOMERANG)
 *   - Control animation playback
 *   - Play specific portions of an animation forwards or backwards
 * 
 * Available Playback Modes:
 *   - ONCE: Play animation one time and stop
 *   - LOOP: Play animation forward repeatedly
 *   - BOOMERANG: Play animation forward then backward repeatedly
 * 
 * Animation File:
 *   The animation array variable name matches the header filename:
 *   - animation.h -> const uint32_t animation[][4]
 *   - myanimation.h -> const uint32_t myanimation[][4]
 *   This name is set when exporting from the Matrix Editor
 * 
 * startAnimation Usage:
 *   Full animation:
 *     film.startAnimation(myAnimation, mode)
 *   Partial animation:
 *     film.startAnimation(myAnimation, mode, startFrame, endFrame)
 *   Note: Frame numbers start at 1
 * 
 * Animation Control Methods:
 *   - setSpeed(milliseconds): Set a custom frame duration
 *   - restoreOriginalSpeed(): Return to original frame timings
 *   - pause(): Pause the animation
 *   - resume(): Resume a paused animation
 *   - stop(): Stop the animation completely
 *   - update(): Update the animation (call in loop)
 * 
 * Status Methods:
 *   - isPlaying(): Check if animation is playing
 *   - isPaused(): Check if animation is paused
 *   - isComplete(): Check if animation is complete
 *   - getState(): Get current animation state
 *   - getCurrentFrame(): Get current frame number
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * 
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "animation.h"     // Your animation file from LED Matrix Editor

// Create an instance of TinyFilmFestival
TinyFilmFestival film;

// Create an Animation object from the frame data
Animation myAnimation = animation;

// Animation control settings
int playSpeed = 50;    // Animation speed in milliseconds

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.print("Total frames in animation: ");
    Serial.println(myAnimation.getFrameCount());
    
    // Start the LED matrix
    film.begin();
    
    // Uncomment different lines to try various playback methods
    
    // Method 1: Play animation once and stop
    //film.startAnimation(myAnimation, ONCE);
    
    // Method 2: Play animation in a continuous loop
    //film.startAnimation(myAnimation, LOOP);
    
    // Method 3: Play animation in boomerang mode (forward/backward)
    film.startAnimation(myAnimation, BOOMERANG);
    
    // Method 4: Play frames 2-6 forward
    //film.startAnimation(myAnimation, LOOP, 2, 6);
    
    // Method 5: Play frames 6-2 backward
    //film.startAnimation(myAnimation, LOOP, 6, 2);
    
    // Optional: Set a custom playback speed
    film.setSpeed(playSpeed);
    
    // Other control examples (uncomment to try):
    //film.pause();              // Pause the animation
    //film.resume();             // Resume the animation
    //film.restoreOriginalSpeed(); // Use original frame timings
    //film.stop();              // Stop the animation
}

// Counter for completed animations
int completionCount = 0;

void loop() {
    // Required: Update the animation in each loop
    film.update();
    
    //add other code here to interact with the controls dynamically with sensor inputs    
}