/*
 * TinyFilmFestival - Pressure-Based Speed Control Example
 * 
 * This example demonstrates using a pressure sensor to control
 * animation speed. The pressure value is mapped to a speed range.
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - Pressure sensor connected to analog pin A0
 */

#include "TinyFilmFestival.h"
#include "idle.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object
Animation idleAnim = idle;

// Pressure sensor pins and variables
const int mushPin = A0;             // Analog input pin for pressure sensor
const int mushMin = 0;              // Minimum pressure reading
const int mushMax = 1023;           // Maximum pressure reading
const int speedMin = 50;            // Minimum animation speed (fastest)
const int speedMax = 300;           // Maximum animation speed (slowest)
int mushValue = 0;                  // Variable to store pressure reading
int mappedSpeed = 0;                // Variable to store mapped speed value

void setup() 
{
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Setup pressure sensor pin
    pinMode(mushPin, INPUT);
    
    // Start with animation playing in loop mode
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Animation started with variable speed control");
}

void loop() 
{
    // Read pressure sensor value
    mushValue = analogRead(mushPin);
    
    // Map pressure to speed range
    mappedSpeed = map(mushValue, mushMin, mushMax, speedMax, speedMin);

    // Print the values out to the Serial port
    Serial.print("Sensor Val : ");
    Serial.print(mushValue);
    Serial.print(" Re-Mapped Speed: ");
    Serial.println(mappedSpeed);

    
    // Set animation speed
    film.setSpeed(mappedSpeed);
    
    
    // Update the animation frame
    film.update();
}