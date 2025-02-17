/*
 * TinyFilmFestival - Distance-Based Speed Control Example
 * 
 * This example demonstrates using an HC-SR04 ultrasonic distance sensor to control
 * animation speed. The distance value is mapped to a speed range.
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - HC-SR04 ultrasonic distance sensor connected to pins 14 (trigger) and 15 (echo)
 */

#include "TinyFilmFestival.h"
#include "HCSR04.h"
#include "idle.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object
Animation idleAnim = idle;

// Distance sensor setup
int triggerPin = 14;          // A0 Trigger pin
int echoPin = 15;             // A1 Echo pin 
int maxDistance = 200;        // Maximum distance to measure (cm)
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin, maxDistance);

// Distance and speed control variables
float distanceMin = 0.0;        // Minimum distance reading (cm)
float distanceMax = 100.0;      // Maximum distance for speed control (cm)
int speedMin = 30;              // Minimum animation speed (fastest)
int speedMax = 300;             // Maximum animation speed (slowest)
int sensorInterval = 100;       // How often to read sensor (ms)
unsigned long lastSensorRead = 0;     // Last sensor reading time
float currentDistance = 0.0;          // Variable to store distance reading
int mappedSpeed = 0;                  // Variable to store mapped speed value

void setup() 
{
    // Initialize serial for debug output
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Start with animation playing in loop mode
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Animation started with variable speed control");
}

void loop() 
{
    // Read distance value with timing control
    float distance = readDistance();
    
    if (distance >= 0) //simple error check to be sure it returned a distance value
    {
        // Map distance to speed range
        mappedSpeed = map(constrain(distance * 10, distanceMin * 10, distanceMax * 10), 
                         distanceMin * 10, distanceMax * 10, 
                         speedMax, speedMin);

        // Print the values out to the Serial port
        Serial.print("Distance : ");
        Serial.print(distance);
        Serial.print(" cm, Mapped Speed: ");
        Serial.println(mappedSpeed);
        
        // Set animation speed
        film.setSpeed(mappedSpeed);
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