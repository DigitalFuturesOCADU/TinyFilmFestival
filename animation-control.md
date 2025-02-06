# Animation Control Examples

## Table of Contents
- [AnimationPlayback_01_PlayAnimation](#animationplayback_01_playanimation)
- [AnimationPlayback_02_PlayStates](#animationplayback_02_playstates)
- [AnimationPlayback_03_CyclePlayStates](#animationplayback_03_cycleplaystates)
- [AnimationPlayback_04_PlayStatesMULTI](#animationplayback_04_playstatesmulti)
- [AnimationPlayback_05_CyclePlayStatesMULTI](#animationplayback_05_cycleplaystatesmulti)

## AnimationPlayback_01_PlayAnimation

Simple animation playback with speed control.

```cpp
/*
 * TinyFilmFestival - Example 1
 * Basic Animation Control
 * 
 * This example shows the simplest way to use the TinyFilmFestival library.
 * It demonstrates how to:
 *   - Create an Animation object from frame data
 *   - Set different playback modes (ONCE, LOOP, BOOMERANG)
 *   - Control animation playback
 * 
 * Available Playback Modes:
 *   - ONCE: Play animation one time and stop
 *   - LOOP: Play animation forward repeatedly
 *   - BOOMERANG: Play animation forward then backward repeatedly
 * 
 * Animation Control Methods:
 *   - startAnimation(animation, mode): Start playing an animation
 *   - setSpeed(milliseconds): Set a custom frame duration
 *   - restoreOriginalSpeed(): Return to original frame timings
 *   - pause(): Pause the animation
 *   - resume(): Resume a paused animation
 *   - stop(): Stop the animation completely
 *   - update(): Update the animation (call in loop)
 * 
 * Status Methods:
 *   - isPlaying(): Check if animation is playing
 *   - isPaused(): Check if animation is paused
 *   - isComplete(): Check if animation is complete
 *   - getState(): Get current animation state
 *   - getCurrentFrame(): Get current frame number
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * 
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "animation.h"     // Your animation file from LED Matrix Editor

// Create an instance of TinyFilmFestival
TinyFilmFestival film;

// Create an Animation object from the frame data
Animation myAnimation = animation;

// Animation control settings
int playSpeed = 50;    // Animation speed in milliseconds

void setup() {
    // Start the LED matrix
    film.begin();
    
    // Uncomment different lines to try various playback methods
    
    // Method 1: Play animation once and stop
    //film.startAnimation(myAnimation, ONCE);
    
    // Method 2: Play animation in a continuous loop
    //film.startAnimation(myAnimation, LOOP);
    
    // Method 3: Play animation in boomerang mode (forward/backward)
    film.startAnimation(myAnimation, BOOMERANG);
    
    // Optional: Set a custom playback speed
    film.setSpeed(playSpeed);
    
    // Other control examples (uncomment to try):
    //film.pause();              // Pause the animation
    //film.resume();             // Resume the animation
    //film.restoreOriginalSpeed(); // Use original frame timings
    //film.stop();              // Stop the animation
}

void loop() {
    // Required: Update the animation in each loop
    film.update();
    
    // Optional: Check animation status
    // if (film.isComplete()) {
    //     // Animation has finished (in ONCE mode)
    // }
    
    // if (film.isPaused()) {
    //     // Animation is paused
    // }
}
```

## AnimationPlayback_02_PlayStates

Combines animation control and a simple state machine

```cpp
/*
 * TinyFilmFestival - State Machine Example
 * 
 * This example demonstrates how to combine animation control with a simple
 * state machine to create different playback effects. The example shows:
 *   - How to declare and use the Animation type
 *   - Basic state machine implementation
 *   - Timer-based state transitions
 *   - How animation parameters change with states
 *   - Different playback modes (ONCE, LOOP, BOOMERANG)
 * 
 * 
 * State 0: Normal speed (100ms), plays once
 * State 1: Fast speed (50ms), loops
 * State 2: Slow speed (200ms), boomerang
 * State 3: Original speed from animation data, loops
 * State 4: Paused
 * 
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "animation.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object from the imported frame data
Animation myAnimation = animation;

// State machine variables
int currentState = 0;            // Tracks which state we're in (0-4)


// Speed settings for different states
int normalSpeed = 100;  // Normal playback speed (milliseconds)
int fastSpeed = 50;     // Fast playback speed
int slowSpeed = 200;    // Slow playback speed

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
            // Handle state transition
        switch (currentState) 
        {
            case 0:
                // Normal speed, play once
                film.startAnimation(myAnimation, ONCE);
                film.setSpeed(normalSpeed);
                Serial.println("State 0: Normal speed, Play Once");
                break;
                
            case 1:
                // Fast speed, looping
                film.startAnimation(myAnimation, LOOP);
                film.setSpeed(fastSpeed);
                Serial.println("State 1: Fast speed, Looping");
                break;
                
            case 2:
                // Slow speed, boomerang
                film.startAnimation(myAnimation, BOOMERANG);
                film.setSpeed(slowSpeed);
                Serial.println("State 2: Slow speed, Boomerang");
                break;
                
            case 3:
                // Original timing from animation data, looping
                film.startAnimation(myAnimation, LOOP);
                film.restoreOriginalSpeed();
                Serial.println("State 3: Original speed from animation, Looping");
                break;
                
            case 4:
                // Paused state
                film.pause();
                Serial.println("State 4: Paused");
                break;
        }
}

void loop() {
    // Update the animation frame
    film.update();
    
 
        

    
}
```

## AnimationPlayback_03_CyclePlayStates

Uses a timer to cycle through the different play states

```cpp
/*
 * TinyFilmFestival - State Machine Example
 * 
 * This example demonstrates how to combine animation control with a simple
 * state machine to create different playback effects. The example shows:
 *   - How to declare and use the Animation type
 *   - Basic state machine implementation
 *   - Timer-based state transitions
 *   - How animation parameters change with states
 *   - Different playback modes (ONCE, LOOP, BOOMERANG)
 * 
 * The animation cycles through 5 states:
 * State 0: Normal speed (100ms), plays once
 * State 1: Fast speed (50ms), loops
 * State 2: Slow speed (200ms), boomerang
 * State 3: Original speed from animation data, loops
 * State 4: Paused
 * 
 * Each state lasts for 5 seconds before transitioning to the next state.
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * 
 * Animation Created using the Arduino LED Matrix Editor : https://ledmatrix-editor.arduino.cc/
 */

#include "TinyFilmFestival.h"
#include "animation.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation object from the imported frame data
Animation myAnimation = animation;

// State machine variables
int currentState = 0;            // Tracks which state we're in (0-4)
unsigned long lastStateChange;    // Timestamp of last state change
unsigned long stateDuration = 5000;  // Duration of each state (5 seconds)

// Speed settings for different states
int normalSpeed = 100;  // Normal playback speed (milliseconds)
int fastSpeed = 50;     // Fast playback speed
int slowSpeed = 200;    // Slow playback speed

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize the LED matrix
    film.begin();
    
    // Record the start time
    lastStateChange = millis();
    
    // Start with initial animation in ONCE mode
    film.startAnimation(myAnimation, ONCE);
    
    // Print initial state information
    Serial.println("Starting State Machine Demo");
    Serial.println("State 0: Normal speed, Play Once");
}

void loop() {
    // Update the animation frame
    film.update();
    
    // Check if it's time to change state (every 5 seconds)
    if (millis() - lastStateChange >= stateDuration) {
        // Move to next state (0-4)
        currentState = (currentState + 1) % 5;
        lastStateChange = millis();
        
        // Handle state transition
        switch (currentState) {
            case 0:
                // Normal speed, play once
                film.startAnimation(myAnimation, ONCE);
                film.setSpeed(normalSpeed);
                Serial.println("State 0: Normal speed, Play Once");
                break;
                
            case 1:
                // Fast speed, looping
                film.startAnimation(myAnimation, LOOP);
                film.setSpeed(fastSpeed);
                Serial.println("State 1: Fast speed, Looping");
                break;
                
            case 2:
                // Slow speed, boomerang
                film.startAnimation(myAnimation, BOOMERANG);
                film.setSpeed(slowSpeed);
                Serial.println("State 2: Slow speed, Boomerang");
                break;
                
            case 3:
                // Original timing from animation data, looping
                film.startAnimation(myAnimation, LOOP);
                film.restoreOriginalSpeed();
                Serial.println("State 3: Original speed from animation, Looping");
                break;
                
            case 4:
                // Paused state
                film.pause();
                Serial.println("State 4: Paused");
                break;
        }
    }
}
```

## AnimationPlayback_04_PlayStatesMULTI

State is changed by variable. Changes between multiple animations

```cpp
/*
 * TinyFilmFestival - Simple Two State Example
 * 
 * This example shows how to select between two animations using a variable.
 * 
 * Animations:
 * - idle: 4-frame idle animation
 * - go: 9-frame go animation
 * 
 * Set useIdleAnimation to:
 * true - plays idle animation
 * false - plays go animation
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation objects
Animation idleAnim = idle;
Animation goAnim = go;

// Animation selection
bool useIdleAnimation = true;  // Set to false to use go animation

void setup() {
    // Initialize the LED matrix
    film.begin();
    
    // Start the selected animation
    if (useIdleAnimation) {
        film.startAnimation(idleAnim, BOOMERANG);
    } else {
        film.startAnimation(goAnim, BOOMERANG);
    }
}

void loop() {
    // Update the animation frame
    film.update();
}
```

## AnimationPlayback_05_CyclePlayStatesMULTI

States cycle based on a timer. Changes between multiple animations

```cpp
/*
 * TinyFilmFestival - Multiple Animation State Machine Example
 * 
 * This example demonstrates managing multiple animations with a state machine.
 * It uses two animations:
 * - idle: A 4-frame animation with varied timing (150-300ms)
 * - go: A 9-frame animation with varied timing (66-300ms)
 * 
 * States cycle every 5 seconds:
 * State 0: Idle animation, normal speed, plays once
 * State 1: Go animation, fast speed, loops
 * State 2: Idle animation, slow speed, boomerang
 * State 3: Go animation, original timing, loops
 * State 4: Idle animation, paused
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 *
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

// Create instance of TinyFilmFestival
TinyFilmFestival film;

// Create Animation objects from the imported frame data
Animation idleAnim = idle;
Animation goAnim = go;

// State machine variables
int currentState = 0;            // Tracks which state we're in (0-4)
unsigned long lastStateChange;    // Timestamp of last state change
unsigned long stateDuration = 5000;  // Duration of each state (5 seconds)

// Speed settings for different states
int normalSpeed = 100;  // Normal playback speed (milliseconds)
int fastSpeed = 50;     // Fast playback speed
int slowSpeed = 200;    // Slow playback speed

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the LED matrix
    film.begin();

    // Record the start time
    lastStateChange = millis();

    // Start with initial animation in ONCE mode
    film.startAnimation(idleAnim, ONCE);

    // Print initial state information
    Serial.println("Starting Two-Animation State Machine Demo");
    Serial.println("State 0: Idle animation, Normal speed, Play Once");
}

void loop() {
    // Update the animation frame
    film.update();

    // Check if it's time to change state (every 5 seconds)
    if (millis() - lastStateChange >= stateDuration) {
        // Move to next state (0-4)
        currentState = (currentState + 1) % 5;
        lastStateChange = millis();

        // Handle state transition
        switch (currentState) {
            case 0:
                // Idle animation, normal speed, play once
                film.startAnimation(idleAnim, ONCE);
                film.setSpeed(normalSpeed);
                Serial.println("State 0: Idle animation, Normal speed, Play Once");
                break;

            case 1:
                // Go animation, fast speed, looping
                film.startAnimation(goAnim, LOOP);
                film.setSpeed(fastSpeed);
                Serial.println("State 1: Go animation, Fast speed, Looping");
                break;

            case 2:
                // Idle animation, slow speed, boomerang
                film.startAnimation(idleAnim, BOOMERANG);
                film.setSpeed(slowSpeed);
                Serial.println("State 2: Idle animation, Slow speed, Boomerang");
                break;

            case 3:
                // Go animation, original timing, looping
                film.startAnimation(goAnim, LOOP);
                film.restoreOriginalSpeed();
                Serial.println("State 3: Go animation, Original timing, Looping");
                break;

            case 4:
                // Idle animation, paused
                film.startAnimation(idleAnim, LOOP);
                film.pause();
                Serial.println("State 4: Idle animation, Paused");
                break;
        }
    }
}
```