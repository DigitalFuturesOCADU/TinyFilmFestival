/*
 * TinyFilmFestival - Hybrid Mode - AnimationWithOverlay
 * 
 * Combines a pre-made animation with code-drawn graphics.
 * The animation plays normally while a live indicator bar
 * animates independently on top.
 * 
 * This example demonstrates:
 *   - Playing a pre-made animation
 *   - Drawing graphics over the animation
 *   - Independent timing for overlay animation
 *   - The hybrid approach: best of both worlds
 * 
 * Mode: Hybrid (Animation + Canvas)
 * 
 * Hardware Required:
 *   - Arduino UNO R4 WiFi
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "TinyFilmFestival.h"
#include "idle.h"

// Animation player for the background
TinyFilmFestival film;
Animation backgroundAnim = idle;

// Overlay: animated indicator bar on the right edge
int indicatorLevel = 0;
int indicatorDirection = 1;
unsigned long lastIndicatorUpdate = 0;
const int INDICATOR_SPEED = 150;

// We need direct matrix access for overlay drawing
ArduinoLEDMatrix matrix;

void setup() {
    // Initialize the animation player
    film.begin();
    film.startAnimation(backgroundAnim, LOOP);
    film.setSpeed(100);
}

void loop() {
    // Update the background animation
    film.update();
    
    // Update overlay indicator independently
    if (millis() - lastIndicatorUpdate >= INDICATOR_SPEED) {
        indicatorLevel += indicatorDirection;
        if (indicatorLevel >= 7 || indicatorLevel <= 0) {
            indicatorDirection *= -1;
        }
        lastIndicatorUpdate = millis();
    }
    
    // Draw the overlay on top of the current animation frame
    // Note: This draws after film.update() so it appears on top
    matrix.beginDraw();
    matrix.stroke(0xFFFFFF);
    
    // Draw indicator bar on the right edge (column 11)
    for (int y = 7; y > 7 - indicatorLevel; y--) {
        matrix.point(11, y);
    }
    
    // Draw corner brackets as a frame
    // Top-left
    matrix.point(0, 0);
    matrix.point(1, 0);
    matrix.point(0, 1);
    
    // Top-right (leave room for indicator)
    matrix.point(9, 0);
    matrix.point(10, 0);
    
    // Bottom-left
    matrix.point(0, 7);
    matrix.point(1, 7);
    matrix.point(0, 6);
    
    // Bottom-right
    matrix.point(9, 7);
    matrix.point(10, 7);
    
    matrix.endDraw();
}
