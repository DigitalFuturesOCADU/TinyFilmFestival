/*
 * TinyFilmFestival V2 - Button Play/Pause
 * 05_Sensor_Control/Button_PlayPause
 * 
 * Toggle animation playback with a button press.
 * Demonstrates pause() and resume() for interactive control.
 * 
 * Hardware:
 * - Arduino UNO R4 WiFi (built-in 12×8 LED Matrix)
 * - Pushbutton on pin 2 (connected to GND)
 */

#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation idleAnim = idle;

const int buttonPin = 2;
bool lastButtonState = HIGH;

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP);
    
    screen.begin();
    screen.play(idleAnim, LOOP);
    Serial.println("Press button to toggle play/pause");
}

void loop() {
    bool currentState = digitalRead(buttonPin);
    
    // Detect button press (falling edge)
    if (currentState == LOW && lastButtonState == HIGH) {
        if (screen.isPlaying()) {
            screen.pause();
            Serial.println("Paused");
        } else {
            screen.resume();
            Serial.println("Playing");
        }
        delay(50);  // Simple debounce
    }
    
    lastButtonState = currentState;
    screen.update();
}
