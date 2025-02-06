# Button Control Examples

## Play/Pause Control

Toggle animation playback with button press.

```cpp
/*
 * Play/Pause Control
 * 
 * Hardware:
 * - Pushbutton: pin 2 to ground
 * 
 * Features:
 * - Toggle play/pause
 * - Internal state management
 */

#include "TinyFilmFestival.h"
#include "animation.h"

TinyFilmFestival film;
Animation myAnimation = frameAnimation;
const int buttonPin = 2;

void setup() {
    film.begin();
    pinMode(buttonPin, INPUT_PULLUP);
    film.startAnimation(myAnimation, LOOP);
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {
        film.pause();
    } else {
        film.resume();
    }
    film.update();
}
```

## Speed Control

Cycle through animation speeds with button.

```cpp
/*
 * Speed Control
 * 
 * Hardware:
 * - Pushbutton: pin 2 to ground
 * 
 * Features:
 * - Pressed = Fast speed
 * - Released = Slow speed
 */

#include "TinyFilmFestival.h"
#include "animation.h"

TinyFilmFestival film;
Animation myAnimation = frameAnimation;
const int buttonPin = 2;
const int SPEED_FAST = 50;
const int SPEED_SLOW = 200;

void setup() {
    film.begin();
    pinMode(buttonPin, INPUT_PULLUP);
    film.startAnimation(myAnimation, LOOP);
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {
        film.setSpeed(SPEED_FAST);
    } else {
        film.setSpeed(SPEED_SLOW);
    }
    film.update();
}
```

## Animation Switching

Switch between different animations.

```cpp
/*
 * Animation Switching
 * 
 * Hardware:
 * - Pushbutton: pin 2 to ground
 * 
 * Features:
 * - Pressed = "go" animation
 * - Released = "idle" animation
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

TinyFilmFestival film;
Animation idleAnim = idle;
Animation goAnim = go;
const int buttonPin = 2;

void setup() {
    film.begin();
    pinMode(buttonPin, INPUT_PULLUP);
    film.startAnimation(idleAnim, LOOP);
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {
        film.startAnimation(goAnim, LOOP);
    } else {
        film.startAnimation(idleAnim, LOOP);
    }
    film.update();
}
```