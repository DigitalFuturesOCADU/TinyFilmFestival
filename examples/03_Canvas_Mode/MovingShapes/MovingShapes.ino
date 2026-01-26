/*
 * TinyFilmFestival - Canvas Mode - MovingShapes
 * 
 * Code-generated animations with different motion behaviors.
 * This mirrors the Animation Mode PlayModes (ONCE, LOOP, BOOMERANG)
 * but creates the motion entirely with code.
 * 
 * This example demonstrates:
 *   - Three motion types: ONCE, LOOP, BOOMERANG
 *   - Drawing filled shapes (circle)
 *   - Using Serial to switch between modes
 *   - State machine for animation control
 * 
 * Mode: Canvas
 * Mirrors: 02_Animation_Mode/PlaybackControl
 * 
 * Hardware Required:
 *   - Arduino UNO R4 WiFi
 * 
 * Usage:
 *   Open Serial Monitor and send:
 *   '1' = ONCE mode (shape crosses screen and stops)
 *   '2' = LOOP mode (shape wraps around continuously)
 *   '3' = BOOMERANG mode (shape bounces back and forth)
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Motion modes (mirrors Animation PlayModes)
enum MotionMode {
    MODE_ONCE,
    MODE_LOOP,
    MODE_BOOMERANG
};

// Animation state
int x = 0;
int direction = 1;
MotionMode currentMode = MODE_LOOP;
bool completed = false;

// Timing
unsigned long lastMove = 0;
int speed = 80;  // milliseconds per frame

void setup() {
    Serial.begin(9600);
    matrix.begin();
    
    Serial.println("=== MovingShapes ===");
    Serial.println("Send: 1=ONCE, 2=LOOP, 3=BOOMERANG");
    Serial.println("Starting in LOOP mode");
}

void loop() {
    // Check for mode changes via Serial
    if (Serial.available()) {
        char c = Serial.read();
        switch(c) {
            case '1':
                currentMode = MODE_ONCE;
                resetAnimation();
                Serial.println("Mode: ONCE");
                break;
            case '2':
                currentMode = MODE_LOOP;
                resetAnimation();
                Serial.println("Mode: LOOP");
                break;
            case '3':
                currentMode = MODE_BOOMERANG;
                resetAnimation();
                Serial.println("Mode: BOOMERANG");
                break;
        }
    }
    
    // Update position at specified speed
    if (millis() - lastMove >= speed && !completed) {
        updatePosition();
        lastMove = millis();
    }
    
    // Draw the shape
    matrix.beginDraw();
    matrix.clear();
    matrix.fill(0xFFFFFF);    // Filled shape
    matrix.stroke(0xFFFFFF);  // With outline
    matrix.circle(x, 4, 4);   // Circle at current x position
    matrix.endDraw();
}

void updatePosition() {
    x += direction;
    
    switch(currentMode) {
        case MODE_ONCE:
            // Stop when reaching the far edge
            if (x >= 10) {
                x = 10;
                completed = true;
                Serial.println("Animation complete");
            }
            break;
            
        case MODE_LOOP:
            // Wrap around when exiting screen
            if (x > 13) {
                x = -2;  // Start just off the left edge
            }
            break;
            
        case MODE_BOOMERANG:
            // Bounce at edges
            if (x >= 10 || x <= 1) {
                direction *= -1;
            }
            break;
    }
}

void resetAnimation() {
    x = 1;
    direction = 1;
    completed = false;
}
