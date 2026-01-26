/*
 * TinyFilmFestival V2 - Animation With Overlay
 * 04_Hybrid_Mode/AnimationWithOverlay
 * 
 * Combines a pre-made animation with code-drawn graphics.
 * The animation plays normally while a live indicator bar
 * animates independently on top.
 * 
 * This example demonstrates:
 *   - Playing a pre-made animation with play()
 *   - Drawing graphics over the animation with beginOverlay()/endOverlay()
 *   - Independent timing for overlay animation
 *   - The hybrid approach: best of both worlds
 * 
 * Hardware: Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 */

#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation backgroundAnim = idle;

// Overlay: animated indicator bar on the right edge
int indicatorLevel = 0;
int indicatorDirection = 1;
unsigned long lastIndicatorUpdate = 0;
const int INDICATOR_SPEED = 150;

void setup() {
    screen.begin();
    screen.play(backgroundAnim, LOOP);
    screen.setSpeed(100);
}

void loop() {
    // Update overlay indicator independently
    if (millis() - lastIndicatorUpdate >= INDICATOR_SPEED) {
        indicatorLevel += indicatorDirection;
        if (indicatorLevel >= 7 || indicatorLevel <= 0) {
            indicatorDirection *= -1;
        }
        lastIndicatorUpdate = millis();
    }
    
    // beginOverlay() updates animation AND starts drawing mode
    screen.beginOverlay();
    
    // Draw indicator bar on the right edge (column 11)
    for (int y = 7; y > 7 - indicatorLevel; y--) {
        screen.point(11, y);
    }
    
    // Draw corner brackets as a frame
    // Top-left
    screen.point(0, 0);
    screen.point(1, 0);
    screen.point(0, 1);
    
    // Top-right (leave room for indicator)
    screen.point(9, 0);
    screen.point(10, 0);
    
    // Bottom-left
    screen.point(0, 7);
    screen.point(1, 7);
    screen.point(0, 6);
    
    // Bottom-right
    screen.point(9, 7);
    screen.point(10, 7);
    
    screen.endOverlay();
}
