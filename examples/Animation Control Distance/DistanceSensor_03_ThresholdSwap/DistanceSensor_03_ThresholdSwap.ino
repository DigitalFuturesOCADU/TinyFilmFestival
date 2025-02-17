/*
 * TinyFilmFestival - Distance-Based Animation Switch Example
 * 
 * This example demonstrates switching between animations based on distance.
 * Animation selection uses a simple threshold.
 * 
 * To extend for more animations:
 * 1. Add more animation includes and objects:
 *    #include "anim3.h"
 *    Animation anim3Anim = anim3;
 * 
 * 2. Add more thresholds and conditions:
 *    const float distanceThreshold2 = 70.0;
 *    if (distance < distanceThreshold2) {
 *        film.startAnimation(anim3Anim, LOOP);
 *    } else if (distance < distanceThreshold) {
 *        film.startAnimation(goAnim, LOOP);
 *    } else {
 *        film.startAnimation(idleAnim, LOOP);
 *    }
 */

#include "TinyFilmFestival.h"
#include "HCSR04.h"
#include "idle.h"
#include "go.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation objects
Animation idleAnim = idle;
Animation goAnim = go;

// Distance sensor setup
int triggerPin = 14;          // A0 Trigger pin for HC-SR04
int echoPin = 15;             // A1 Echo pin for HC-SR04
int maxDistance = 200;        // Maximum distance to measure (cm)
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin, maxDistance);

// Distance control variables
float distanceThreshold = 50.0;  // Threshold for animation switch (cm)
int sensorInterval = 100;        // How often to read sensor (ms)
unsigned long lastSensorRead = 0;      // Last sensor reading time
float currentDistance = 0.0;           // Variable to store distance reading

void setup() 
{
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Start with idle animation
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Starting with idle animation");
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

        // Switch animations based on distance
        if (distance < distanceThreshold) 
        {
            film.startAnimation(goAnim, LOOP);
            Serial.println("Playing Go");
        } 
        else 
        {
            film.startAnimation(idleAnim, LOOP);
            Serial.println("Playing Idle");
        }
    }
    
    // Update the animation frame
    film.update();
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