/*
 * Simple LED Matrix Pattern
 * For Arduino UNO R4 WiFi
 * 
 * This example shows how to display a pattern on the built-in LED matrix
 * by modifying a simple grid of 1s and 0s.
 * 
 * How to use:
 * 1. Look at the frame array below
 * 2. Change any 0s to 1s to turn those LEDs on
 * 3. Change any 1s to 0s to turn those LEDs off
 * 4. Upload the modified code to see your pattern!
 * 
 * The grid is 12 columns wide and 8 rows tall
 * Each number represents one LED:
 *   0 = LED off
 *   1 = LED on
 */

#include "Arduino_LED_Matrix.h"

// Create the LED matrix object
ArduinoLEDMatrix matrix;

// Define our pattern using 1s and 0s
// 12 numbers across, 8 rows down
byte frame[8][12] = {
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },  // Row 1
  { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },  // Row 2
  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },  // Row 3
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  // Row 4 
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },  // Row 5
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },  // Row 6
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },  // Row 7
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // Row 8
};
/*
// Same pattern in compressed format (hex values represent the same LED pattern)
const uint32_t frame[] = {
    0x3184a444,  // First 32 bits
    0x44042081,  // Middle 32 bits
    0x100a0040   // Last 32 bits
};
*/

void setup() {
  // Initialize the matrix
  matrix.begin();
  
  // Display our pattern
  matrix.renderBitmap(frame, 8, 12);
}

void loop() {
  // Nothing to do here - pattern stays static
}