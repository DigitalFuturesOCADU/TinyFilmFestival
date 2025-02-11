// TinyFilmFestival.h
#pragma once

#include "Arduino_LED_Matrix.h"

#define MAX_FILMS 5  // Maximum number of films that can be combined

enum PlayMode {
    PLAY_ONCE,
    PLAY_LOOP,
    PLAY_BOOMERANG
};

static const PlayMode ONCE = PLAY_ONCE;
static const PlayMode LOOP = PLAY_LOOP;
static const PlayMode BOOMERANG = PLAY_BOOMERANG;

enum AnimationState {
    IDLE,
    PLAYING,
    PAUSED,
    COMPLETED
};

class Animation {
private:
    const uint32_t (*frames)[4];
    int frameCount;

public:
    Animation() : frames(nullptr), frameCount(0) {}
    
    template<size_t N>
    Animation(const uint32_t (&frameArray)[N][4]) : frames(frameArray), frameCount(N) {}
    
    template<size_t N>
    Animation& operator=(const uint32_t (&frameArray)[N][4]) {
        frames = frameArray;
        frameCount = N;
        return *this;
    }

    const uint32_t (*getFrames() const)[4] { return frames; }
    int getFrameCount() const { return frameCount; }
};

class TinyFilmFestival {
private:
    ArduinoLEDMatrix baseMatrix;
    bool isCustomSpeed;
    int customSpeedInterval;
    uint32_t* originalTimings;
    int frameCount;
    int currentFrameIndex;
    int startFrameIndex;
    int endFrameIndex;
    bool isBoomerang;
    bool isReversing;
    bool isPlayingBackward;
    const uint32_t (*currentAnimation)[4];
    unsigned long lastUpdateTime;
    PlayMode currentMode;
    AnimationState currentState;

    void cleanup();
    void copyTimings(const uint32_t frames[][4], int numFrames);
    void setState(AnimationState newState);
    bool shouldStartNewAnimation(const Animation& animation, PlayMode mode) const;
    bool isValidAnimation() const { return currentAnimation != nullptr && frameCount > 0; }
    bool isValidFrame(int frame) const { return frame <= frameCount && frame > 0; }
    void clearDisplay();  // Added clearDisplay declaration

protected:
    void updateFrame();
    bool getCurrentFrame(uint32_t frame[3]);

public:
    TinyFilmFestival();
    ~TinyFilmFestival();

    bool begin();

    void startAnimation(const Animation& animation, PlayMode mode = PLAY_ONCE, int startFrame = 0, int endFrame = 0) {
        if (!shouldStartNewAnimation(animation, mode)) {
            return;
        }
        
        cleanup();
        currentMode = mode;
        isBoomerang = (mode == PLAY_BOOMERANG);
        frameCount = animation.getFrameCount();
        currentAnimation = animation.getFrames();
        copyTimings(currentAnimation, frameCount);
        
        // Convert 1-based input to 0-based internal indices
        if (startFrame == 0 && endFrame == 0) {
            startFrameIndex = 0;
            endFrameIndex = frameCount - 1;
        } else {
            startFrameIndex = max(1, min(startFrame, frameCount)) - 1;
            endFrameIndex = endFrame == 0 ? frameCount - 1 : max(1, min(endFrame, frameCount)) - 1;
        }
        
        isPlayingBackward = startFrameIndex > endFrameIndex;
        if (isPlayingBackward) {
            int temp = endFrameIndex;
            endFrameIndex = startFrameIndex;
            startFrameIndex = temp;
        }
        
        currentFrameIndex = isPlayingBackward ? endFrameIndex : startFrameIndex;
        isReversing = false;
        
        const uint32_t frame[3] = {
            currentAnimation[currentFrameIndex][0],
            currentAnimation[currentFrameIndex][1],
            currentAnimation[currentFrameIndex][2]
        };
        baseMatrix.loadFrame(frame);
        
        lastUpdateTime = millis();
        setState(PLAYING);
    }

    template<size_t N>
    void startAnimation(const uint32_t (&frames)[N][4], PlayMode mode = PLAY_ONCE, int startFrame = 0, int endFrame = 0) {
        Animation anim(frames);
        startAnimation(anim, mode, startFrame, endFrame);
    }

    void setSpeed(int speedMs);
    void pause();
    void resume();
    void restoreOriginalSpeed();
    void update();
    void displayFrame(const uint32_t frame[3]);
    void stop();

    bool isPaused() const { return currentState == PAUSED; }
    bool isComplete() const { return currentState == COMPLETED; }
    bool isPlaying() const { return currentState == PLAYING; }
    bool isIdle() const { return currentState == IDLE; }
    bool isCustomSpeedActive() const { return isCustomSpeed; }
    bool isPlayingBackwards() const { return isPlayingBackward; }
    
    AnimationState getState() const { return currentState; }
    int getTotalFrames() const { return frameCount; }
    int getCurrentFrame() const { return currentFrameIndex + 1; } // Convert to 1-based for external use
    int getCurrentSpeed() const { return isCustomSpeed ? customSpeedInterval : originalTimings[currentFrameIndex]; }
    int getStartFrame() const { return startFrameIndex + 1; } // Convert to 1-based for external use
    int getEndFrame() const { return endFrameIndex + 1; } // Convert to 1-based for external use

    friend class CombinedFilmFestival;
};

class CombinedFilmFestival {
    private:
        ArduinoLEDMatrix baseMatrix;
        TinyFilmFestival* films[MAX_FILMS];  // Array of pointers
        uint8_t filmCount;
        uint32_t combinedFrame[3];
    
    public:
        CombinedFilmFestival() : filmCount(0) {
            combinedFrame[0] = 0;
            combinedFrame[1] = 0;
            combinedFrame[2] = 0;
            for(int i = 0; i < MAX_FILMS; i++) {
                films[i] = nullptr;
            }
        }
    
        bool begin() {
            return baseMatrix.begin();
        }
    
        bool addFilm(TinyFilmFestival& film) {  // Keep reference parameter for ease of use
            if (filmCount >= MAX_FILMS) return false;
            films[filmCount] = &film;  // Store pointer
            filmCount++;
            return true;
        }
    
        void update() {
            // Clear combined frame
            combinedFrame[0] = 0;
            combinedFrame[1] = 0;
            combinedFrame[2] = 0;
    
            // Update each film and combine frames
            uint32_t frame[3];
            for (int i = 0; i < filmCount; i++) {
                if (films[i] != nullptr) {
                    films[i]->updateFrame();
                    if (films[i]->getCurrentFrame(frame)) {
                        // OR the frames together
                        combinedFrame[0] |= frame[0];
                        combinedFrame[1] |= frame[1];
                        combinedFrame[2] |= frame[2];
                    }
                }
            }
    
            // Display final combined frame
            baseMatrix.loadFrame(combinedFrame);
        }
};