/*
 * TinyFilmFestival - Canvas Mode - LayeredGraphics
 * 
 * Multiple independent animated elements on screen,
 * each moving at its own speed. This mirrors LayeredAnimations
 * from Animation Mode but creates everything with code.
 * 
 * This example demonstrates:
 *   - Multiple animation states (position, direction, timing)
 *   - Independent speed control per element
 *   - Combining different shapes in one scene
 *   - Non-blocking timing with millis()
 * 
 * Mode: Canvas
 * Mirrors: 02_Animation_Mode/LayeredAnimations
 * 
 * Hardware Required:
 *   - Arduino UNO R4 WiFi
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// === Layer 1: Slow horizontal scan line (background) ===
int scanY = 0;
int scanDirection = 1;
unsigned long lastScanUpdate = 0;
const int SCAN_SPEED = 200;  // Slow: 200ms per step

// === Layer 2: Fast bouncing dot (foreground) ===
int dotX = 6;
int dotDirection = 1;
unsigned long lastDotUpdate = 0;
const int DOT_SPEED = 50;  // Fast: 50ms per step

// === Layer 3: Pulsing center ring (medium speed) ===
int ringSize = 2;
int ringDirection = 1;
unsigned long lastRingUpdate = 0;
const int RING_SPEED = 120;  // Medium: 120ms per step

void setup() {
    matrix.begin();
}

void loop() {
    unsigned long currentTime = millis();
    
    // Update Layer 1: Scan line (slow)
    if (currentTime - lastScanUpdate >= SCAN_SPEED) {
        scanY += scanDirection;
        if (scanY >= 7 || scanY <= 0) {
            scanDirection *= -1;
        }
        lastScanUpdate = currentTime;
    }
    
    // Update Layer 2: Bouncing dot (fast)
    if (currentTime - lastDotUpdate >= DOT_SPEED) {
        dotX += dotDirection;
        if (dotX >= 11 || dotX <= 0) {
            dotDirection *= -1;
        }
        lastDotUpdate = currentTime;
    }
    
    // Update Layer 3: Pulsing ring (medium)
    if (currentTime - lastRingUpdate >= RING_SPEED) {
        ringSize += ringDirection;
        if (ringSize >= 4 || ringSize <= 1) {
            ringDirection *= -1;
        }
        lastRingUpdate = currentTime;
    }
    
    // Draw all layers
    matrix.beginDraw();
    matrix.clear();
    matrix.stroke(0xFFFFFF);
    
    // Layer 1: Horizontal scan line
    matrix.line(0, scanY, 11, scanY);
    
    // Layer 2: Bouncing dot
    matrix.point(dotX, 4);
    
    // Layer 3: Pulsing ring (outline only)
    matrix.noFill();
    matrix.circle(6, 4, ringSize * 2);
    
    matrix.endDraw();
}
