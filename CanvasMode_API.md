# Canvas Mode API Reference

## Table of Contents
- [Overview](#overview)
- [Setup](#setup)
- [Matrix Methods](#matrix-methods)
  - [begin()](#begin)
  - [width()](#width)
  - [height()](#height)
- [Drawing Control Methods](#drawing-control-methods)
  - [beginDraw()](#begindraw)
  - [endDraw()](#enddraw)
  - [background()](#background)
  - [clear()](#clear)
  - [set()](#set)
- [Style Control Methods](#style-control-methods)
  - [fill()](#fill)
  - [noFill()](#nofill)
  - [stroke()](#stroke)
  - [noStroke()](#nostroke)
- [Shape Drawing Methods](#shape-drawing-methods)
  - [point()](#point)
  - [line()](#line)
  - [rect()](#rect)
  - [circle()](#circle)
  - [ellipse()](#ellipse)
- [Text Methods](#text-methods)
  - [text()](#text)
  - [textFont()](#textfont)
  - [textFontWidth()](#textfontwidth)
  - [textFontHeight()](#textfontheight)
  - [beginText()](#begintext)
  - [print(), println()](#print-println)
  - [endText()](#endtext)
  - [textScrollSpeed()](#textscrollspeed)
- [Example Sketches](#example-sketches)
  - [Scrolling Text](#scrolling-text)
  - [Drawing Shapes](#drawing-shapes)
  - [Sine Wave Animation](#sine-wave-animation)

---

## Overview

Canvas Mode lets you draw directly to the Arduino UNO R4 WiFi's 12×8 LED matrix using code. Unlike Animation Mode (which plays pre-made frames), Canvas Mode generates graphics in real-time — perfect for:

- **Dynamic data** — sensor readings, counters, progress bars
- **Procedural effects** — sine waves, bouncing dots, patterns
- **Interactive graphics** — responding to input in real-time

The `TinyScreen` class wraps all ArduinoGraphics drawing methods, so you only need one include and one object.

---

## Setup

```cpp
#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    // Draw something here
    screen.endDraw();
}
```

> **Note:** You don't need to include `ArduinoGraphics.h` or `Arduino_LED_Matrix.h` separately — `TinyFilmFestival.h` includes them automatically.

---

## Matrix Methods

### `begin()`

#### Description

Initializes the R4 WiFi's LED matrix.

#### Syntax

```cpp
screen.begin()
```

#### Parameters

None

#### Returns

Boolean: true for success, false on failure.

#### Example

```cpp
#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    if (!screen.begin()) {
        Serial.println("Failed to initialize!");
        while (1);
    }
}
```

---

### `width()`

#### Description

Returns the pixel width of the LED matrix (12 pixels).

#### Syntax

```cpp
screen.width()
```

#### Parameters

None

#### Returns

Returns 12 (the width of the R4 WiFi LED matrix).

#### Example

```cpp
int w = screen.width();  // w will be 12
```

---

### `height()`

#### Description

Returns the pixel height of the LED matrix (8 pixels).

#### Syntax

```cpp
screen.height()
```

#### Parameters

None

#### Returns

Returns 8 (the height of the R4 WiFi LED matrix).

#### Example

```cpp
int h = screen.height();  // h will be 8
```

---

## Drawing Control Methods

### `beginDraw()`

#### Description

Begins a fresh drawing operation. Clears the internal buffer and prepares for drawing commands.

#### Syntax

```cpp
screen.beginDraw()
```

#### Parameters

None

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.point(0, 0);
screen.endDraw();
```

---

### `endDraw()`

#### Description

Ends a drawing operation and displays the result on the LED matrix.

#### Syntax

```cpp
screen.endDraw()
```

#### Parameters

None

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.point(5, 3);
screen.endDraw();  // Now the point appears on the matrix
```

---

### `background()`

#### Description

Sets the background color. For the single-color matrix, this determines if background pixels are on or off.

#### Syntax

```cpp
screen.background(r, g, b)
screen.background(hexColor)
```

#### Parameters

- `r, g, b`: Color values (0-255). Use 0 for off, any non-zero for on.
- `hexColor`: 24-bit RGB color (0x000000 for off, 0xFFFFFF for on)

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.background(0, 0, 0);  // Background LEDs off
screen.stroke(0xFFFFFF);
screen.point(6, 4);
screen.endDraw();
```

---

### `clear()`

#### Description

Clears the LED matrix (sets all LEDs to the background state).

#### Syntax

```cpp
screen.clear()
screen.clear(x, y)
```

#### Parameters

- `x`: x position of pixel to clear (optional)
- `y`: y position of pixel to clear (optional)

#### Returns

Nothing

#### Example

```cpp
// Clear entire matrix
screen.beginDraw();
screen.clear();
screen.endDraw();

// Clear just one pixel
screen.beginDraw();
screen.clear(2, 3);
screen.endDraw();
```

---

### `set()`

#### Description

Sets the state of a specific LED directly.

#### Syntax

```cpp
screen.set(x, y, r, g, b)
screen.set(x, y, hexColor)
```

#### Parameters

- `x`: x position (0-11)
- `y`: y position (0-7)
- `r, g, b`: Color values (0-255)
- `hexColor`: 24-bit RGB color

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.set(3, 2, 255, 255, 255);  // Turn on LED at 3,2
screen.set(4, 2, 0xFFFFFF);       // Turn on LED at 4,2
screen.endDraw();
```

---

## Style Control Methods

### `fill()`

#### Description

Sets the fill state for shape drawing (interior of shapes).

#### Syntax

```cpp
screen.fill(r, g, b)
screen.fill(hexColor)
```

#### Parameters

- `r, g, b`: Color values (0-255)
- `hexColor`: 24-bit RGB color (0xFFFFFF for on)

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.fill(0xFFFFFF);
screen.rect(2, 2, 8, 4);  // Draw a filled rectangle
screen.endDraw();
```

---

### `noFill()`

#### Description

Disables filling for shapes (only outlines will be drawn).

#### Syntax

```cpp
screen.noFill()
```

#### Parameters

None

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.noFill();
screen.rect(2, 2, 8, 4);  // Draw rectangle outline only
screen.endDraw();
```

---

### `stroke()`

#### Description

Sets the stroke (outline) state for drawing.

#### Syntax

```cpp
screen.stroke(r, g, b)
screen.stroke(hexColor)
```

#### Parameters

- `r, g, b`: Color values (0-255)
- `hexColor`: 24-bit RGB color

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.line(0, 0, 11, 7);  // Draw a diagonal line
screen.endDraw();
```

---

### `noStroke()`

#### Description

Disables stroke (outline) for shapes.

#### Syntax

```cpp
screen.noStroke()
```

#### Parameters

None

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.noStroke();
screen.fill(0xFFFFFF);
screen.rect(3, 2, 6, 4);  // Filled rectangle, no outline
screen.endDraw();
```

---

## Shape Drawing Methods

### `point()`

#### Description

Draws a single point (turns on a single LED).

#### Syntax

```cpp
screen.point(x, y)
```

#### Parameters

- `x`: x position (0-11)
- `y`: y position (0-7)

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.point(6, 4);  // Turn on center LED
screen.endDraw();
```

---

### `line()`

#### Description

Draws a line between two points.

#### Syntax

```cpp
screen.line(x1, y1, x2, y2)
```

#### Parameters

- `x1, y1`: Starting point
- `x2, y2`: Ending point

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.line(0, 0, 11, 7);  // Diagonal across matrix
screen.endDraw();
```

---

### `rect()`

#### Description

Draws a rectangle with optional fill.

#### Syntax

```cpp
screen.rect(x, y, width, height)
```

#### Parameters

- `x, y`: Top-left corner position
- `width`: Rectangle width
- `height`: Rectangle height

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.noFill();
screen.rect(2, 1, 8, 6);  // Rectangle outline
screen.endDraw();
```

---

### `circle()`

#### Description

Draws a circle with optional fill.

#### Syntax

```cpp
screen.circle(x, y, diameter)
```

#### Parameters

- `x, y`: Center position
- `diameter`: Circle diameter in pixels

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.fill(0xFFFFFF);
screen.circle(6, 4, 6);  // Filled circle in center
screen.endDraw();
```

---

### `ellipse()`

#### Description

Draws an ellipse with optional fill.

#### Syntax

```cpp
screen.ellipse(x, y, width, height)
```

#### Parameters

- `x, y`: Center position
- `width`: Ellipse width
- `height`: Ellipse height

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.noFill();
screen.ellipse(6, 4, 10, 6);  // Wide ellipse
screen.endDraw();
```

---

## Text Methods

### `text()`

#### Description

Draws text on the LED matrix.

#### Syntax

```cpp
screen.text(string)
screen.text(string, x, y)
```

#### Parameters

- `string`: Text to display
- `x, y`: Starting position (optional)

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(0xFFFFFF);
screen.textFont(Font_4x6);
screen.text("Hi", 0, 1);
screen.endDraw();
```

---

### `textFont()`

#### Description

Sets the font for text drawing. Available fonts: `Font_4x6` and `Font_5x7`.

#### Syntax

```cpp
screen.textFont(font)
```

#### Parameters

- `font`: Font to use (`Font_4x6` or `Font_5x7`)

#### Returns

Nothing

#### Example

```cpp
screen.textFont(Font_4x6);  // Smaller font, fits more text
```

---

### `textFontWidth()`

#### Description

Returns the width of the current font in pixels.

#### Syntax

```cpp
screen.textFontWidth()
```

#### Parameters

None

#### Returns

Font width in pixels (4 for Font_4x6, 5 for Font_5x7)

#### Example

```cpp
screen.textFont(Font_4x6);
int w = screen.textFontWidth();  // w = 4
```

---

### `textFontHeight()`

#### Description

Returns the height of the current font in pixels.

#### Syntax

```cpp
screen.textFontHeight()
```

#### Parameters

None

#### Returns

Font height in pixels (6 for Font_4x6, 7 for Font_5x7)

#### Example

```cpp
screen.textFont(Font_4x6);
int h = screen.textFontHeight();  // h = 6
```

---

### `beginText()`

#### Description

Start the process of displaying and optionally scrolling text.

#### Syntax

```cpp
screen.beginText()
screen.beginText(x, y)
screen.beginText(x, y, hexColor)
```

#### Parameters

- `x, y`: Text position
- `hexColor`: Text color (optional)

#### Returns

Nothing

#### Example

```cpp
screen.beginText(0, 1);
screen.print("Hi");
screen.endText();
```

---

### `print(), println()`

#### Description

Adds text to be displayed after `beginText()`. Works like `Serial.print()`.

#### Syntax

```cpp
screen.print(text)
screen.println(text)
```

#### Parameters

- `text`: Text to display

#### Returns

Nothing

#### Example

```cpp
screen.beginText(0, 1);
screen.print("Hello");
screen.endText();
```

---

### `endText()`

#### Description

End the text display, optionally with scrolling.

#### Syntax

```cpp
screen.endText()
screen.endText(scrollDirection)
```

#### Parameters

- `scrollDirection`: `NO_SCROLL`, `SCROLL_LEFT`, `SCROLL_RIGHT`, `SCROLL_UP`, `SCROLL_DOWN`

#### Returns

Nothing

#### Example

```cpp
screen.beginText(0, 1);
screen.print("Hello Arduino!");
screen.endText(SCROLL_LEFT);  // Scroll text left
```

---

### `textScrollSpeed()`

#### Description

Sets the text scrolling speed in milliseconds per pixel.

#### Syntax

```cpp
screen.textScrollSpeed(speed)
```

#### Parameters

- `speed`: Delay in milliseconds between scroll steps

#### Returns

Nothing

#### Example

```cpp
screen.textScrollSpeed(100);  // 100ms per pixel
screen.beginText(0, 1);
screen.print("Scrolling!");
screen.endText(SCROLL_LEFT);
```

---

## Example Sketches

### Scrolling Text

```cpp
/*
 * Scrolling Text Example
 * Displays static text, then scrolls a message
 */
#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();

    // Display static text first
    screen.beginDraw();
    screen.stroke(0xFFFFFF);
    screen.textFont(Font_4x6);
    screen.text("Hi!", 1, 1);
    screen.endDraw();
    
    delay(2000);
}

void loop() {
    // Scrolling text
    screen.beginDraw();
    screen.stroke(0xFFFFFF);
    screen.textScrollSpeed(100);
    screen.textFont(Font_4x6);
    screen.beginText(0, 1, 0xFFFFFF);
    screen.print("  Hello Arduino R4!  ");
    screen.endText(SCROLL_LEFT);
    screen.endDraw();
}
```

---

### Drawing Shapes

```cpp
/*
 * Drawing Shapes Example
 * Cycles through different shape types
 */
#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    // Rectangle outline
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    screen.noFill();
    screen.rect(1, 1, 10, 6);
    screen.endDraw();
    delay(1000);
    
    // Filled rectangle
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    screen.fill(0xFFFFFF);
    screen.rect(2, 2, 8, 4);
    screen.endDraw();
    delay(1000);
    
    // Circle outline
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    screen.noFill();
    screen.circle(6, 4, 6);
    screen.endDraw();
    delay(1000);
    
    // Filled circle
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    screen.fill(0xFFFFFF);
    screen.circle(6, 4, 4);
    screen.endDraw();
    delay(1000);
    
    // Crossed diagonal lines
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    screen.line(0, 0, 11, 7);
    screen.line(0, 7, 11, 0);
    screen.endDraw();
    delay(1000);
    
    // Point pattern
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    for (int x = 1; x < 11; x += 2) {
        for (int y = 1; y < 7; y += 2) {
            screen.point(x, y);
        }
    }
    screen.endDraw();
    delay(1000);
}
```

---

### Sine Wave Animation

```cpp
/*
 * Sine Wave Animation Example
 * Animates a moving sine wave across the matrix
 */
#include "TinyFilmFestival.h"

TinyScreen screen;

float phase = 0.0;
const float phaseIncrement = 0.2;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    screen.stroke(0xFFFFFF);
    
    // Draw sine wave
    for (int x = 0; x < 12; x++) {
        float sinValue = sin(x * 0.5 + phase);
        int y = (int)(3.5 + 3.0 * sinValue);
        y = constrain(y, 0, 7);
        screen.point(x, y);
    }
    
    screen.endDraw();
    
    // Animate
    phase += phaseIncrement;
    if (phase > 2 * PI) {
        phase -= 2 * PI;
    }
    
    delay(100);
}
```

---

## See Also

- [Animation Mode API](AnimationMode_API.md) — Pre-made frame playback
- [Hybrid Mode](#hybrid-mode) — Combining animations with canvas drawing
- [LED Matrix Editor](https://ledmatrix-editor.arduino.cc/) — Create animation frames
