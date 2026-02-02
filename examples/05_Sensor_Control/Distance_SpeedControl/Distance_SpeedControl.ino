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
 * 
 * LED Matrix Layout (12 columns x 8 rows):
 * 
 *      x=0  x=1  x=2  x=3  x=4  x=5  x=6  x=7  x=8  x=9  x=10 x=11
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=0 |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=1 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=2 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=3 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=4 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=5 | 60 | 61 | 62 | 63 | 64 | 65 | 66 | 67 | 68 | 69 | 70 | 71 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=6 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 | 81 | 82 | 83 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 * y=7 | 84 | 85 | 86 | 87 | 88 | 89 | 90 | 91 | 92 | 93 | 94 | 95 |
 *     +----+----+----+----+----+----+----+----+----+----+----+----+
 */

#include "TinyFilmFestival.h"
#include "HCSR04.h"
#include "idle.h"

TinyScreen screen;
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
    screen.begin();
    screen.play(idleAnim, LOOP);
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
            
            screen.setSpeed(speed);
            
            Serial.print(dist);
            Serial.print(" cm → ");
            Serial.print(speed);
            Serial.println(" ms");
        }
        lastRead = millis();
    }
    
    screen.update();
}
