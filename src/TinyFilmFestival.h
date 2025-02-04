/*
 * TinyFilmFestival Library
 * For Arduino UNO R4 WiFi LED Matrix
 */

#pragma once

#include "Arduino_LED_Matrix.h"

// Animation playback modes
enum PlayMode {
    PLAY_ONCE,      // Play animation one time and stop
    PLAY_LOOP,      // Play animation forward repeatedly
    PLAY_BOOMERANG  // Play forward and backward repeatedly
};

class TinyFilmFestival {
private:
    ArduinoLEDMatrix baseMatrix;
    bool isCustomSpeed;
    uint32_t customSpeedInterval;
    bool isPaused;
    uint32_t* originalTimings;
    uint32_t frameCount;
    uint32_t currentFrameIndex;
    bool isBoomerang;
    bool isReversing;
    bool sequenceCompleted;
    const uint32_t (*currentAnimation)[4];
    unsigned long lastUpdateTime;
    PlayMode currentMode;

    void cleanup();
    void copyTimings(const uint32_t frames[][4], uint32_t numFrames);
    void updateFrame();

public:
    TinyFilmFestival();
    ~TinyFilmFestival();

    // Initialize the matrix
    bool begin();

    // Start an animation with specified mode
    template<size_t N>
    void startAnimation(const uint32_t (&frames)[N][4], PlayMode mode = PLAY_ONCE) {
        currentMode = mode;
        isBoomerang = (mode == PLAY_BOOMERANG);
        
        uint32_t numFrames = N;
        currentAnimation = frames;
        copyTimings(frames, numFrames);
        
        currentFrameIndex = 0;
        isReversing = false;
        isPaused = false;
        sequenceCompleted = false;
        lastUpdateTime = millis();
        
        const uint32_t frame[3] = {frames[0][0], frames[0][1], frames[0][2]};
        baseMatrix.loadFrame(frame);
    }

    // Animation control methods
    void setSpeed(uint32_t speedMs);
    void pause();
    void resume();
    void restoreOriginalSpeed();
    void update();
    void displayFrame(const uint32_t frame[3]);

    // Status check methods
    bool isPausedState();
    bool sequenceDone();
    uint32_t getCurrentFrame();
};