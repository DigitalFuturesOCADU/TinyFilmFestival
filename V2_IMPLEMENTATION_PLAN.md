# TinyFilmFestival V2.0 - Implementation Plan

> **Status**: 🟢 ALL 13 EXAMPLES COMPLETE + VERIFIED  
> **Last Updated**: January 26, 2026  
> **Progress**: 20/35 tasks (57%)

---

## Overview

TinyFilmFestival V2.0 unifies two approaches to the Arduino R4 WiFi LED Matrix:

| Animation Mode | Canvas Mode |
|----------------|-------------|
| Pre-made frames from LED Matrix Editor | Code-generated moving graphics |
| `play()`, `pause()`, `setSpeed()` | `beginDraw()`, `point()`, `circle()` |
| Content in `.h` files | Content in code logic |

**New in V2.0**: Hybrid Mode combines both — animations with code-drawn overlays.

---

## Final Example Structure (13 total)

```
examples/
├── 01_Basics/                           # Foundation
│   ├── FirstAnimation/                  # [EDIT] From existing
│   └── FirstCanvas/                     # [NEW]
│
├── 02_Animation_Mode/                   # Pre-made animation control  
│   ├── PlaybackControl/                 # [CONSOLIDATE] Modes + Speed
│   └── LayeredAnimations/               # [EDIT] From existing
│
├── 03_Canvas_Mode/                      # Code-generated graphics
│   ├── MovingShapes/                    # [NEW]
│   └── LayeredGraphics/                 # [NEW]
│
├── 04_Hybrid_Mode/                      # Animation + Canvas combined
│   └── AnimationWithOverlay/            # [NEW]
│
├── 05_Sensor_Control/                   # Interactive control
│   ├── Button_PlayPause/                # [CONSOLIDATE]
│   ├── Button_ContentSwitch/            # [CONSOLIDATE]
│   ├── Distance_SpeedControl/           # [EDIT]
│   ├── Distance_ZoneSwitch/             # [CONSOLIDATE]
│   └── Pressure_SpeedControl/           # [EDIT]
│
└── 06_Projects/                         # Complete example
    └── InteractiveCharacter/            # [NEW]
```

### Legend
- `[NEW]` — Write from scratch
- `[EDIT]` — Modify existing example
- `[CONSOLIDATE]` — Merge multiple existing examples into one

---

## Implementation Tasks

### Phase 1: Library Extensions
*Add Canvas/Hybrid capabilities to TinyFilmFestival*

- [ ] **1.1** Create `TinyScreen` wrapper class in `src/`
- [ ] **1.2** Wrap ArduinoGraphics drawing methods (`point`, `line`, `rect`, `circle`, `text`)
- [ ] **1.3** Add `play()` as alias for `startAnimation()`
- [ ] **1.4** Add `beginOverlay()`/`endOverlay()` for hybrid mode
- [ ] **1.5** Add simplified constants (`ON`/`OFF`)
- [ ] **1.6** Test backward compatibility with existing examples

### Phase 2: Folder Restructure
*Reorganize examples folder*

- [x] **2.1** Create new folder structure (`01_Basics/`, etc.)
- [x] **2.2** Move existing examples to new locations
- [x] **2.3** Rename `.ino` files to match new folder names
- [ ] **2.4** Delete deprecated/merged example folders *(deferred to Phase 10)*
- [x] **2.5** Copy required `.h` animation files to each example folder

### Phase 3: Basics Examples ✅
*Entry point for new users*

- [x] **3.1** `FirstAnimation/` — Simplified to 30 lines
- [x] **3.2** `FirstCanvas/` — NEW: Bouncing dot (minimal code)

### Phase 4: Animation Mode Examples ✅

- [x] **4.1** `PlaybackControl/` — Cycles through all modes + speeds (85 lines)
- [x] **4.2** `LayeredAnimations/` — Streamlined to 50 lines

### Phase 5: Canvas Mode Examples

- [x] **5.1** `MovingShapes/` — NEW: Motion types mirroring PlayModes
- [x] **5.2** `LayeredGraphics/` — NEW: Multiple independent animated elements

### Phase 6: Hybrid Mode Example

- [x] **6.1** `AnimationWithOverlay/` — NEW: Animation + drawn indicator

### Phase 7: Sensor Control Examples ✅

- [x] **7.1** `Button_PlayPause/` — Clean toggle with debounce (48 lines)
- [x] **7.2** `Button_ContentSwitch/` — State-change detection (47 lines)
- [x] **7.3** `Distance_SpeedControl/` — Mapped distance→speed (65 lines)
- [x] **7.4** `Distance_ZoneSwitch/` — Threshold-based switching (65 lines)
- [x] **7.5** `Pressure_SpeedControl/` — Analog pressure→speed (56 lines)

### Phase 8: Project Example

- [x] **8.1** `InteractiveCharacter/` — NEW: Full project combining all concepts

### Phase 9: Documentation

- [ ] **9.1** Streamline `README.md` (quick start only)
- [ ] **9.2** Create `docs/getting-started.md`
- [ ] **9.3** Create `docs/animation-mode.md`
- [ ] **9.4** Create `docs/canvas-mode.md`
- [ ] **9.5** Create `docs/hybrid-mode.md`
- [ ] **9.6** Create `docs/api-reference.md`
- [ ] **9.7** Update `library.properties` version to 2.0.0

### Phase 10: Cleanup

- [x] **10.1** Delete old example folders (5 folders removed)
- [x] **10.2** Remove deprecated documentation files (5 files removed)
- [x] **10.3** Test all 13 examples compile ✅ (Arduino CLI verified)
- [ ] **10.4** Final review and commit

---

