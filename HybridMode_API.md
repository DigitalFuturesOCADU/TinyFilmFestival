# Hybrid Mode API Reference

## Table of Contents
- [Overview](#overview)
- [Setup](#setup)
- [Overlay Methods](#overlay-methods)
  - [beginOverlay()](#beginoverlay)
  - [endOverlay()](#endoverlay)
- [Drawing Over Animations](#drawing-over-animations)
- [Example Sketches](#example-sketches)
  - [Progress Bar Overlay](#progress-bar-overlay)
  - [Sparkle Effects](#sparkle-effects)
  - [Interactive Overlay](#interactive-overlay)

---

## Overview

Hybrid Mode combines the best of both worlds:
- **Animation Mode** — detailed pre-made frames playing in the background
- **Canvas Mode** — dynamic, code-drawn elements on top

This is perfect for:
- **Progress indicators** on animated backgrounds
- **Sparkle/effect overlays** on character animations
- **HUD elements** over game backgrounds
- **Interactive highlights** responding to input

The key difference from pure Canvas Mode:
- `beginDraw()`/`endDraw()` — starts fresh, clears the matrix
- `beginOverlay()`/`endOverlay()` — preserves the current animation frame

---

## Setup

```cpp
#include "TinyFilmFestival.h"
#include "myAnimation.h"

TinyScreen screen;
Animation anim = animation;

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    // 1. Update animation frame
    screen.update();
    
    // 2. Draw overlay on top
    screen.beginOverlay();
    screen.point(11, 0);        // Status indicator in corner
    screen.endOverlay();
}
```

---

## Overlay Methods

### `beginOverlay()`

#### Description

Begins an overlay drawing operation. Unlike `beginDraw()`, this preserves the current animation frame and allows you to draw additional elements on top.

#### Syntax

```cpp
screen.beginOverlay()
```

#### Parameters

None

#### Returns

Nothing

#### How It Works

1. The current animation frame is rendered to the display buffer
2. You can now draw additional elements
3. When you call `endOverlay()`, both the animation and your drawings are displayed

#### Example

```cpp
screen.update();           // Update animation

screen.beginOverlay();     // Start overlay (keeps animation)
screen.point(0, 0);        // Draw on top
screen.endOverlay();       // Show combined result
```

---

### `endOverlay()`

#### Description

Ends the overlay drawing operation and displays the combined result (animation + overlay).

#### Syntax

```cpp
screen.endOverlay()
```

#### Parameters

None

#### Returns

Nothing

#### Example

```cpp
screen.beginOverlay();
screen.line(0, 7, 11, 7);  // Draw bottom bar
screen.endOverlay();       // Display result
```

---

## Drawing Over Animations

All Canvas Mode drawing methods work in overlay mode:

```cpp
screen.update();

screen.beginOverlay();

// Points
screen.point(x, y);

// Lines
screen.line(x1, y1, x2, y2);

// Shapes
screen.rect(x, y, w, h);
screen.circle(cx, cy, r);

// Style
screen.stroke(0xFFFFFF);
screen.fill(0xFFFFFF);
screen.noFill();

screen.endOverlay();
```

### Important Notes

1. **Call `update()` first** — This advances the animation frame
2. **Overlay is additive** — Your drawings add lit pixels; they don't erase animation pixels
3. **Overlay is temporary** — Each loop iteration starts fresh from the animation

### Overlay vs. Draw Comparison

| Method | Animation | Overlay |
|--------|-----------|---------|
| `beginDraw()` | Cleared | Cleared |
| `beginOverlay()` | Preserved | Fresh |

---

## Example Sketches

### Progress Bar Overlay

```cpp
/*
 * Progress Bar Overlay Example
 * Shows a progress bar over a looping animation
 */
#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation idleAnim = idle;
int progress = 0;

void setup() {
    screen.begin();
    screen.play(idleAnim, LOOP);
}

void loop() {
    // Update animation
    screen.update();
    
    // Draw progress bar at bottom
    screen.beginOverlay();
    
    // Calculate bar width (0-11 pixels)
    int barWidth = map(progress, 0, 100, 0, 11);
    
    // Draw filled progress bar
    screen.stroke(0xFFFFFF);
    for (int x = 0; x <= barWidth; x++) {
        screen.point(x, 7);
    }
    
    screen.endOverlay();
    
    // Update progress
    progress = (progress + 1) % 101;
    delay(50);
}
```

---

### Sparkle Effects

```cpp
/*
 * Sparkle Effects Example
 * Random sparkles over a character animation
 */
#include "TinyFilmFestival.h"
#include "character.h"

TinyScreen screen;
Animation charAnim = character;

void setup() {
    screen.begin();
    screen.play(charAnim, LOOP);
}

void loop() {
    screen.update();
    
    // Add random sparkles
    screen.beginOverlay();
    
    // 30% chance of sparkle each frame
    if (random(100) < 30) {
        int x = random(12);
        int y = random(8);
        screen.point(x, y);
    }
    
    screen.endOverlay();
    
    delay(100);
}
```

---

### Interactive Overlay

```cpp
/*
 * Interactive Overlay Example
 * Draw indicators based on sensor input
 */
#include "TinyFilmFestival.h"
#include "landscape.h"

TinyScreen screen;
Animation bgAnim = landscape;

const int SENSOR_PIN = A0;

void setup() {
    screen.begin();
    screen.play(bgAnim, LOOP);
}

void loop() {
    screen.update();
    
    // Read sensor
    int sensorValue = analogRead(SENSOR_PIN);
    int level = map(sensorValue, 0, 1023, 0, 7);
    
    // Draw level indicator on right edge
    screen.beginOverlay();
    
    screen.stroke(0xFFFFFF);
    for (int y = 7; y >= (7 - level); y--) {
        screen.point(11, y);
    }
    
    screen.endOverlay();
    
    delay(50);
}
```

---

### Complete Project: Character with Mood

```cpp
/*
 * Character with Mood Indicator
 * Animated character with emotion overlay based on sensor
 */
#include "TinyFilmFestival.h"
#include "idle.h"
#include "happy.h"

TinyScreen screen;
Animation idleAnim = idle;
Animation happyAnim = happy;

const int SENSOR_PIN = A0;
const int HAPPY_THRESHOLD = 700;

bool isHappy = false;

void setup() {
    screen.begin();
    screen.play(idleAnim, LOOP);
}

void loop() {
    int sensorValue = analogRead(SENSOR_PIN);
    
    // Switch animation based on threshold
    if (sensorValue > HAPPY_THRESHOLD && !isHappy) {
        screen.play(happyAnim, LOOP);
        isHappy = true;
    } else if (sensorValue <= HAPPY_THRESHOLD && isHappy) {
        screen.play(idleAnim, LOOP);
        isHappy = false;
    }
    
    screen.update();
    
    // Draw heart icon when happy
    if (isHappy) {
        screen.beginOverlay();
        // Simple heart in top-right corner
        screen.point(9, 0);
        screen.point(11, 0);
        screen.point(8, 1);
        screen.point(10, 1);
        screen.point(9, 2);
        screen.endOverlay();
    }
    
    delay(50);
}
```

---

## Best Practices

### 1. Always Update First
```cpp
// ✓ Correct order
screen.update();        // Animation first
screen.beginOverlay();  // Then overlay

// ✗ Wrong order
screen.beginOverlay();  // Overlay before update = stale frame
screen.update();
```

### 2. Keep Overlays Simple
The 12×8 matrix is small. Complex overlays can overwhelm the animation:
```cpp
// ✓ Good: subtle indicator
screen.point(11, 0);

// ✗ Too much: covers whole screen
for (int x = 0; x < 12; x++) {
    screen.line(x, 0, x, 7);
}
```

### 3. Consider Timing
Overlay drawing adds processing time. For fast animations, keep overlays minimal:
```cpp
// ✓ Good: simple check and draw
if (showIndicator) {
    screen.beginOverlay();
    screen.point(11, 7);
    screen.endOverlay();
}

// ✗ Slower: always drawing even when not needed
screen.beginOverlay();
if (showIndicator) {
    screen.point(11, 7);
}
screen.endOverlay();
```

---

## See Also

- [Animation Mode API](AnimationMode_API.md) — Pre-made frame playback
- [Canvas Mode API](CanvasMode_API.md) — Real-time code-drawn graphics
- [LED Matrix Editor](https://ledmatrix-editor.arduino.cc/) — Create animation frames
