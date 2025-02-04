/*
 * TinyFilmFestival Library
 * For Arduino UNO R4 WiFi LED Matrix
 */

#include "TinyFilmFestival.h"

TinyFilmFestival::TinyFilmFestival() :
    isCustomSpeed(false),
    customSpeedInterval(0),
    isPaused(false),
    originalTimings(nullptr),
    frameCount(0),
    currentFrameIndex(0),
    isBoomerang(false),
    isReversing(false),
    sequenceCompleted(false),
    currentAnimation(nullptr),
    lastUpdateTime(0),
    currentMode(PLAY_ONCE)
{
}

TinyFilmFestival::~TinyFilmFestival() {
    cleanup();
}

void TinyFilmFestival::cleanup() {
    if (originalTimings != nullptr) {
        delete[] originalTimings;
        originalTimings = nullptr;
    }
}

void TinyFilmFestival::copyTimings(const uint32_t frames[][4], uint32_t numFrames) {
    cleanup();
    frameCount = numFrames;
    originalTimings = new uint32_t[frameCount];
    
    for (uint32_t i = 0; i < frameCount; i++) {
        originalTimings[i] = frames[i][3];
    }
}

bool TinyFilmFestival::begin() {
    return baseMatrix.begin();
}

void TinyFilmFestival::setSpeed(uint32_t speedMs) {
    if (speedMs == 0) {
        isPaused = true;
    } else {
        isPaused = false;
        isCustomSpeed = true;
        customSpeedInterval = speedMs;
    }
}

void TinyFilmFestival::pause() {
    isPaused = true;
}

void TinyFilmFestival::resume() {
    isPaused = false;
    lastUpdateTime = millis();
}

void TinyFilmFestival::restoreOriginalSpeed() {
    isCustomSpeed = false;
    isPaused = false;
    lastUpdateTime = millis();
}

bool TinyFilmFestival::isPausedState() {
    return isPaused;
}

bool TinyFilmFestival::sequenceDone() {
    if (sequenceCompleted) {
        sequenceCompleted = false;
        return true;
    }
    return false;
}

uint32_t TinyFilmFestival::getCurrentFrame() {
    return currentFrameIndex;
}

void TinyFilmFestival::update() {
    updateFrame();
}

void TinyFilmFestival::displayFrame(const uint32_t frame[3]) {
    baseMatrix.loadFrame(frame);
    isPaused = true;
    currentAnimation = nullptr;
}

void TinyFilmFestival::updateFrame() {
    if (isPaused || currentAnimation == nullptr) return;

    unsigned long currentTime = millis();
    uint32_t interval = isCustomSpeed ? customSpeedInterval : originalTimings[currentFrameIndex];

    if (currentTime - lastUpdateTime >= interval) {
        // Load current frame
        const uint32_t frame[3] = {
            currentAnimation[currentFrameIndex][0],
            currentAnimation[currentFrameIndex][1],
            currentAnimation[currentFrameIndex][2]
        };
        baseMatrix.loadFrame(frame);

        // Update frame index based on mode
        if (isBoomerang) {
            if (!isReversing) {
                currentFrameIndex++;
                if (currentFrameIndex >= frameCount - 1) {
                    isReversing = true;
                    currentFrameIndex = frameCount - 1;
                }
            } else {
                currentFrameIndex--;
                if (currentFrameIndex == 0) {
                    isReversing = false;
                    if (currentMode == PLAY_ONCE) {
                        isPaused = true;
                        sequenceCompleted = true;
                    }
                }
            }
        } else {
            currentFrameIndex = (currentFrameIndex + 1) % frameCount;
            if (currentFrameIndex == 0) {
                if (currentMode == PLAY_ONCE) {
                    isPaused = true;
                    sequenceCompleted = true;
                }
            }
        }

        lastUpdateTime = currentTime;
    }
}