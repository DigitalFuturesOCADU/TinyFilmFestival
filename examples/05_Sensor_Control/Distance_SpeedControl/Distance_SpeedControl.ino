/*
 * TinyFilmFestival V2 - Distance Speed Control
 * 05_Sensor_Control/Distance_SpeedControl
 * 
 * Control animation speed with an ultrasonic distance sensor.
 * Closer = faster, farther = slower.
 * 
 * Hardware:
 * - Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 * - HC-SR04 ultrasonic sensor (Trigger: A0, Echo: A1)
 * 
 * Library: HCSR04 by Martin Sosic
 */

#include "TinyFilmFestival.h"
#include "HCSR04.h"
#include "idle.h"

TinyFilmFestival film;
Animation idleAnim = idle;

// Distance sensor
const int trigPin = A0;
const int echoPin = A1;
UltraSonicDistanceSensor sensor(trigPin, echoPin, 200);

// Speed mapping
const float minDist = 5.0;      // cm - closest reading
const float maxDist = 80.0;     // cm - farthest to respond
const int fastSpeed = 30;       // ms per frame (closest)
const int slowSpeed = 250;      // ms per frame (farthest)

unsigned long lastRead = 0;
const int readInterval = 100;   // ms between sensor reads

void setup() {
    Serial.begin(9600);
    film.begin();
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Move hand closer/farther to control speed");
}

void loop() {
    // Read sensor at intervals
    if (millis() - lastRead > readInterval) {
        float dist = sensor.measureDistanceCm();
        
        if (dist > 0) {
            // Constrain and map distance to speed
            dist = constrain(dist, minDist, maxDist);
            int speed = map(dist * 10, minDist * 10, maxDist * 10, 
                           fastSpeed, slowSpeed);
            
            film.setSpeed(speed);
            
            Serial.print(dist);
            Serial.print(" cm → ");
            Serial.print(speed);
            Serial.println(" ms");
        }
        lastRead = millis();
    }
    
    film.update();
}
