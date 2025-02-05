# TinyFilmFestival Library

A simple animation playback library for the Arduino UNO R4 WiFi LED Matrix. Control animations with different speeds, modes, and playback states to create dynamic visual effects.

## Features

- Play animations with adjustable speeds
- Multiple playback modes (single play, loop, boomerang)
- Pause and resume control
- Easy state machine integration
- Frame-by-frame control
- Optimized for the UNO R4 WiFi LED Matrix

## Installation

1. Download the library
2. Include it in your Arduino libraries folder
3. Include in your sketch with:
```cpp
#include "TinyFilmFestival.h"
```

## Basic Usage

Initialize and play a simple animation:

```cpp
#include "TinyFilmFestival.h"
#include "animation.h"  // Your animation file

TinyFilmFestival film;

void setup() {
    film.begin();
    film.startAnimation(frameAnimation, PLAY_LOOP);
}

void loop() {
    film.update();
}
```

## API Reference

### Begin Matrix

Initialize the LED matrix:

```cpp
film.begin();
```

### Start Animation

Start playing an animation with a specified mode:

```cpp
// Available modes: PLAY_ONCE, PLAY_LOOP, PLAY_BOOMERANG
film.startAnimation(frameAnimation, PLAY_LOOP);
```

### Set Speed

Change animation playback speed in milliseconds:

```cpp
film.setSpeed(100);  // Play each frame for 100ms
```

### Pause and Resume

Control animation playback:

```cpp
film.pause();   // Pause animation
film.resume();  // Resume animation
```

### Restore Original Speed

Return to the original frame timings defined in the animation:

```cpp
film.restoreOriginalSpeed();
```

### Check Status

Query animation state:

```cpp
if (film.isPausedState()) {
    // Animation is paused
}

if (film.sequenceDone()) {
    // Animation sequence completed
}

int currentFrame = film.getCurrentFrame();
```

## Examples

### Simple State Machine

Control animation playback using states:

```cpp
int animationState = 0;
int animationTime = 3000;
int lastStateChange = 0;

void loop() {
    film.update();
    
    if (millis() - lastStateChange > animationTime) {
        animationState = (animationState + 1) % 4;
        lastStateChange = millis();
        
        switch(animationState) {
            case 0:
                film.setSpeed(100);
                film.startAnimation(frameAnimation, PLAY_LOOP);
                break;
            case 1:
                film.setSpeed(50);
                film.startAnimation(frameAnimation, PLAY_LOOP);
                break;
            case 2:
                film.setSpeed(200);
                film.startAnimation(frameAnimation, PLAY_LOOP);
                break;
            case 3:
                film.setSpeed(100);
                film.startAnimation(frameAnimation, PLAY_BOOMERANG);
                break;
        }
    }
}
```

### Multiple Animations

Switch between different animations:

```cpp
// In your sketch:
#include "animation1.h"
#include "animation2.h"

// Switch between animations
film.startAnimation(animation1, PLAY_LOOP);
delay(2000);
film.startAnimation(animation2, PLAY_BOOMERANG);
```

### Dynamic Speed Control

Adjust animation speed based on input:

```cpp
void loop() {
    film.update();
    
    // Read from potentiometer
    int speed = map(analogRead(A0), 0, 1023, 50, 200);
    film.setSpeed(speed);
}
```

## Animation File Format

Animations are defined as arrays of frame data:

```cpp
const uint32_t frameAnimation[][4] = {
    // Each row: 3 bytes of LED data + timing
    { 0x123456, 0x789ABC, 0xDEF012, 100 },  // Frame 1, 100ms
    { 0x345678, 0x9ABCDE, 0xF01234, 100 }   // Frame 2, 100ms
};
```

## Contributing

Feel free to open issues or submit pull requests for improvements.

## License

This library is released under the MIT License.