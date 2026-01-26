/*
 * ScrollingText Example
 * TinyFilmFestival V2 - Canvas Mode
 * 
 * Demonstrates text display and scrolling on the LED matrix.
 * Shows static text, then scrolling text in different directions.
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
    // Scroll text left
    screen.textScrollSpeed(100);
    screen.beginText(0, 1, 0xFFFFFF);
    screen.print("  Hello Arduino R4!  ");
    screen.endText(SCROLL_LEFT);
    
    delay(500);
    
    // Scroll text right
    screen.beginText(0, 1, 0xFFFFFF);
    screen.print("  TinyFilmFestival  ");
    screen.endText(SCROLL_RIGHT);
    
    delay(500);
}
