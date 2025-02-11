/*
 * TinyFilmFestival - Pressure-Based Animation Switch Example
 * 
 * This example demonstrates switching between animations based on pressure.
 * Animation selection uses a simple threshold.
 * 
 * To extend for more animations:
 * 1. Add more animation includes and objects:
 *    #include "anim3.h"
 *    Animation anim3Anim = anim3;
 * 
 * 2. Add more thresholds and conditions:
 *    const int mushThreshold2 = 700;
 *    if (mushValue > mushThreshold2) {
 *        film.startAnimation(anim3Anim, LOOP);
 *    } else if (mushValue > mushThreshold) {
 *        film.startAnimation(goAnim, LOOP);
 *    } else {
 *        film.startAnimation(idleAnim, LOOP);
 *    }
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation objects
Animation idleAnim = idle;
Animation goAnim = go;

// Pressure sensor pins and variables
const int mushPin = A0;             // Analog input pin for pressure sensor
const int mushThreshold = 500;      // Threshold for animation switch
int mushValue = 0;                  // Variable to store pressure reading

void setup() 
{
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Setup pressure sensor pin
    pinMode(mushPin, INPUT);
    
    // Start with idle animation
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Starting with idle animation");
}

void loop() 
{
    // Read pressure sensor value
    mushValue = analogRead(mushPin);

    // Switch animations based on pressure
    if (mushValue > mushThreshold) 
    {
        film.startAnimation(goAnim, LOOP);
        Serial.println("Playing Go");
    } 
    else 
    {
        film.startAnimation(idleAnim, LOOP);
        Serial.println("Playing Idle");
    }
    
    // Update the animation frame
    film.update();
}

