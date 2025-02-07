# TinyFilmFestival Library

LED matrix animation library for Arduino UNO R4 WiFi's built-in matrix. Create and control LED animations with multiple playback modes and state management.

## Features
- Frame-by-frame animation control
- Multiple playback modes (once, loop, boomerang)
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
```cpp
Animation myAnimation = frameData;  // frameData is uint32_t[][4] array

```

### PlayMode Types
- `ONCE`: Play once and stop
- `LOOP`: Play repeatedly  
- `BOOMERANG`: Play forward/backward



### AnimationState Types
- `IDLE`: No animation loaded
- `PLAYING`: Animation playing
- `PAUSED`: Animation paused
- `COMPLETED`: Animation finished (PLAY_ONCE mode)

## API Reference

### Animation Control Functions
```cpp
// Start animation playback
void startAnimation(const Animation& animation, PlayMode mode = PLAY_ONCE);


// Speed control
void setSpeed(uint32_t speedMs);        // Set custom frame duration
void restoreOriginalSpeed();            // Return to original timing

// Playback control
void pause();                           // Pause animation
void resume();                          // Resume animation
void stop();                            // Stop animation completely
void update();                          // Update frame (call in loop)
void displayFrame(const uint32_t frame[3]); // Display single frame
```

### Status Functions
```cpp
bool isPaused() const;              // Check if paused
bool isComplete() const;            // Check if complete (PLAY_ONCE)
bool isPlaying() const;             // Check if playing
bool isIdle() const;                // Check if no animation loaded
bool isCustomSpeedActive() const;   // Check if using custom speed
AnimationState getState() const;     // Get current state
uint32_t getCurrentFrame() const;    // Get current frame number
uint32_t getCurrentSpeed() const;    // Get current frame duration
```

### Basic Usage Example
```cpp
#include "TinyFilmFestival.h"
#include "animation.h" //this is the name of your downloaded file

TinyFilmFestival film;
Animation myAnimation = animation;

void setup() {
    film.begin();
    film.startAnimation(myAnimation, LOOP);
}

void loop() {
    film.update();
}
```

## Documentation
- [LED Matrix Editor Guide](editor-guide.md)
- [Basic Matrix Examples](basic-matrix.md)
- [Animation Control Examples](animation-control.md) 
- [Button Control Examples](button-control.md)
