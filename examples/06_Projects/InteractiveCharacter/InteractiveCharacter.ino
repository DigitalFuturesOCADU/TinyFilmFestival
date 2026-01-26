/*
 * TinyFilmFestival - Project - InteractiveCharacter
 * 
 * A complete project combining Animation Mode, Canvas Mode, and Sensors.
 * A character on the LED matrix reacts to proximity:
 * 
 *   FAR (>60cm):      Sleeping - slow idle animation, dim
 *   MEDIUM (30-60cm): Alert - normal speed idle
 *   CLOSE (15-30cm):  Excited - fast "go" animation + sparkle overlay
 *   VERY CLOSE (<15cm): Overwhelmed - animation pauses, warning flash
 * 
 * This example demonstrates:
 *   - Multi-zone sensor interaction
 *   - Animation switching based on state
 *   - Speed control based on proximity
 *   - Hybrid overlay effects (sparkles)
 *   - Complete project structure
 * 
 * Mode: Hybrid (Animation + Canvas + Sensor)
 * 
 * Hardware Required:
 *   - Arduino UNO R4 WiFi
 *   - HC-SR04 Ultrasonic Distance Sensor
 *     - Trigger: Pin 14 (A0)
 *     - Echo: Pin 15 (A1)
 * 
 * Libraries Required:
 *   - TinyFilmFestival
 *   - HCSR04 (install from Library Manager)
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "TinyFilmFestival.h"
#include "HCSR04.h"
#include "idle.h"
#include "go.h"

// === Hardware Setup ===
UltraSonicDistanceSensor sensor(14, 15, 200);  // trigger, echo, maxDistance
ArduinoLEDMatrix matrix;

// === Animation Setup ===
TinyFilmFestival film;
Animation idleAnim = idle;
Animation goAnim = go;

// === Character States ===
enum CharacterState {
    SLEEPING,
    ALERT,
    EXCITED,
    OVERWHELMED
};

CharacterState currentState = SLEEPING;
CharacterState previousState = SLEEPING;

// === Timing ===
unsigned long lastSensorRead = 0;
const int SENSOR_INTERVAL = 100;  // Read sensor every 100ms

unsigned long lastSparkle = 0;
const int SPARKLE_INTERVAL = 50;

unsigned long lastFlash = 0;
bool flashOn = false;

// === Sparkle overlay positions ===
int sparkleX = 0;
int sparkleY = 0;

void setup() {
    Serial.begin(9600);
    film.begin();
    
    // Start in sleeping state
    film.startAnimation(idleAnim, LOOP);
    film.setSpeed(300);  // Very slow for sleeping
    
    Serial.println("=== Interactive Character ===");
    Serial.println("Approach the sensor to wake the character!");
}

void loop() {
    // Read distance sensor
    float distance = readDistance();
    
    // Determine character state based on distance
    CharacterState newState = determineState(distance);
    
    // Handle state changes
    if (newState != currentState) {
        previousState = currentState;
        currentState = newState;
        onStateChange();
    }
    
    // Update animation
    film.update();
    
    // Draw overlays based on state
    drawOverlay();
    
    // Debug output
    static unsigned long lastDebug = 0;
    if (millis() - lastDebug > 500) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.print(" cm, State: ");
        Serial.println(getStateName(currentState));
        lastDebug = millis();
    }
}

float readDistance() {
    static float lastDistance = 100;
    
    if (millis() - lastSensorRead >= SENSOR_INTERVAL) {
        float d = sensor.measureDistanceCm();
        if (d > 0) {
            lastDistance = d;
        }
        lastSensorRead = millis();
    }
    return lastDistance;
}

CharacterState determineState(float distance) {
    if (distance < 15) {
        return OVERWHELMED;
    } else if (distance < 30) {
        return EXCITED;
    } else if (distance < 60) {
        return ALERT;
    } else {
        return SLEEPING;
    }
}

void onStateChange() {
    switch (currentState) {
        case SLEEPING:
            film.startAnimation(idleAnim, LOOP);
            film.setSpeed(300);  // Very slow
            break;
            
        case ALERT:
            film.startAnimation(idleAnim, LOOP);
            film.setSpeed(100);  // Normal speed
            break;
            
        case EXCITED:
            film.startAnimation(goAnim, LOOP);
            film.setSpeed(50);  // Fast!
            break;
            
        case OVERWHELMED:
            film.pause();  // Too close! Freeze up
            break;
    }
}

void drawOverlay() {
    matrix.beginDraw();
    matrix.stroke(0xFFFFFF);
    
    switch (currentState) {
        case SLEEPING:
            // Draw "Zzz" indicator in corner
            matrix.point(10, 0);
            if ((millis() / 500) % 2 == 0) {
                matrix.point(11, 1);
            }
            break;
            
        case ALERT:
            // Draw subtle corner dots to show awareness
            matrix.point(0, 0);
            matrix.point(11, 0);
            break;
            
        case EXCITED:
            // Draw random sparkles around the character
            if (millis() - lastSparkle >= SPARKLE_INTERVAL) {
                sparkleX = random(0, 12);
                sparkleY = random(0, 8);
                lastSparkle = millis();
            }
            matrix.point(sparkleX, sparkleY);
            // Extra sparkle
            matrix.point((sparkleX + 5) % 12, (sparkleY + 3) % 8);
            break;
            
        case OVERWHELMED:
            // Flash warning border
            if (millis() - lastFlash >= 100) {
                flashOn = !flashOn;
                lastFlash = millis();
            }
            if (flashOn) {
                // Draw border
                matrix.line(0, 0, 11, 0);   // Top
                matrix.line(0, 7, 11, 7);   // Bottom
                matrix.line(0, 0, 0, 7);    // Left
                matrix.line(11, 0, 11, 7);  // Right
            }
            break;
    }
    
    matrix.endDraw();
}

const char* getStateName(CharacterState state) {
    switch (state) {
        case SLEEPING: return "SLEEPING";
        case ALERT: return "ALERT";
        case EXCITED: return "EXCITED";
        case OVERWHELMED: return "OVERWHELMED";
        default: return "UNKNOWN";
    }
}
