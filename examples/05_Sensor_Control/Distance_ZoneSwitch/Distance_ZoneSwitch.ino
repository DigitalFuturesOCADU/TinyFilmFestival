/*
 * TinyFilmFestival V2 - Distance Zone Switch
 * 05_Sensor_Control/Distance_ZoneSwitch
 * 
 * Switch animations based on distance zones.
 * Creates an "interactive zone" effect around the display.
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
#include "go.h"

TinyFilmFestival film;
Animation idleAnim = idle;
Animation goAnim = go;

// Distance sensor
const int trigPin = A0;
const int echoPin = A1;
UltraSonicDistanceSensor sensor(trigPin, echoPin, 200);

// Zone threshold
const float threshold = 40.0;   // cm - switch point

unsigned long lastRead = 0;
const int readInterval = 100;
bool inCloseZone = false;

void setup() {
    Serial.begin(9600);
    film.begin();
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Move closer than 40cm to trigger 'go' animation");
}

void loop() {
    if (millis() - lastRead > readInterval) {
        float dist = sensor.measureDistanceCm();
        
        if (dist > 0) {
            bool nowClose = (dist < threshold);
            
            // Only switch when crossing threshold
            if (nowClose && !inCloseZone) {
                film.startAnimation(goAnim, LOOP);
                Serial.println("CLOSE - playing: go");
            } else if (!nowClose && inCloseZone) {
                film.startAnimation(idleAnim, LOOP);
                Serial.println("FAR - playing: idle");
            }
            
            inCloseZone = nowClose;
        }
        lastRead = millis();
    }
    
    film.update();
}
