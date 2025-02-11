// TinyFilmFestival.cpp
#include "TinyFilmFestival.h"

TinyFilmFestival::TinyFilmFestival() :
    isCustomSpeed(false),
    customSpeedInterval(0),
    originalTimings(nullptr),
    frameCount(0),
    currentFrameIndex(0),
    startFrameIndex(0),
    endFrameIndex(0),
    isBoomerang(false),
    isReversing(false),
    isPlayingBackward(false),
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

void TinyFilmFestival::clearDisplay() {
    const uint32_t blankFrame[3] = {0, 0, 0};
    baseMatrix.loadFrame(blankFrame);
}

bool TinyFilmFestival::shouldStartNewAnimation(const Animation& animation, PlayMode mode) const {
    if (!isValidAnimation() || currentState == IDLE) {
        return true;
    }
    
    if (currentAnimation != animation.getFrames() || currentMode != mode) {
        return true;
    }
    
    if (currentState == COMPLETED && mode != PLAY_ONCE) {
        return true;
    }
    
    return false;
}

void TinyFilmFestival::copyTimings(const uint32_t frames[][4], int numFrames) {
    if (originalTimings != nullptr) {
        delete[] originalTimings;
    }
    
    originalTimings = new uint32_t[numFrames];
    for (int i = 0; i < numFrames; i++) {
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
    
    switch (currentState) {
        case PLAYING:
            break;
        default:
            break;
    }
    
    currentState = newState;
    
    switch (currentState) {
        case IDLE:
            cleanup();
            clearDisplay();
            break;
            
        case PLAYING:
            if (!isValidAnimation()) {
                currentState = IDLE;
            }
            break;
            
        case COMPLETED:
            if (currentMode == PLAY_ONCE) {
                clearDisplay();
            } else if (isValidAnimation()) {
                setState(PLAYING);
            }
            break;
            
        case PAUSED:
            break;
    }
}

void TinyFilmFestival::setSpeed(int speedMs) {
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

bool TinyFilmFestival::getCurrentFrame(uint32_t frame[3]) {
    if (!isValidAnimation() || currentState != PLAYING) return false;
    
    frame[0] = currentAnimation[currentFrameIndex][0];
    frame[1] = currentAnimation[currentFrameIndex][1];
    frame[2] = currentAnimation[currentFrameIndex][2];
    return true;
}

void TinyFilmFestival::updateFrame() {
    if (currentState != PLAYING || !isValidAnimation()) return;

    unsigned long currentTime = millis();
    uint32_t interval = isCustomSpeed ? customSpeedInterval : originalTimings[currentFrameIndex];

    if (currentTime - lastUpdateTime >= interval) {
        if (!isBoomerang) {
            if (isPlayingBackward) {
                currentFrameIndex--;
                if (currentFrameIndex <= startFrameIndex) {
                    if (currentMode == PLAY_ONCE) {
                        setState(COMPLETED);
                        return;
                    } else {
                        currentFrameIndex = endFrameIndex;
                    }
                }
            } else {
                currentFrameIndex++;
                if (currentFrameIndex > endFrameIndex) {
                    if (currentMode == PLAY_ONCE) {
                        setState(COMPLETED);
                        return;
                    } else {
                        currentFrameIndex = startFrameIndex;
                    }
                }
            }
        } else {
            if (!isReversing) {
                currentFrameIndex = isPlayingBackward ? currentFrameIndex - 1 : currentFrameIndex + 1;
                if (currentFrameIndex >= endFrameIndex || currentFrameIndex <= startFrameIndex) {
                    isReversing = true;
                    currentFrameIndex = isPlayingBackward ? startFrameIndex : endFrameIndex;
                }
            } else {
                currentFrameIndex = isPlayingBackward ? currentFrameIndex + 1 : currentFrameIndex - 1;
                if (currentFrameIndex <= startFrameIndex || currentFrameIndex >= endFrameIndex) {
                    isReversing = false;
                    if (currentMode == PLAY_ONCE) {
                        setState(COMPLETED);
                        return;
                    } else {
                        currentFrameIndex = isPlayingBackward ? endFrameIndex : startFrameIndex;
                    }
                }
            }
        }

        lastUpdateTime = currentTime;
        
        // Display the current frame
        const uint32_t frame[3] = {
            currentAnimation[currentFrameIndex][0],
            currentAnimation[currentFrameIndex][1],
            currentAnimation[currentFrameIndex][2]
        };
        baseMatrix.loadFrame(frame);
    }
}