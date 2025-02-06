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
1. Copy TinyFilmFestival library files to Arduino libraries folder
2. Include in sketch: `#include "TinyFilmFestival.h"`

## Core Components

### Animation Class
```cpp
Animation myAnimation = frameData;  // frameData is uint32_t[][4] array
size_t frameCount = myAnimation.getFrameCount();
const uint32_t (*frames)[4] = myAnimation.getFrames();
```

### PlayMode Types
- `PLAY_ONCE`: Play once and stop
- `PLAY_LOOP`: Play repeatedly  
- `PLAY_BOOMERANG`: Play forward/backward

Constants: `ONCE`, `LOOP`, `BOOMERANG`

### AnimationState Types
- `IDLE`: No animation loaded
- `PLAYING`: Animation playing
- `PAUSED`: Animation paused
- `COMPLETED`: Animation finished (PLAY_ONCE mode)

## Documentation
- [LED Matrix Editor Guide](editor-guide.md)
- [Basic Matrix Examples](basic-matrix.md)
- [Animation Control Examples](animation-control.md) 
- [Button Control Examples](button-control.md)