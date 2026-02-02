# Canvas Mode API Reference

## Table of Contents
- [Overview](#overview)
- [LED Matrix Layout](#led-matrix-layout)
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
  - [Visual Guide to Drawing Primitives](#visual-guide-to-drawing-primitives)
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

**Monochrome Matrix:** The R4 WiFi LED matrix is **on/off only** — no color or brightness control. The library provides simple `ON` and `OFF` constants for all drawing methods:

```cpp
screen.stroke(ON);       // Outlines lit
screen.fill(OFF);        // Interiors dark
screen.background(OFF);  // Background dark
```

---

## LED Matrix Layout

The R4 WiFi has a 12×8 LED matrix (96 LEDs total). Coordinates start at (0,0) in the top-left:

```
     x=0  x=1  x=2  x=3  x=4  x=5  x=6  x=7  x=8  x=9  x=10 x=11
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=0 |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=1 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=2 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=3 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=4 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=5 | 60 | 61 | 62 | 63 | 64 | 65 | 66 | 67 | 68 | 69 | 70 | 71 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=6 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 | 81 | 82 | 83 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=7 | 84 | 85 | 86 | 87 | 88 | 89 | 90 | 91 | 92 | 93 | 94 | 95 |
    +----+----+----+----+----+----+----+----+----+----+----+----+

● = LED ON     ○ = LED OFF (in diagrams below)
```

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

Sets the background state. For the monochrome matrix, this determines if background LEDs are on or off.

#### Syntax

```cpp
screen.background(ON)    // All background LEDs on
screen.background(OFF)   // All background LEDs off (default)
```

#### Parameters

- `ON` or `OFF`

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.background(OFF);   // Background LEDs off
screen.stroke(ON);
screen.point(6, 4);       // Draw a single lit LED
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
screen.set(x, y, ON)
screen.set(x, y, OFF)
```

#### Parameters

- `x`: x position (0-11)
- `y`: y position (0-7)
- `ON` or `OFF`

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.set(3, 2, ON);   // Turn on LED at 3,2
screen.set(4, 2, ON);   // Turn on LED at 4,2
screen.endDraw();
```

---

## Style Control Methods

The R4 WiFi has a **monochrome LED matrix** — LEDs are either ON or OFF. Use the simple `ON`/`OFF` constants:

```cpp
screen.stroke(ON);     // Outlines will light up LEDs
screen.fill(OFF);      // Interiors will be dark
screen.background(OFF); // Background stays dark
```

### `fill()`

#### Description

Sets whether shapes are filled (interior LEDs on or off).

#### Syntax

```cpp
screen.fill(ON)    // Fill shapes with lit LEDs
screen.fill(OFF)   // No fill (same as noFill)
```

#### Parameters

- `ON` or `OFF`

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.fill(ON);
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
screen.stroke(ON);
screen.noFill();
screen.rect(2, 2, 8, 4);  // Draw rectangle outline only
screen.endDraw();
```

---

### `stroke()`

#### Description

Sets whether shape outlines are drawn (stroke LEDs on or off).

#### Syntax

```cpp
screen.stroke(ON)    // Draw outlines with lit LEDs
screen.stroke(OFF)   // No outlines (same as noStroke)
```

#### Parameters

- `ON` or `OFF`

#### Returns

Nothing

#### Example

```cpp
screen.beginDraw();
screen.stroke(ON);
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
screen.fill(ON);
screen.rect(3, 2, 6, 4);  // Filled rectangle, no outline
screen.endDraw();
```

---

## Shape Drawing Methods

### Visual Guide to Drawing Primitives

This section shows how each drawing primitive looks on the 12×8 matrix with different style combinations.

**Legend:**
- `●` = LED ON
- `○` = LED OFF  
- Empty cell = LED OFF (for cleaner diagrams)

---

#### point(x, y) — Single Pixel

Draws a single LED at the specified coordinates.

**Dark background, point ON:**
```cpp
screen.background(OFF);      // Background OFF
screen.stroke(ON);           // Stroke ON
screen.point(5, 3);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 |   |   |   |   |   | ● |   |   |   |   |   |   |  ← point(5, 3)
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Lit background, point OFF (drawing a "hole"):**
```cpp
screen.background(ON);       // Background ON
screen.stroke(OFF);          // Stroke OFF
screen.point(5, 3);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● | ● | ● | ● | ● | ○ | ● | ● | ● | ● | ● | ● |  ← point OFF at (5, 3)
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

---

#### line(x1, y1, x2, y2) — Line Between Two Points

Draws a line from (x1, y1) to (x2, y2).

**Diagonal line:**
```cpp
screen.stroke(ON);
screen.line(1, 1, 8, 6);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   | ● |   |   |   |   |   |   |   |   |   |   |  ← start (1, 1)
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   | ● | ● |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 |   |   |   |   | ● |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   |   |   |   | ● | ● |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   | ● |   |   |   |  ← end (8, 6)
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Horizontal and vertical lines:**
```cpp
screen.stroke(ON);
screen.line(0, 3, 11, 3);  // Horizontal
screen.line(5, 0, 5, 7);   // Vertical
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   |   |   | ● |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   |   |   |   | ● |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   |   |   |   | ● |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |  ← horizontal line y=3
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   |   |   |   | ● |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   |   |   |   | ● |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
                      ↑
              vertical line x=5
```

---

#### rect(x, y, width, height) — Rectangle

Draws a rectangle. Uses `stroke()` for outline and `fill()` for interior.

**Stroke only (outline):**
```cpp
screen.stroke(ON);
screen.noFill();
screen.rect(2, 1, 8, 5);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |  ← top edge
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   | ● |   |   |   |   |   |   | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 |   |   | ● |   |   |   |   |   |   | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   | ● |   |   |   |   |   |   | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |  ← bottom edge
  +---+---+---+---+---+---+---+---+---+---+---+---+
          ↑                           ↑
        x=2                         x=9
```

**Fill only (solid rectangle, no outline):**
```cpp
screen.noStroke();
screen.fill(ON);
screen.rect(2, 1, 8, 5);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   | ● | ● | ● | ● | ● | ● | ● | ● |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Both stroke and fill:**
```cpp
screen.stroke(ON);
screen.fill(ON);
screen.rect(2, 1, 8, 5);
```
Same result as fill only — all interior LEDs are on.

**Lit background with OFF rectangle (creating a "window"):**
```cpp
screen.background(ON);       // All LEDs ON
screen.stroke(OFF);          // Stroke OFF
screen.fill(OFF);            // Fill OFF
screen.rect(3, 2, 6, 4);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 | ● | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 | ● | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 | ● | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Lit background, outline only OFF (creating a frame):**
```cpp
screen.background(ON);       // All LEDs ON
screen.stroke(OFF);          // Stroke OFF
screen.noFill();             // No fill
screen.rect(3, 2, 6, 4);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 | ● | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● |  ← top edge OFF
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● | ● | ● | ○ | ● | ● | ● | ● | ○ | ● | ● | ● |  ← interior still ON
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 | ● | ● | ● | ○ | ● | ● | ● | ● | ○ | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 | ● | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● |  ← bottom edge OFF
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

---

#### circle(cx, cy, diameter) — Circle

Draws a circle centered at (cx, cy) with specified diameter.

**Stroke only (outline):**
```cpp
screen.stroke(ON);
screen.noFill();
screen.circle(5, 3, 6);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   | ● | ● | ● | ● |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   | ● |   |   |   |   | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   | ● |   |   |   |   | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 |   |   | ● |   |   | ○ |   | ● |   |   |   |   |  ← center (5, 3)
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   | ● |   |   |   |   | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   |   | ● | ● | ● | ● |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Fill only (solid circle):**
```cpp
screen.noStroke();
screen.fill(ON);
screen.circle(5, 3, 6);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   | ● | ● | ● | ● |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   | ● | ● | ● | ● | ● | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 |   |   | ● | ● | ● | ● | ● | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 |   |   | ● | ● | ● | ● | ● | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 |   |   | ● | ● | ● | ● | ● | ● |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   |   | ● | ● | ● | ● |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Lit background with OFF circle (creating a "spotlight" effect):**
```cpp
screen.background(ON);       // All LEDs ON
screen.stroke(OFF);          // Stroke OFF
screen.fill(OFF);            // Fill OFF
screen.circle(5, 3, 6);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 | ● | ● | ● | ○ | ○ | ○ | ○ | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 | ● | ● | ○ | ○ | ○ | ○ | ○ | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 | ● | ● | ● | ○ | ○ | ○ | ○ | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

**Combo: Filled background rectangle with outline circle:**
```cpp
screen.noStroke();
screen.fill(ON);
screen.rect(0, 0, 12, 8);        // Fill entire screen

screen.stroke(OFF);          // Stroke OFF
screen.noFill();
screen.circle(5, 3, 6);          // Draw circle outline OFF
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 | ● | ● | ● | ○ | ○ | ○ | ○ | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 | ● | ● | ○ | ● | ● | ● | ● | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 | ● | ● | ○ | ● | ● | ● | ● | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● | ● | ○ | ● | ● | ● | ● | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 | ● | ● | ○ | ● | ● | ● | ● | ○ | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 | ● | ● | ● | ○ | ○ | ○ | ○ | ● | ● | ● | ● | ● |
  +---+---+---+---+---+---+---+---+---+---+---+---+

Ring of OFF pixels with ON center — inverse circle outline!
```

---

#### ellipse(cx, cy, width, height) — Ellipse

Draws an ellipse centered at (cx, cy) with specified width and height.

**Wide ellipse:**
```cpp
screen.stroke(ON);
screen.noFill();
screen.ellipse(5, 3, 10, 4);
```
```
    0   1   2   3   4   5   6   7   8   9  10  11
  +---+---+---+---+---+---+---+---+---+---+---+---+
0 |   |   |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
1 |   |   | ● | ● | ● | ● | ● | ● | ● |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
2 | ● | ● |   |   |   |   |   |   |   | ● | ● |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
3 | ● |   |   |   |   | ○ |   |   |   |   | ● |   |  ← center (5, 3)
  +---+---+---+---+---+---+---+---+---+---+---+---+
4 | ● | ● |   |   |   |   |   |   |   | ● | ● |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
5 |   |   | ● | ● | ● | ● | ● | ● | ● |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+---+---+
```

---

### Style Combinations Summary

| Background | Stroke | Fill | Result |
|------------|--------|------|--------|
| OFF | ON | OFF | Shape outline only (most common) |
| OFF | ON | ON | Solid filled shape |
| OFF | OFF | ON | Filled shape, no outline |
| ON | OFF | OFF | "Cut out" shape from lit background |
| ON | OFF | ON | Dark shape on bright background |
| ON | ON | OFF | Dark outline, bright interior |

---

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
screen.stroke(ON);
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
screen.stroke(ON);
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
screen.stroke(ON);
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
screen.stroke(ON);
screen.fill(ON);
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
screen.stroke(ON);
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
screen.stroke(ON);
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
    screen.stroke(ON);
    screen.textFont(Font_4x6);
    screen.text("Hi!", 1, 1);
    screen.endDraw();
    
    delay(2000);
}

void loop() {
    // Scrolling text
    screen.beginDraw();
    screen.stroke(ON);
    screen.textScrollSpeed(100);
    screen.textFont(Font_4x6);
    screen.beginText(0, 1);
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
    screen.stroke(ON);
    screen.noFill();
    screen.rect(1, 1, 10, 6);
    screen.endDraw();
    delay(1000);
    
    // Filled rectangle
    screen.beginDraw();
    screen.clear();
    screen.stroke(ON);
    screen.fill(ON);
    screen.rect(2, 2, 8, 4);
    screen.endDraw();
    delay(1000);
    
    // Circle outline
    screen.beginDraw();
    screen.clear();
    screen.stroke(ON);
    screen.noFill();
    screen.circle(6, 4, 6);
    screen.endDraw();
    delay(1000);
    
    // Filled circle
    screen.beginDraw();
    screen.clear();
    screen.stroke(ON);
    screen.fill(ON);
    screen.circle(6, 4, 4);
    screen.endDraw();
    delay(1000);
    
    // Crossed diagonal lines
    screen.beginDraw();
    screen.clear();
    screen.stroke(ON);
    screen.line(0, 0, 11, 7);
    screen.line(0, 7, 11, 0);
    screen.endDraw();
    delay(1000);
    
    // Point pattern
    screen.beginDraw();
    screen.clear();
    screen.stroke(ON);
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
    screen.stroke(ON);
    
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
