/*
 * TinyFilmFestival - Distance-Controlled Combined Animation
 * 
 * This example shows how to:
 *   - Play a continuous looping background animation
 *   - Trigger a second animation with distance
 *   - Combine multiple animations using CombinedFilmFestival
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - HC-SR04 ultrasonic distance sensor connected to pins 14 (trigger) and 15 (echo)
 */

#include "TinyFilmFestival.h"
#include "HCSR04.h"
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
int backgroundSpeed = 100;    // Speed for landscape (milliseconds)
int effectSpeed = 50;         // Speed for fiz effect (milliseconds)

// Distance sensor setup
int triggerPin = 14;          // A0 Trigger pin for HC-SR04
int echoPin = 15;             // A1 Echo pin for HC-SR04
int maxDistance = 200;        // Maximum distance to measure (cm)
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin, maxDistance);

// Distance control variables
float distanceThreshold = 50.0;  // Threshold for effect trigger (cm)
int sensorInterval = 100;        // How often to read sensor (ms)
unsigned long lastSensorRead = 0;      // Last sensor reading time
float currentDistance = 0.0;           // Variable to store distance reading

void setup() 
{
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("Starting distance-controlled animation demo");
    
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
    // Read distance value with timing control
    float distance = readDistance();
    
    if (distance >= 0) //simple error check to be sure it returned a distance value
    {
        Serial.print("Distance : ");
        Serial.print(distance);
        Serial.print(" cm, Threshold: ");
        Serial.println(distanceThreshold);

        // Check distance against threshold
        if (distance < distanceThreshold) 
        {
            // Close distance - start effect
            effectFilm.startAnimation(fizAnim, LOOP);
            Serial.println("Effect started");
        } 
        else 
        {
            // Far distance - stop effect
            effectFilm.stop();
            Serial.println("Effect stopped");
        }
    }
    
    // Update the combined animation
    combinedFilm.update();
}

// Reads distance from the HC-SR04 sensor at specified intervals
// Function returns float since HC-SR04 can measure partial centimeters
float readDistance()
{
    unsigned long currentTime = millis();
    
    // Only read sensor if interval has elapsed
    if (currentTime - lastSensorRead >= sensorInterval)
    {
        currentDistance = distanceSensor.measureDistanceCm();
        lastSensorRead = currentTime;
    }
    
    return currentDistance;
}