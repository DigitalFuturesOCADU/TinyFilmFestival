/*
 * TinyFilmFestival V2 - Button Content Switch
 * 05_Sensor_Control/Button_ContentSwitch
 * 
 * Switch between two animations based on button state.
 * Demonstrates hot-swapping animation content.
 * 
 * Hardware:
 * - Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 * - Pushbutton on pin 2 (connected to GND)
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

TinyScreen screen;
Animation idleAnim = idle;
Animation goAnim = go;

const int buttonPin = 2;
bool wasPressed = false;

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP);
    
    screen.begin();
    screen.play(idleAnim, LOOP);
    Serial.println("Hold button to play 'go' animation");
}

void loop() {
    bool isPressed = (digitalRead(buttonPin) == LOW);
    
    // Switch animation when button state changes
    if (isPressed && !wasPressed) {
        screen.play(goAnim, LOOP);
        Serial.println("Playing: go");
    } else if (!isPressed && wasPressed) {
        screen.play(idleAnim, LOOP);
        Serial.println("Playing: idle");
    }
    
    wasPressed = isPressed;
    screen.update();
}
