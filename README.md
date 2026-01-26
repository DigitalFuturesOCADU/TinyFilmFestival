# TinyFilmFestival

| ![Character](images/character.gif) | ![Landscape](images/landscape.gif) |
|------------------------------------|------------------------------------|
| ![Load](images/load.gif)           | ![Pow](images/pow.gif)             |

A library for the Arduino UNO R4 WiFi's built-in 12×8 LED Matrix. One class, three modes:

| Mode | What it does | Key methods |
|------|--------------|-------------|
| **Animation** | Play pre-made frames | `play()`, `pause()`, `setSpeed()` |
| **Canvas** | Draw with code | `beginDraw()`, `point()`, `line()` |
| **Hybrid** | Draw over animations | `beginOverlay()`, `endOverlay()` |

---

## Quick Start

### Animation Mode
Play pre-made frame animations created in the LED Matrix Editor.

```cpp
#include "TinyFilmFestival.h"
#include "idle.h"               // Your animation file

TinyScreen screen;
Animation myAnim = idle;        // Variable name from .h file

void setup() {
    screen.begin();
    screen.play(myAnim, LOOP);
}

void loop() {
    screen.update();
}
```

### Canvas Mode
Draw graphics in real-time using code — perfect for dynamic visualizations.

```cpp
#include "TinyFilmFestival.h"

TinyScreen screen;
int x = 0;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    screen.point(x, 4);
    screen.endDraw();
    
    x = (x + 1) % 12;
    delay(100);
}
```

### Hybrid Mode
Combine both — play an animation and draw additional elements on top.

```cpp
#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation myAnim = idle;

void setup() {
    screen.begin();
    screen.play(myAnim, LOOP);
}

void loop() {
    screen.update();            // Update animation
    
    screen.beginOverlay();      // Draw on top
    screen.point(11, 0);        // Status indicator
    screen.endOverlay();
}
```

---

## Installation

1. Open Arduino IDE → **Sketch** → **Include Library** → **Manage Libraries**
2. Search: `TinyFilmFestival`
3. Click **Install** → Choose **INSTALL ALL** when prompted

---

## How It Works

TinyFilmFestival wraps the Arduino LED Matrix and ArduinoGraphics libraries into a single unified `TinyScreen` class. You only need one include and one object to access all features.

**Animation files** come from the [LED Matrix Editor](https://ledmatrix-editor.arduino.cc/) — a web tool where you draw frames visually and export `.h` files. These files contain frame data and timing that `TinyScreen` plays back automatically.

**Canvas drawing** uses the same graphics primitives as ArduinoGraphics (`point`, `line`, `rect`, `circle`, `text`) but through the `TinyScreen` wrapper, so you don't need separate includes.

### Documentation

| Guide | What's inside |
|-------|---------------|
| [Animation Mode API](AnimationMode_API.md) | `play()`, `pause()`, `setSpeed()`, layering multiple animations |
| [Canvas Mode API](CanvasMode_API.md) | `point()`, `line()`, `rect()`, `circle()`, `text()`, scrolling |
| [Hybrid Mode API](HybridMode_API.md) | `beginOverlay()` / `endOverlay()` for drawing over animations |
| [LED Matrix Editor Guide](editor-guide.md) | How to create and export `.h` animation files |
| [Example Animations](exampleAnimations/) | Pre-made `.h` files ready to use in your projects |

---

## Examples

Find these in **File → Examples → TinyFilmFestival**

### 01_Basics
| Example | Description |
|---------|-------------|
| **FirstAnimation** | Simplest Animation Mode example — load and play |
| **FirstCanvas** | Simplest Canvas Mode example — bouncing dot |

### 02_Animation_Mode
| Example | Description |
|---------|-------------|
| **PlaybackControl** | All playback modes (LOOP/ONCE/BOOMERANG), speed control, partial clips |
| **LayeredAnimations** | Multiple animations combined with addLayer() and playOnLayer() |

### 03_Canvas_Mode
| Example | Description |
|---------|-------------|
| **MovingShapes** | Motion patterns mirroring animation modes (continuous, single-pass, bounce) |
| **LayeredGraphics** | Multiple independent animated elements drawn in layers |
| **ScrollingText** | Static and scrolling text display |

### 04_Hybrid_Mode
| Example | Description |
|---------|-------------|
| **AnimationWithOverlay** | Pre-made animation with code-drawn progress indicator |

### 05_Sensor_Control
| Example | Description |
|---------|-------------|
| **Button_PlayPause** | Toggle animation play/pause with button |
| **Button_ContentSwitch** | Switch between animations based on button state |
| **Distance_SpeedControl** | Control animation speed with ultrasonic sensor |
| **Distance_ZoneSwitch** | Switch animations based on proximity zones |
| **Pressure_SpeedControl** | Control animation speed with pressure sensor |

### 06_Projects
| Example | Description |
|---------|-------------|
| **InteractiveCharacter** | Complete project: 4-zone proximity character with sparkle effects |

---

## Hardware

**Required:** Arduino UNO R4 WiFi (has built-in 12×8 LED Matrix)

**Optional (for sensor examples):**
- Pushbutton (pin 2 → GND)
- HC-SR04 ultrasonic (Trigger: A0, Echo: A1)
- Pressure sensor (A0)

---

## License

MIT License — see [LICENSE](LICENSE)
