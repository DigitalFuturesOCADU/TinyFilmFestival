/*
 * TinyFilmFestival - Example 2
 * Multiple Animation Control with Frame Combining
 * 
 * This example shows how to play multiple animations simultaneously
 * by combining their frames. It demonstrates:
 *   - Creating multiple TinyFilmFestival objects
 *   - Loading different animations for each object
 *   - Running animations in parallel with frame combining
 *   - Setting different speeds for each animation
 * 
 * Animation Files:
 *   The animation array variable name matches the header filename:
 *   - landscape.h -> const uint32_t landscape[][4]
 *   - pow.h -> const uint32_t pow[][4]
 *   This name is set when exporting from the Matrix Editor
 * 
 * Multiple Animation Tips:
 *   - Each TinyFilmFestival object runs one animation
 *   - The CombinedFilmFestival class combines frames from multiple animations
 *   - Animations are layered in the order they are added
 *   - Each animation maintains independent:
 *     - Speed settings
 *     - Play modes
 *     - Start/end frames
 * 
 * Hardware Required:
 * - Arduino UNO R4 WiFi with built-in LED Matrix
 * 
 * Uses Arduino LED Matrix Editor https://ledmatrix-editor.arduino.cc/ 
 */

#include "TinyFilmFestival.h"
#include "landscape.h"    // First animation file
#include "fiz.h"         // Second animation file

// Create two TinyFilmFestival objects for animations
TinyFilmFestival film1;
TinyFilmFestival film2;

// Create a CombinedFilmFestival to merge the animations
CombinedFilmFestival combinedFilm;

// Create Animation objects from the frame data
Animation landscapeAnim = landscape;
Animation powAnim = fiz;

// Animation control settings
int speed1 = 100;    // Speed for first animation (milliseconds)
int speed2 = 50;     // Speed for second animation (milliseconds)

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("Starting multiple animation demo");
    Serial.print("Landscape animation frames: ");
    Serial.println(landscapeAnim.getFrameCount());
    Serial.print("Pow animation frames: ");
    Serial.println(powAnim.getFrameCount());
    
    // Start the LED matrix
    combinedFilm.begin();
    
    // Configure first animation (landscape)
    film1.startAnimation(landscapeAnim, LOOP);
    film1.setSpeed(speed1);
    
    // Configure second animation (pow)
    film2.startAnimation(powAnim, LOOP);
    film2.setSpeed(speed2);
    
    // Add animations to the combiner
    // Order matters - first added appears "behind" later ones
    combinedFilm.addFilm(film1);  // Landscape in background
    combinedFilm.addFilm(film2);  // Pow effect in foreground
}

void loop() {
    // Update the combined animation
    // This will update all animations and merge their frames
    combinedFilm.update();
    
    // Optional: Monitor animation states
    if (film1.isComplete()) 
    {
        Serial.println("Landscape animation completed a cycle");
    }
    
    if (film2.isComplete()) 
    {
        Serial.println("Pow animation completed a cycle");
    }
}