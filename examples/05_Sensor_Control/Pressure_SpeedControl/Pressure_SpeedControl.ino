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
#include "idle.h"

TinyScreen screen;
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
    
    screen.begin();
    screen.play(idleAnim, LOOP);
    Serial.println("Press sensor to speed up animation");
}

void loop() {
    int pressure = analogRead(pressurePin);
    
    // Map pressure to speed (higher pressure = faster)
    if (pressure > minPressure) {
        pressure = constrain(pressure, minPressure, maxPressure);
        int speed = map(pressure, minPressure, maxPressure, 
                       slowSpeed, fastSpeed);
        screen.setSpeed(speed);
        
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.print(" → ");
        Serial.print(speed);
        Serial.println(" ms");
    } else {
        screen.setSpeed(slowSpeed);
    }
    
    screen.update();
}
