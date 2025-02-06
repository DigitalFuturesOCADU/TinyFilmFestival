# Animation Control Examples

## Basic Animation Control

Simple animation playback with speed control.

```cpp
/*
 * Basic Animation Control
 * 
 * Demonstrates:
 * - Loading animation
 * - Setting playback mode
 * - Controlling speed
 * 
 * Available Modes:
 * - ONCE: Play once and stop
 * - LOOP: Play repeatedly
 * - BOOMERANG: Play forward/backward
 */

#include "TinyFilmFestival.h"
#include "animation.h"

TinyFilmFestival film;
Animation myAnimation = frameAnimation;

void setup() {
    film.begin();
    film.startAnimation(myAnimation, LOOP);
    film.setSpeed(50);  // 50ms per frame
}

void loop() {
    film.update();
}
```

## State Machine Example

Advanced animation control using states and timing.

```cpp
/*
 * State Machine Example
 * 
 * States (5 seconds each):
 * 0: Normal speed, plays once
 * 1: Fast speed, loops
 * 2: Slow speed, boomerang
 * 3: Original timing, loops
 * 4: Paused
 */

#include "TinyFilmFestival.h"
#include "animation.h"

TinyFilmFestival film;
Animation myAnimation = frameAnimation;

int currentState = 0;
unsigned long lastStateChange = 0;
unsigned long stateDuration = 5000;

void setup() {
    film.begin();
    lastStateChange = millis();
    film.startAnimation(myAnimation, ONCE);
}

void loop() {
    film.update();
    
    if (millis() - lastStateChange >= stateDuration) {
        currentState = (currentState + 1) % 5;
        lastStateChange = millis();
        
        switch (currentState) {
            case 0:
                film.startAnimation(myAnimation, ONCE);
                film.setSpeed(100);
                break;
            case 1:
                film.startAnimation(myAnimation, LOOP);
                film.setSpeed(50);
                break;
            // Additional states...
        }
    }
}
```