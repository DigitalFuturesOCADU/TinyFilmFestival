// TinyFilmFestival.cpp
#include "TinyFilmFestival.h"

TinyFilmFestival::TinyFilmFestival() :
    isCustomSpeed(false),
    customSpeedInterval(0),
    originalTimings(nullptr),
    frameCount(0),
    currentFrameIndex(0),
    isBoomerang(false),
    isReversing(false),
    currentAnimation(nullptr),
    lastUpdateTime(0),
    currentMode(PLAY_ONCE),
    currentState(IDLE)
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
    currentAnimation = nullptr;
    frameCount = 0;
}

bool TinyFilmFestival::shouldStartNewAnimation(const Animation& animation, PlayMode mode) const {
    // If we're not playing anything or in IDLE state, definitely start
    if (!isValidAnimation() || currentState == IDLE) {
        return true;
    }
    
    // If it's a different animation or different mode, start new
    if (currentAnimation != animation.getFrames() || currentMode != mode) {
        return true;
    }
    
    // If we're completed and not in PLAY_ONCE, restart
    if (currentState == COMPLETED && mode != PLAY_ONCE) {
        return true;
    }
    
    // Otherwise, don't restart
    return false;
}

void TinyFilmFestival::copyTimings(const uint32_t frames[][4], uint32_t numFrames) {
    if (originalTimings != nullptr) {
        delete[] originalTimings;
    }
    
    originalTimings = new uint32_t[numFrames];
    for (uint32_t i = 0; i < numFrames; i++) {
        originalTimings[i] = frames[i][3];
    }
}

bool TinyFilmFestival::begin() {
    bool success = baseMatrix.begin();
    if (success) {
        setState(IDLE);
    }
    return success;
}

void TinyFilmFestival::setState(AnimationState newState) {
    if (currentState == newState) return;
    
    // Handle state exit actions
    switch (currentState) {
        case PLAYING:
            // Store last frame time in case we resume
            break;
        default:
            break;
    }
    
    currentState = newState;
    
    // Handle state entry actions
    switch (currentState) {
        case IDLE:
            cleanup();
            break;
            
        case PLAYING:
            if (!isValidAnimation()) {
                currentState = IDLE;
            }
            break;
            
        case COMPLETED:
            if (currentMode != PLAY_ONCE && isValidAnimation()) {
                setState(PLAYING);
            }
            break;
            
        case PAUSED:
            break;
    }
}

void TinyFilmFestival::setSpeed(uint32_t speedMs) {
    if (!isValidAnimation()) return;
    
    if (speedMs == 0) {
        setState(PAUSED);
    } else {
        isCustomSpeed = true;
        customSpeedInterval = speedMs;
        
        if (currentState != PLAYING) {
            lastUpdateTime = millis();
            setState(PLAYING);
        }
    }
}

void TinyFilmFestival::pause() {
    if (currentState == PLAYING) {
        setState(PAUSED);
    }
}

void TinyFilmFestival::resume() {
    if (currentState != PLAYING && isValidAnimation()) {
        lastUpdateTime = millis();
        setState(PLAYING);
    }
}

void TinyFilmFestival::restoreOriginalSpeed() {
    if (!isValidAnimation()) return;
    
    if (isCustomSpeed) {
        isCustomSpeed = false;
        if (currentState != PLAYING) {
            lastUpdateTime = millis();
            setState(PLAYING);
        }
    }
}

void TinyFilmFestival::stop() {
    setState(IDLE);
}

void TinyFilmFestival::update() {
    updateFrame();
}

void TinyFilmFestival::displayFrame(const uint32_t frame[3]) {
    baseMatrix.loadFrame(frame);
    setState(PAUSED);
}

void TinyFilmFestival::updateFrame() {
    if (currentState != PLAYING || !isValidAnimation()) return;

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
                        setState(COMPLETED);
                    }
                }
            }
        } else {
            currentFrameIndex = (currentFrameIndex + 1) % frameCount;
            if (currentFrameIndex == 0 && currentMode == PLAY_ONCE) {
                setState(COMPLETED);
            }
        }

        lastUpdateTime = currentTime;
    }
}