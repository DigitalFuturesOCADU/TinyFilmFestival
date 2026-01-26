/*
 * TinyFilmFestival V2 - Pressure Speed Control
 * 05_Sensor_Control/Pressure_SpeedControl
 * 
 * Control animation speed with a pressure/force sensor.
 * Harder press = faster animation.
 * 
 * Hardware:
 * - Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 * - Pressure/force sensor on analog pin A0
 */

#include "TinyFilmFestival.h"
#include "idle.h"

TinyFilmFestival film;
Animation idleAnim = idle;

const int pressurePin = A0;

// Speed mapping
const int minPressure = 50;     // Ignore noise below this
const int maxPressure = 900;    // Max expected reading
const int slowSpeed = 200;      // ms (no pressure)
const int fastSpeed = 30;       // ms (max pressure)

void setup() {
    Serial.begin(9600);
    pinMode(pressurePin, INPUT);
    
    film.begin();
    film.startAnimation(idleAnim, LOOP);
    Serial.println("Press sensor to speed up animation");
}

void loop() {
    int pressure = analogRead(pressurePin);
    
    // Map pressure to speed (higher pressure = faster)
    if (pressure > minPressure) {
        pressure = constrain(pressure, minPressure, maxPressure);
        int speed = map(pressure, minPressure, maxPressure, 
                       slowSpeed, fastSpeed);
        film.setSpeed(speed);
        
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.print(" → ");
        Serial.print(speed);
        Serial.println(" ms");
    } else {
        film.setSpeed(slowSpeed);
    }
    
    film.update();
}
