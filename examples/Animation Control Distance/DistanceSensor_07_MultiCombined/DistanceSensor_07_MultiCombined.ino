/*
 * TinyFilmFestival - Multi-Layer Distance Animation Example
 * 
 * This example demonstrates combining multiple animations based on distance ranges.
 * As distance increases, more animations are layered on top of each other:
 * - Very Close: Single animation
 * - Close: Two animations combined
 * - Medium: Three animations combined
 * - Far: All four animations combined
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - HC-SR04 ultrasonic distance sensor connected to pins 14 (trigger) and 15 (echo)
 */

#include "TinyFilmFestival.h"
#include "HCSR04.h"
#include "idle.h"
#include "go.h"
#include "fiz.h"
#include "landscape.h"

// Create TinyFilmFestival objects for each animation layer
TinyFilmFestival fizFilm;
TinyFilmFestival goFilm;
TinyFilmFestival landscapeFilm;
TinyFilmFestival idleFilm;

// Create a CombinedFilmFestival to merge the animations
CombinedFilmFestival combinedFilm;

// Create Animation objects
Animation idleAnim = idle;
Animation goAnim = go;
Animation fizAnim = fiz;
Animation landscapeAnim = landscape;

// Distance sensor setup
int triggerPin = 14;          // Trigger pin for HC-SR04
int echoPin = 15;             // Echo pin for HC-SR04
int maxDistance = 200;        // Maximum distance to measure (cm)
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin, maxDistance);

// Distance control variables
float distanceThreshold1 = 25.0;  // First threshold (cm)
float distanceThreshold2 = 50.0;  // Second threshold (cm)
float distanceThreshold3 = 75.0;  // Third threshold (cm)
int sensorInterval = 100;         // How often to read sensor (ms)
unsigned long lastSensorRead = 0;       // Last sensor reading time
float currentDistance = 0.0;            // Variable to store distance reading

// Animation speed settings
int fizSpeed = 50;        // Speed for fiz animation
int goSpeed = 100;        // Speed for go animation
int landscapeSpeed = 150; // Speed for landscape animation
int idleSpeed = 200;      // Speed for idle animation

void setup() 
{
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the combined matrix
    combinedFilm.begin();
    
    // Configure individual animations
    fizFilm.startAnimation(fizAnim, LOOP);
    fizFilm.setSpeed(fizSpeed);
    fizFilm.stop();
    
    goFilm.startAnimation(goAnim, LOOP);
    goFilm.setSpeed(goSpeed);
    goFilm.stop();
    
    landscapeFilm.startAnimation(landscapeAnim, LOOP);
    landscapeFilm.setSpeed(landscapeSpeed);
    landscapeFilm.stop();
    
    idleFilm.startAnimation(idleAnim, LOOP);
    idleFilm.setSpeed(idleSpeed);
    idleFilm.stop();
    
    // Add all animations to the combiner
    combinedFilm.addFilm(fizFilm);
    combinedFilm.addFilm(goFilm);
    combinedFilm.addFilm(landscapeFilm);
    combinedFilm.addFilm(idleFilm);
    
    Serial.println("Starting layered animation system");
}

void loop() 
{
    // Read distance value with timing control
    float distance = readDistance();
    
    if (distance >= 0)
    {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");

        // Switch animations based on distance ranges
        // Very Close Range: 0cm to 25cm (exclusive)
        // Only shows the fiz animation
        if ((distance >= 0) && (distance < distanceThreshold1))
        {
            // Start the closest layer
            fizFilm.startAnimation(fizAnim, LOOP);
            
            // Stop all other layers
            goFilm.stop();
            landscapeFilm.stop();
            idleFilm.stop();
            
            Serial.println("Layer 1: Fiz (Very Close)");
        }
        // Close Range: 25cm (inclusive) to 50cm (exclusive)
        // Shows fiz and go animations combined
        else if ((distance >= distanceThreshold1) && (distance < distanceThreshold2))
        {
            // Start first two layers
            fizFilm.startAnimation(fizAnim, LOOP);
            goFilm.startAnimation(goAnim, LOOP);
            
            // Stop outer layers
            landscapeFilm.stop();
            idleFilm.stop();
            
            Serial.println("Layer 1-2: Fiz + Go (Close)");
        }
        // Medium Range: 50cm (inclusive) to 75cm (exclusive)
        // Shows fiz, go, and landscape animations combined
        else if ((distance >= distanceThreshold2) && (distance < distanceThreshold3))
        {
            // Start first three layers
            fizFilm.startAnimation(fizAnim, LOOP);
            goFilm.startAnimation(goAnim, LOOP);
            landscapeFilm.startAnimation(landscapeAnim, LOOP);
            
            // Stop outer layer
            idleFilm.stop();
            
            Serial.println("Layer 1-3: Fiz + Go + Landscape (Medium)");
        }
        // Far Range: 75cm and beyond
        // Shows all animations combined
        else if (distance >= distanceThreshold3)
        {
            // Start all layers
            fizFilm.startAnimation(fizAnim, LOOP);
            goFilm.startAnimation(goAnim, LOOP);
            landscapeFilm.startAnimation(landscapeAnim, LOOP);
            idleFilm.startAnimation(idleAnim, LOOP);
            
            Serial.println("Layer 1-4: Fiz + Go + Landscape + Idle (Far)");
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