// TinyFilmFestival.h
#pragma once

#include "Arduino_LED_Matrix.h"

enum PlayMode {
    PLAY_ONCE,      // Play animation one time and stop
    PLAY_LOOP,      // Play animation forward repeatedly
    PLAY_BOOMERANG  // Play forward and backward repeatedly
};

// Make the enum values accessible as constants
static const PlayMode ONCE = PLAY_ONCE;
static const PlayMode LOOP = PLAY_LOOP;
static const PlayMode BOOMERANG = PLAY_BOOMERANG;

enum AnimationState {
    IDLE,       // Initial state or no animation loaded
    PLAYING,    // Animation is actively playing
    PAUSED,     // Animation is paused
    COMPLETED   // Animation has finished (for PLAY_ONCE mode)
};

class Animation {
private:
    const uint32_t (*frames)[4];
    size_t frameCount;

public:
    // Default constructor
    Animation() : frames(nullptr), frameCount(0) {}

    // Constructor from array
    template<size_t N>
    Animation(const uint32_t (&frameArray)[N][4]) : frames(frameArray), frameCount(N) {}

    // Assignment operator
    template<size_t N>
    Animation& operator=(const uint32_t (&frameArray)[N][4]) {
        frames = frameArray;
        frameCount = N;
        return *this;
    }

    const uint32_t (*getFrames() const)[4] { return frames; }
    size_t getFrameCount() const { return frameCount; }
};

class TinyFilmFestival {
private:
    ArduinoLEDMatrix baseMatrix;
    bool isCustomSpeed;
    uint32_t customSpeedInterval;
    uint32_t* originalTimings;
    uint32_t frameCount;
    uint32_t currentFrameIndex;
    bool isBoomerang;
    bool isReversing;
    const uint32_t (*currentAnimation)[4];
    unsigned long lastUpdateTime;
    PlayMode currentMode;
    AnimationState currentState;

    void cleanup();
    void copyTimings(const uint32_t frames[][4], uint32_t numFrames);
    void updateFrame();
    void setState(AnimationState newState);
    bool shouldStartNewAnimation(const Animation& animation, PlayMode mode) const;
    bool isValidAnimation() const { return currentAnimation != nullptr && frameCount > 0; }

public:
    TinyFilmFestival();
    ~TinyFilmFestival();

    bool begin();

    void startAnimation(const Animation& animation, PlayMode mode = PLAY_ONCE) {
        if (!shouldStartNewAnimation(animation, mode)) {
            return;
        }
        
        cleanup();
        currentMode = mode;
        isBoomerang = (mode == PLAY_BOOMERANG);
        frameCount = animation.getFrameCount();
        currentAnimation = animation.getFrames();
        copyTimings(currentAnimation, frameCount);
        currentFrameIndex = 0;
        isReversing = false;
        
        const uint32_t frame[3] = {
            currentAnimation[0][0],
            currentAnimation[0][1],
            currentAnimation[0][2]
        };
        baseMatrix.loadFrame(frame);
        
        lastUpdateTime = millis();
        setState(PLAYING);
    }

    // Maintain backwards compatibility
    template<size_t N>
    void startAnimation(const uint32_t (&frames)[N][4], PlayMode mode = PLAY_ONCE) {
        Animation anim(frames);
        startAnimation(anim, mode);
    }

    void setSpeed(uint32_t speedMs);
    void pause();
    void resume();
    void restoreOriginalSpeed();
    void update();
    void displayFrame(const uint32_t frame[3]);
    void stop();

    // Status methods
    bool isPaused() const { return currentState == PAUSED; }
    bool isComplete() const { return currentState == COMPLETED; }
    bool isPlaying() const { return currentState == PLAYING; }
    bool isIdle() const { return currentState == IDLE; }
    bool isCustomSpeedActive() const { return isCustomSpeed; }
    AnimationState getState() const { return currentState; }
    uint32_t getCurrentFrame() const { return currentFrameIndex; }
    uint32_t getCurrentSpeed() const { return isCustomSpeed ? customSpeedInterval : originalTimings[currentFrameIndex]; }
};