## Example Specifications

### 01_Basics/FirstAnimation
**Source**: Simplify `AnimationPlayback_01_PlayAnimation`  
**Purpose**: Absolute minimum to play a pre-made animation  
**Lines**: ~20

```cpp
#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    screen.update();
}
```

---

### 01_Basics/FirstCanvas
**Source**: NEW  
**Purpose**: Absolute minimum code-generated animation  
**Lines**: ~25

```cpp
#include "TinyFilmFestival.h"

TinyScreen screen;
int x = 0;
int direction = 1;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    screen.point(x, 4);
    screen.endDraw();
    
    x += direction;
    if (x >= 11 || x <= 0) direction *= -1;
    delay(100);
}
```

---

### 02_Animation_Mode/PlaybackControl
**Source**: CONSOLIDATE `AnimationPlayback_01` + `AnimationPlayback_02`  
**Purpose**: All playback modes and speed control in one example  
**Lines**: ~50

Shows: ONCE, LOOP, BOOMERANG modes + `setSpeed()` + `resetSpeed()`  
Uses Serial menu to switch between states.

---

### 02_Animation_Mode/LayeredAnimations
**Source**: EDIT `AnimationPlayback_06_PlayMultipleAtOnce`  
**Purpose**: CombinedFilmFestival for layered playback  
**Lines**: ~40

Clean up comments, standardize header format.

---

### 03_Canvas_Mode/MovingShapes
**Source**: NEW  
**Purpose**: Code-generated animations with ONCE/LOOP/BOOMERANG behavior  
**Lines**: ~60

Bouncing circle with three motion modes (mirrors PlaybackControl).

---

### 03_Canvas_Mode/LayeredGraphics
**Source**: NEW  
**Purpose**: Multiple independent animated elements  
**Lines**: ~50

Three layers at different speeds (mirrors LayeredAnimations).

---

### 04_Hybrid_Mode/AnimationWithOverlay
**Source**: NEW  
**Purpose**: Pre-made animation with code-drawn overlay  
**Lines**: ~35

Animation plays + indicator bar drawn on top.

---

### 05_Sensor_Control/Button_PlayPause
**Source**: CONSOLIDATE from `AnimationBUTTON_01`  
**Purpose**: Digital input controls play/pause  
**Lines**: ~30

Includes commented Canvas Mode alternative.

---

### 05_Sensor_Control/Button_ContentSwitch
**Source**: CONSOLIDATE from `AnimationBUTTON_03` + `_04`  
**Purpose**: Button switches between animations  
**Lines**: ~35

---

### 05_Sensor_Control/Distance_SpeedControl
**Source**: EDIT `DistanceSensor_02_SpeedChange`  
**Purpose**: Continuous analog input → speed mapping  
**Lines**: ~45

Clean up, standardize header.

---

### 05_Sensor_Control/Distance_ZoneSwitch
**Source**: CONSOLIDATE `DistanceSensor_03` + `_04`  
**Purpose**: Threshold-based content switching  
**Lines**: ~40

---

### 05_Sensor_Control/Pressure_SpeedControl
**Source**: EDIT `PressureMush_02_SpeedChange`  
**Purpose**: Analog pressure → speed (shows second sensor type)  
**Lines**: ~40

---

### 06_Projects/InteractiveCharacter
**Source**: NEW  
**Purpose**: Complete project combining Animation + Canvas + Sensors  
**Lines**: ~80

Character reacts to proximity:
- Far: Sleeping (slow idle)
- Medium: Alert (normal speed)
- Close: Excited (fast + sparkle overlay)

---

## Files to Delete After Migration

```
examples/
├── Animation Control BUTTON/        # → Merged into 05_Sensor_Control/
├── Animation Control Distance/      # → Merged into 05_Sensor_Control/
├── Animation Control Pressure Mush/ # → Merged into 05_Sensor_Control/
├── Animation Playback/              # → Merged into 02_Animation_Mode/
└── Basic Matrix/                    # → Replaced by 01_Basics/
```

**Documentation files to consolidate/delete:**
- `animation-control.md` → Merge into `docs/animation-mode.md`
- `button-control.md` → Merge into `docs/` sensor section
- `basic-matrix.md` → Merge into `docs/getting-started.md`
- `ArduinoGraphics_R4.md` → Merge into `docs/canvas-mode.md`

---

## Progress Summary

| Phase | Tasks | Complete | Status |
|-------|-------|----------|--------|
| 1. Library Extensions | 6 | 0 | ⬜ Not Started |
| 2. Folder Restructure | 5 | 4 | ✅ Complete |
| 3. Basics Examples | 2 | 1 | 🟡 In Progress |
| 4. Animation Mode | 2 | 0 | ⬜ Not Started |
| 5. Canvas Mode | 2 | 2 | ✅ Complete |
| 6. Hybrid Mode | 1 | 1 | ✅ Complete |
| 7. Sensor Control | 5 | 0 | ⬜ Not Started |
| 8. Project Example | 1 | 1 | ✅ Complete |
| 9. Documentation | 7 | 0 | ⬜ Not Started |
| 10. Cleanup | 4 | 0 | ⬜ Not Started |
| **TOTAL** | **35** | **9** | **26%** |

---

## Decision Log

| Date | Decision |
|------|----------|
| 2026-01-26 | Finalized at 13 examples (Minimum + InteractiveCharacter) |
| 2026-01-26 | Unified class name: `TinyScreen` |
| 2026-01-26 | Hybrid mode uses `beginOverlay()`/`endOverlay()` |
| 2026-01-26 | Canvas examples must show motion (no static graphics) |

---

*Plan Version: 1.0*  
*Ready for implementation*
