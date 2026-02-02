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
 * 
 * LED Matrix Layout (12 columns x 8 rows):
 * 
 *      x=0  x=1  x=2  x=3  x=4  x=5  x=6  x=7  x=8  x=9  x=10 x=11
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=0 |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=1 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=2 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=3 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=4 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=5 | 60 | 61 | 62 | 63 | 64 | 65 | 66 | 67 | 68 | 69 | 70 | 71 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=6 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 | 81 | 82 | 83 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=7 | 84 | 85 | 86 | 87 | 88 | 89 | 90 | 91 | 92 | 93 | 94 | 95 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
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
