/*
 * TinyFilmFestival - Basics - FirstCanvas
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
 * Mode: Canvas
 * See also: 01_Basics/FirstAnimation (pre-made animation version)
 * 
 * Hardware Required:
 *   - Arduino UNO R4 WiFi
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Position and direction
int x = 0;
int direction = 1;  // 1 = moving right, -1 = moving left

void setup() {
    matrix.begin();
}

void loop() {
    // Start drawing
    matrix.beginDraw();
    
    // Clear the screen (set all pixels off)
    matrix.clear();
    
    // Set the drawing color to "on"
    matrix.stroke(0xFFFFFF);
    
    // Draw a single point at the current position
    matrix.point(x, 4);  // y=4 is the middle row
    
    // Show what we drew
    matrix.endDraw();
    
    // Update position for next frame
    x += direction;
    
    // Bounce off the edges
    if (x >= 11 || x <= 0) {
        direction *= -1;  // Reverse direction
    }
    
    // Control animation speed (smaller = faster)
    delay(100);
}
