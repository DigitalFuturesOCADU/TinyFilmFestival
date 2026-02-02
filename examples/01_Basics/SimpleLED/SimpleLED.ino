/*
 * SimpleLED Example
 * 
 * Demonstrates simple LED control on the R4 WiFi matrix using
 * digitalWrite-style functions.
 * 
 * Functions:
 *   ledBegin()              - Initialize (call once in setup)
 *   ledWrite(x, y, HIGH)    - Turn on LED at column x, row y
 *   ledWrite(x, y, LOW)     - Turn off LED
 *   ledToggle(x, y)         - Toggle LED state
 *   ledRead(x, y)           - Read current state
 *   ledClear()              - Turn off all LEDs
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
 * 
 * Numbers inside = linear index for ledWrite(index, state)
 */

#include <TinyFilmFestival.h>

unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  ledBegin();  // Initialize the matrix (call once in setup)
  
  // Light up the four corners
  ledWrite(0, 0, HIGH);   // Top-left corner
  ledWrite(11, 0, HIGH);  // Top-right corner
  ledWrite(0, 7, HIGH);   // Bottom-left corner
  ledWrite(11, 7, HIGH);  // Bottom-right corner
  
  delay(2000);
  
  // Toggle corners off one by one
  ledToggle(0, 0);
  delay(300);
  ledToggle(11, 0);
  delay(300);
  ledToggle(0, 7);
  delay(300);
  ledToggle(11, 7);
  delay(300);
  
  // Draw a horizontal line across the middle
  for (int x = 0; x < 12; x++) {
    ledWrite(x, 3, HIGH);
    delay(100);
  }
  
  delay(1000);
  
  // Clear the line
  for (int x = 0; x < 12; x++) {
    ledWrite(x, 3, LOW);
    delay(100);
  }
  
  delay(500);
}

void loop() {
  // Blink center LED using a non-blocking timer
  if (millis() - lastBlinkTime >= 500) {
    lastBlinkTime = millis();
    ledState = !ledState;
    ledWrite(5, 3, ledState);
  }
}
