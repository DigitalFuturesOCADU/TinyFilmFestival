/*
 * TinyFilmFestival V2 - Playback Control
 * 02_Animation_Mode/PlaybackControl
 * 
 * Demonstrates all Animation Mode playback options:
 * - Playback modes: ONCE, LOOP, BOOMERANG
 * - Speed control: setSpeed(), restoreOriginalSpeed()
 * - Partial playback: play specific frame ranges
 * 
 * Animation files (.h) are created using the Arduino LED Matrix Editor:
 * https://ledmatrix-editor.arduino.cc/
 * 
 * Hardware: Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 */

#include "TinyFilmFestival.h"
#include "animation.h"

TinyFilmFestival film;
Animation myAnim = animation;

// Demo cycling
int demoMode = 0;
unsigned long lastChange = 0;
const int demoDuration = 4000;

void setup() {
    Serial.begin(9600);
    film.begin();
    
    Serial.print("Animation has ");
    Serial.print(myAnim.getFrameCount());
    Serial.println(" frames");
    
    startDemo(0);
}

void loop() {
    // Cycle through demos every few seconds
    if (millis() - lastChange > demoDuration) {
        demoMode = (demoMode + 1) % 5;
        startDemo(demoMode);
        lastChange = millis();
    }
    
    film.update();
}

void startDemo(int mode) {
    switch (mode) {
        case 0:
            // LOOP: continuous forward playback
            film.startAnimation(myAnim, LOOP);
            film.restoreOriginalSpeed();
            Serial.println("Mode: LOOP (normal speed)");
            break;
            
        case 1:
            // BOOMERANG: forward then backward
            film.startAnimation(myAnim, BOOMERANG);
            Serial.println("Mode: BOOMERANG");
            break;
            
        case 2:
            // Fast speed
            film.startAnimation(myAnim, LOOP);
            film.setSpeed(30);
            Serial.println("Mode: LOOP (fast - 30ms)");
            break;
            
        case 3:
            // Slow speed
            film.startAnimation(myAnim, LOOP);
            film.setSpeed(200);
            Serial.println("Mode: LOOP (slow - 200ms)");
            break;
            
        case 4:
            // Partial playback: frames 2-5 only
            film.startAnimation(myAnim, LOOP, 2, 5);
            film.restoreOriginalSpeed();
            Serial.println("Mode: LOOP (frames 2-5 only)");
            break;
    }
}
