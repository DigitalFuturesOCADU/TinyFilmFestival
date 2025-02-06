# Basic Matrix Examples

## Single Frame Display

Display static patterns on the LED matrix. This example shows basic matrix control and pattern definition.

```cpp
/*
 * Simple LED Matrix Pattern
 * For Arduino UNO R4 WiFi
 * 
 * The grid is 12 columns wide and 8 rows tall
 * Each number represents one LED:
 *   0 = LED off
 *   1 = LED on
 */

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

byte frame[8][12] = {
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void setup() {
  matrix.begin();
  matrix.renderBitmap(frame, 8, 12);
}

void loop() {
  // Pattern stays static
}
```

## Two Frame Animation

Create simple animations by alternating between patterns.

```cpp
/*
 * Simple LED Matrix Animation
 * 
 * Adjust DISPLAY_TIME to control animation speed:
 * - Smaller number = faster animation
 * - Larger number = slower animation
 */

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
const int DISPLAY_TIME = 1000;  // 1 second per frame

byte frame1[8][12] = {
  // Pattern 1
};

byte frame2[8][12] = {
  // Pattern 2
};

void setup() {
  matrix.begin();
}

void loop() {
  matrix.renderBitmap(frame1, 8, 12);
  delay(DISPLAY_TIME);
  
  matrix.renderBitmap(frame2, 8, 12);
  delay(DISPLAY_TIME);
}