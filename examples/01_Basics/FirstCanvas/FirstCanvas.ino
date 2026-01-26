/*
 * TinyFilmFestival V2 - First Canvas
 * 01_Basics/FirstCanvas
 * 
 * Your first code-generated animation: a bouncing dot.
 * No pre-made animation file needed - the motion is created with code!
 * 
 * This example demonstrates:
 *   - Using beginDraw() and endDraw() to draw on the matrix
 *   - Clearing the screen each frame
 *   - Using variables to create motion
 *   - The basic animation loop pattern
 * 
 * Hardware: Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 */

#include "TinyFilmFestival.h"

TinyScreen screen;

// Position and direction
int x = 0;
int direction = 1;  // 1 = moving right, -1 = moving left

void setup() {
    screen.begin();
}

void loop() {
    // Start drawing
    screen.beginDraw();
    
    // Clear the screen (set all pixels off)
    screen.clear();
    
    // Draw a single point at the current position
    screen.point(x, 4);  // y=4 is the middle row
    
    // Show what we drew
    screen.endDraw();
    
    // Update position for next frame
    x += direction;
    
    // Bounce off the edges
    if (x >= 11 || x <= 0) {
        direction *= -1;  // Reverse direction
    }
    
    // Control animation speed (smaller = faster)
    delay(100);
}
