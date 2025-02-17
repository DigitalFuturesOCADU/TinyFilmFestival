/*
 * TinyFilmFestival - Simple Distance Sensor Play/Pause Example
 * 
 * This example demonstrates using an HC-SR04 ultrasonic distance sensor to toggle 
 * play/pause state of an animation. The animation starts playing automatically,
 * and distance below threshold toggles between playing and paused states.
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * - HC-SR04 ultrasonic distance sensor connected to pins 14 (trigger) and 15 (echo)
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
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

// Distance control variables
float distanceThreshold = 30.0;  // Threshold for activation (cm)
int sensorInterval = 100;        // How often to read sensor (ms)
unsigned long lastSensorRead = 0;      // Last sensor reading time
float currentDistance = 0.0;           // Variable to store distance reading

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
    // Read distance value with timing control
    float distance = readDistance();
    
   
    if (distance >= 0) //simple error check to be sure it returned a distance value
    {
        Serial.print("Distance : ");
        Serial.print(distance);
        Serial.print(" cm, Threshold: ");
        Serial.println(distanceThreshold);

        // Check if distance is less than threshold
        if (distance < distanceThreshold) 
        {
            film.pause();
            Serial.println("Animation paused");
        }
        else 
        {
            film.resume();
            Serial.println("Animation resumed");
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