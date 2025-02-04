/*
 * Simple LED Matrix Animation
 * For Arduino UNO R4 WiFi
 * 
 * This example shows how to create a simple animation by switching
 * between two different patterns on the LED matrix.
 * 
 * How to use:
 * 1. Look at the two frame arrays below (frame1 and frame2)
 * 2. Change any 0s to 1s to turn those LEDs on
 * 3. Change any 1s to 0s to turn those LEDs off
 * 4. Adjust the DISPLAY_TIME value to make the animation faster or slower
 * 5. Upload the modified code to see your animation!
 * 
 * The grid is 12 columns wide and 8 rows tall
 * Each number represents one LED:
 *   0 = LED off
 *   1 = LED on
 */

#include "Arduino_LED_Matrix.h"

// Create the LED matrix object
ArduinoLEDMatrix matrix;

// How long to show each frame (in milliseconds)
// Smaller number = faster animation
// Larger number = slower animation
const int DISPLAY_TIME = 1000;  // 1 second per frame

// First pattern - same as the static example
byte frame1[8][12] = {
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },  // Row 1
  { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },  // Row 2
  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },  // Row 3
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  // Row 4 
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },  // Row 5
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },  // Row 6
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },  // Row 7
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // Row 8
};

// Second pattern - a simple smiley face
byte frame2[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // Row 1
  { 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },  // Row 2
  { 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },  // Row 3
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // Row 4
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },  // Row 5
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },  // Row 6
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },  // Row 7
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // Row 8
};

void setup() {
  // Initialize the matrix
  matrix.begin();
}

void loop() {
  // Show the first pattern
  matrix.renderBitmap(frame1, 8, 12);
  delay(DISPLAY_TIME); //**Note** We are only using delay here for a simple example Avoid it in the future
  
  // Show the second pattern
  matrix.renderBitmap(frame2, 8, 12);
  delay(DISPLAY_TIME); //**Note** We are only using delay here for a simple example Avoid it in the future
}