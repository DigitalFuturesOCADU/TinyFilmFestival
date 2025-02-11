/*
 * TinyFilmFestival - Simple Pressure Sensor Play/Pause Example
 * 
 * This example demonstrates using a pressure sensor to toggle play/pause state
 * of an animation. The animation starts playing automatically,
 * and pressure above threshold toggles between playing and paused states.
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - Pressure sensor connected to analog pin A0
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "idle.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object
Animation idleAnim = idle;

// Pressure sensor pins and variables
const int mushPin = A0;             // Analog input pin for pressure sensor
const int mushThreshold = 500;      // Threshold for pressure activation (adjust as needed)
int mushValue = 0;                  // Variable to store pressure reading

void setup() 
{
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
        
    // Start with animation playing in loop mode
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Animation started");
}

void loop() 
{
    // Read pressure sensor value
    mushValue = analogRead(mushPin);
    Serial.print("Input : ");
    Serial.print(mushValue);
    Serial.print(" Threshold: ");
    Serial.println(mushThreshold);

    // Check if pressure exceeds threshold
    if (mushValue > mushThreshold) 
    {
        film.pause();
        Serial.println("Animation paused");
    }
    else 
    {
        film.resume();
        //film.startAnimation(idleAnim, LOOP);
        Serial.println("Animation resumed");
    }
    
    // Update the animation frame
    film.update();

}
