/*
 * TinyFilmFestival V2 - Layered Animations
 * 02_Animation_Mode/LayeredAnimations
 * 
 * Play multiple animations simultaneously using CombinedFilmFestival.
 * Animations are layered - earlier added = background, later = foreground.
 * Each animation runs independently with its own speed and playback mode.
 * 
 * Animation files (.h) are created using the Arduino LED Matrix Editor:
 * https://ledmatrix-editor.arduino.cc/
 * 
 * Hardware: Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 */

#include "TinyFilmFestival.h"
#include "landscape.h"
#include "fiz.h"

// Individual animation players
TinyFilmFestival film1;
TinyFilmFestival film2;

// Combines multiple animations into one output
CombinedFilmFestival combined;

Animation bgAnim = landscape;   // Background layer
Animation fgAnim = fiz;         // Foreground layer

void setup() {
    Serial.begin(9600);
    combined.begin();
    
    // Configure background (slow, looping)
    film1.startAnimation(bgAnim, LOOP);
    film1.setSpeed(150);
    
    // Configure foreground (fast, boomerang)
    film2.startAnimation(fgAnim, BOOMERANG);
    film2.setSpeed(60);
    
    // Add layers (order matters: first = back, last = front)
    combined.addFilm(film1);
    combined.addFilm(film2);
    
    Serial.println("Layered animation running");
}

void loop() {
    combined.update();
}
