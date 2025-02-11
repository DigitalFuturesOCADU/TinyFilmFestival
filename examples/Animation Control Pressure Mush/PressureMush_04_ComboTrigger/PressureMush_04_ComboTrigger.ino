/*
 * TinyFilmFestival - Pressure-Controlled Combined Animation
 * 
 * This example shows how to:
 *   - Play a continuous looping background animation
 *   - Trigger a second animation with pressure
 *   - Combine multiple animations using CombinedFilmFestival
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - Pressure sensor connected to analog pin A0
 */

#include "TinyFilmFestival.h"
#include "landscape.h"    // Background animation
#include "fiz.h"         // Effect animation

// Create TinyFilmFestival objects for each animation
TinyFilmFestival backgroundFilm;
TinyFilmFestival effectFilm;

// Create a CombinedFilmFestival to merge the animations
CombinedFilmFestival combinedFilm;

// Create Animation objects from the frame data
Animation landscapeAnim = landscape;
Animation fizAnim = fiz;

// Animation control settings
const int backgroundSpeed = 100;    // Speed for landscape (milliseconds)
const int effectSpeed = 50;         // Speed for fiz effect (milliseconds)

// Pressure sensor pins and variables
const int mushPin = A0;             // Analog input pin for pressure sensor
const int mushThreshold = 500;      // Threshold for effect trigger
int mushValue = 0;                  // Variable to store pressure reading

void setup() 
{
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("Starting pressure-controlled animation demo");
    
    // Setup pressure sensor pin
    pinMode(mushPin, INPUT);
    
    // Start the LED matrix
    combinedFilm.begin();
    
    // Configure background animation (continuous loop)
    backgroundFilm.startAnimation(landscapeAnim, LOOP);
    backgroundFilm.setSpeed(backgroundSpeed);
    
    // Configure effect animation (starts stopped)
    effectFilm.startAnimation(fizAnim, LOOP);
    effectFilm.setSpeed(effectSpeed);
    effectFilm.stop();
    
    // Add animations to the combiner
    combinedFilm.addFilm(backgroundFilm);  // Landscape in background
    combinedFilm.addFilm(effectFilm);      // Effect in foreground
}

void loop() 
{
    // Read pressure sensor value
    mushValue = analogRead(mushPin);
    
    // Check pressure against threshold
    if (mushValue > mushThreshold) 
    {
        // High pressure - start effect
        effectFilm.startAnimation(fizAnim, LOOP);
        Serial.println("Effect started");
    } 
    else 
    {
        // Low pressure - stop effect
        effectFilm.stop();
        Serial.println("Effect stopped");
    }
    
    // Update the combined animation
    combinedFilm.update();
}