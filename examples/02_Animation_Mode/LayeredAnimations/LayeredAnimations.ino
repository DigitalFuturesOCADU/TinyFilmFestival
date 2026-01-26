/*
 * TinyFilmFestival V2 - Layered Animations
 * 02_Animation_Mode/LayeredAnimations
 * 
 * Play multiple animations simultaneously using TinyScreen layers.
 * Each layer runs independently with its own speed and playback mode.
 * Layers are combined (OR'd) when displayed.
 * 
 * Animation files (.h) are created using the Arduino LED Matrix Editor:
 * https://ledmatrix-editor.arduino.cc/
 * 
 * Hardware: Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 */

#include "TinyFilmFestival.h"
#include "landscape.h"
#include "fiz.h"

TinyScreen screen;

Animation bgAnim = landscape;   // Background layer
Animation fgAnim = fiz;         // Foreground layer

int fgLayer;  // Foreground layer index

void setup() {
    Serial.begin(9600);
    screen.begin();
    
    // Layer 0 (primary) - Background, slow looping
    screen.play(bgAnim, LOOP);
    screen.setSpeed(150);
    
    // Add a second layer for foreground
    fgLayer = screen.addLayer();
    
    // Configure foreground layer (fast, boomerang)
    screen.playOnLayer(fgLayer, fgAnim, BOOMERANG);
    screen.setSpeedOnLayer(fgLayer, 60);
    
    Serial.println("Layered animation running");
}

void loop() {
    // update() handles all layers automatically
    screen.update();
}
