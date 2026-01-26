/*
 * TinyFilmFestival V2 - First Animation
 * 01_Basics/FirstAnimation
 * 
 * The simplest Animation Mode example. Load a pre-made animation 
 * file and play it on the LED matrix.
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

void setup() {
    film.begin();
    
    // Play animation in a loop
    // Try also: ONCE (play once) or BOOMERANG (forward/backward)
    film.startAnimation(myAnim, LOOP);
}

void loop() {
    film.update();
}
