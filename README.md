# TinyFilmFestival Library

LED matrix animation library for Arduino UNO R4 WiFi's built-in matrix. Create and control LED animations with multiple playback modes, partial clip playback, and the ability to combine multiple animations.

## Features
- Frame-by-frame animation control
- Multiple playback modes (once, loop, boomerang)
- Partial clip playback (forward or backward)
- Combine multiple animations simultaneously
- Custom speed control
- Pause/resume functionality
- State management
- Button input integration
- Animation switching

## Installation
1. Install the Library from the Library Manager
2. Include in sketch: `#include "TinyFilmFestival.h"`

## Core Components

### Animation Class
The Animation class is automatically created from your exported header file:
```cpp
// If your exported file is named "myanimation.h":
#include "myanimation.h"
Animation myAnim = myanimation;  // Variable name matches header filename
```

### PlayMode Types
- `ONCE`: Play once and stop
- `LOOP`: Play repeatedly  
- `BOOMERANG`: Play forward/backward repeatedly

### AnimationState Types
- `IDLE`: No animation loaded
- `PLAYING`: Animation playing
- `PAUSED`: Animation paused
- `COMPLETED`: Animation finished (PLAY_ONCE mode)

## Animation Control

### Single Animation Control
```cpp
TinyFilmFestival film;
Animation myAnim = animation;  // animation.h is your exported file

// Basic playback
film.startAnimation(myAnim, LOOP);             // Play full animation in loop

// Partial clip playback (frame numbers start at 1)
film.startAnimation(myAnim, LOOP, 2, 6);       // Play frames 2-6 forward
film.startAnimation(myAnim, LOOP, 6, 2);       // Play frames 6-2 backward

// Speed control
film.setSpeed(100);                            // Set frame duration to 100ms
film.restoreOriginalSpeed();                   // Return to original timing

// Playback control
film.pause();                                  // Pause animation
film.resume();                                 // Resume animation
film.stop();                                   // Stop animation completely
film.update();                                 // Update frame (call in loop)
```

### Multiple Animation Control
Combine multiple animations to play simultaneously:
```cpp
TinyFilmFestival film1, film2;                 // Create film objects
CombinedFilmFestival combinedFilm;             // Create combiner

// Setup animations
film1.startAnimation(landscapeAnim, LOOP);     // Background
film2.startAnimation(effectAnim, LOOP);        // Foreground

// Add to combiner (order matters - first = background)
combinedFilm.addFilm(film1);                   // Background layer
combinedFilm.addFilm(film2);                   // Foreground layer

// Update combined animation
combinedFilm.update();                         // Call in loop
```

### Status Functions
```cpp
// Playback status
bool isPaused();                   // Check if paused
bool isComplete();                 // Check if complete (PLAY_ONCE)
bool isPlaying();                  // Check if playing
bool isIdle();                     // Check if no animation loaded
bool isCustomSpeedActive();        // Check if using custom speed
bool isPlayingBackwards();         // Check if playing in reverse

// Current state
AnimationState getState();         // Get current state
int getCurrentFrame();             // Get current frame number (1-based)
int getCurrentSpeed();             // Get current frame duration
int getTotalFrames();             // Get total frames in animation
int getStartFrame();              // Get start frame of current clip
int getEndFrame();                // Get end frame of current clip
```

## Basic Examples

### Simple Looping Animation
```cpp
#include "TinyFilmFestival.h"
#include "animation.h"             // Your exported animation file

TinyFilmFestival film;
Animation myAnimation = animation;  // Name matches header file

void setup() {
    film.begin();
    film.startAnimation(myAnimation, LOOP);
}

void loop() {
    film.update();
}
```

### Partial Clip Playback
```cpp
#include "TinyFilmFestival.h"
#include "animation.h"

TinyFilmFestival film;
Animation myAnimation = animation;

void setup() {
    film.begin();
    // Play frames 2-6 forward in a loop
    film.startAnimation(myAnimation, LOOP, 2, 6);
    // Or play frames 6-2 backward in a loop
    //film.startAnimation(myAnimation, LOOP, 6, 2);
}

void loop() {
    film.update();
}
```

### Combined Animations
```cpp
#include "TinyFilmFestival.h"
#include "landscape.h"
#include "effect.h"

TinyFilmFestival background, effect;
CombinedFilmFestival combined;

Animation landscapeAnim = landscape;
Animation effectAnim = effect;

void setup() {
    combined.begin();
    
    // Setup animations
    background.startAnimation(landscapeAnim, LOOP);
    effect.startAnimation(effectAnim, LOOP);
    
    // Add to combiner (background first)
    combined.addFilm(background);
    combined.addFilm(effect);
}

void loop() {
    combined.update();
}
```

## Documentation
- [LED Matrix Editor Guide](editor-guide.md)
- [Basic Matrix Examples](basic-matrix.md)
- [Animation Control Examples](animation-control.md) 
- [Button Control Examples](button-control.md)