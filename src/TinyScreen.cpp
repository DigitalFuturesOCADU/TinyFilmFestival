// TinyScreen.cpp
// Implementation of the unified TinyScreen class
#include "TinyScreen.h"

//==============================================================================
// AnimationLayer Implementation
//==============================================================================

AnimationLayer::AnimationLayer() :
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

AnimationLayer::~AnimationLayer() {
    cleanup();
}

void AnimationLayer::cleanup() {
    if (originalTimings != nullptr) {
        delete[] originalTimings;
        originalTimings = nullptr;
    }
    currentAnimation = nullptr;
    frameCount = 0;
    currentState = IDLE;
}

void AnimationLayer::copyTimings(const uint32_t frames[][4], int numFrames) {
    if (originalTimings != nullptr) {
        delete[] originalTimings;
    }
    
    originalTimings = new uint32_t[numFrames];
    for (int i = 0; i < numFrames; i++) {
        originalTimings[i] = frames[i][3];
    }
}

void AnimationLayer::start(const Animation& animation, PlayMode mode, int startFrame, int endFrame) {
    cleanup();
    
    currentMode = mode;
    isBoomerang = (mode == PLAY_BOOMERANG);
    frameCount = animation.getFrameCount();
    currentAnimation = animation.getFrames();
    
    if (frameCount == 0 || currentAnimation == nullptr) {
        currentState = IDLE;
        return;
    }
    
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
    lastUpdateTime = millis();
    currentState = PLAYING;
}

void AnimationLayer::setSpeed(int speedMs) {
    if (!isValidAnimation()) return;
    
    if (speedMs == 0) {
        currentState = PAUSED;
    } else {
        isCustomSpeed = true;
        customSpeedInterval = speedMs;
        
        if (currentState != PLAYING) {
            lastUpdateTime = millis();
            currentState = PLAYING;
        }
    }
}

void AnimationLayer::pause() {
    if (currentState == PLAYING) {
        currentState = PAUSED;
    }
}

void AnimationLayer::resume() {
    if (currentState != PLAYING && isValidAnimation()) {
        lastUpdateTime = millis();
        currentState = PLAYING;
    }
}

void AnimationLayer::restoreOriginalSpeed() {
    if (!isValidAnimation()) return;
    
    if (isCustomSpeed) {
        isCustomSpeed = false;
        if (currentState != PLAYING) {
            lastUpdateTime = millis();
            currentState = PLAYING;
        }
    }
}

void AnimationLayer::stop() {
    cleanup();
}

int AnimationLayer::getCurrentSpeed() const {
    if (!isValidAnimation()) return 0;
    return isCustomSpeed ? customSpeedInterval : originalTimings[currentFrameIndex];
}

bool AnimationLayer::getFrame(uint32_t frame[3]) const {
    if (!isValidAnimation() || currentState == IDLE) return false;
    
    frame[0] = currentAnimation[currentFrameIndex][0];
    frame[1] = currentAnimation[currentFrameIndex][1];
    frame[2] = currentAnimation[currentFrameIndex][2];
    return true;
}

bool AnimationLayer::updateFrame() {
    if (currentState != PLAYING || !isValidAnimation()) return false;

    unsigned long currentTime = millis();
    uint32_t interval = isCustomSpeed ? customSpeedInterval : originalTimings[currentFrameIndex];

    if (currentTime - lastUpdateTime < interval) return false;

    // Advance frame
    if (!isBoomerang) {
        if (isPlayingBackward) {
            currentFrameIndex--;
            if (currentFrameIndex < startFrameIndex) {
                if (currentMode == PLAY_ONCE) {
                    currentState = COMPLETED;
                    return true;
                } else {
                    currentFrameIndex = endFrameIndex;
                }
            }
        } else {
            currentFrameIndex++;
            if (currentFrameIndex > endFrameIndex) {
                if (currentMode == PLAY_ONCE) {
                    currentState = COMPLETED;
                    return true;
                } else {
                    currentFrameIndex = startFrameIndex;
                }
            }
        }
    } else {
        // Boomerang mode
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
                    currentState = COMPLETED;
                    return true;
                } else {
                    currentFrameIndex = isPlayingBackward ? endFrameIndex : startFrameIndex;
                }
            }
        }
    }

    lastUpdateTime = currentTime;
    return true;
}

//==============================================================================
// TinyScreen Implementation
//==============================================================================

TinyScreen::TinyScreen() : layerCount(1), inOverlay(false) {
    combinedFrame[0] = 0;
    combinedFrame[1] = 0;
    combinedFrame[2] = 0;
}

bool TinyScreen::begin() {
    return matrix.begin();
}

//--- Animation Mode (simple) ---

void TinyScreen::play(const Animation& animation, PlayMode mode) {
    primary().start(animation, mode, 0, 0);
}

void TinyScreen::play(const Animation& animation, PlayMode mode, int startFrame, int endFrame) {
    primary().start(animation, mode, startFrame, endFrame);
}

void TinyScreen::startAnimation(const Animation& animation, PlayMode mode, int startFrame, int endFrame) {
    primary().start(animation, mode, startFrame, endFrame);
}

//--- Layered Animations ---

int TinyScreen::addLayer() {
    if (layerCount >= MAX_LAYERS) return -1;
    return layerCount++;
}

void TinyScreen::playOnLayer(int layer, const Animation& animation, PlayMode mode) {
    if (layer >= 0 && layer < layerCount) {
        layers[layer].start(animation, mode, 0, 0);
    }
}

void TinyScreen::playOnLayer(int layer, const Animation& animation, PlayMode mode, int startFrame, int endFrame) {
    if (layer >= 0 && layer < layerCount) {
        layers[layer].start(animation, mode, startFrame, endFrame);
    }
}

void TinyScreen::setSpeedOnLayer(int layer, int speedMs) {
    if (layer >= 0 && layer < layerCount) {
        layers[layer].setSpeed(speedMs);
    }
}

void TinyScreen::pauseLayer(int layer) {
    if (layer >= 0 && layer < layerCount) {
        layers[layer].pause();
    }
}

void TinyScreen::resumeLayer(int layer) {
    if (layer >= 0 && layer < layerCount) {
        layers[layer].resume();
    }
}

void TinyScreen::stopLayer(int layer) {
    if (layer >= 0 && layer < layerCount) {
        layers[layer].stop();
    }
}

//--- Primary Layer Control ---

void TinyScreen::setSpeed(int speedMs) {
    primary().setSpeed(speedMs);
}

void TinyScreen::pause() {
    primary().pause();
}

void TinyScreen::resume() {
    primary().resume();
}

void TinyScreen::restoreOriginalSpeed() {
    primary().restoreOriginalSpeed();
}

void TinyScreen::stop() {
    primary().stop();
}

//--- Frame Update ---

void TinyScreen::update() {
    // Clear combined frame
    combinedFrame[0] = 0;
    combinedFrame[1] = 0;
    combinedFrame[2] = 0;

    // Update each layer and combine frames
    uint32_t frame[3];
    for (int i = 0; i < layerCount; i++) {
        layers[i].updateFrame();
        if (layers[i].getFrame(frame)) {
            combinedFrame[0] |= frame[0];
            combinedFrame[1] |= frame[1];
            combinedFrame[2] |= frame[2];
        }
    }

    // Display combined frame
    matrix.loadFrame(combinedFrame);
}

//--- Canvas Mode ---

void TinyScreen::beginDraw() {
    matrix.beginDraw();
}

void TinyScreen::endDraw() {
    matrix.endDraw();
}

void TinyScreen::clear() {
    matrix.clear();
}

void TinyScreen::set(int x, int y, bool on) {
    // ArduinoLEDMatrix set() expects RGB values
    // For single-color matrix, use 1,1,1 for on, 0,0,0 for off
    uint8_t val = on ? 1 : 0;
    matrix.set(x, y, val, val, val);
}

void TinyScreen::point(int x, int y) {
    matrix.point(x, y);
}

void TinyScreen::line(int x1, int y1, int x2, int y2) {
    matrix.line(x1, y1, x2, y2);
}

void TinyScreen::rect(int x, int y, int width, int height) {
    matrix.rect(x, y, width, height);
}

void TinyScreen::circle(int cx, int cy, int diameter) {
    matrix.circle(cx, cy, diameter);
}

void TinyScreen::ellipse(int cx, int cy, int width, int height) {
    matrix.ellipse(cx, cy, width, height);
}

//--- Style Control ---

void TinyScreen::stroke(uint8_t r, uint8_t g, uint8_t b) {
    matrix.stroke(r, g, b);
}

void TinyScreen::stroke(uint32_t color) {
    matrix.stroke(color);
}

void TinyScreen::noStroke() {
    matrix.noStroke();
}

void TinyScreen::fill(uint8_t r, uint8_t g, uint8_t b) {
    matrix.fill(r, g, b);
}

void TinyScreen::fill(uint32_t color) {
    matrix.fill(color);
}

void TinyScreen::noFill() {
    matrix.noFill();
}

void TinyScreen::background(uint8_t r, uint8_t g, uint8_t b) {
    matrix.background(r, g, b);
}

void TinyScreen::background(uint32_t color) {
    matrix.background(color);
}

//--- Text Methods ---

void TinyScreen::text(const char* str, int x, int y) {
    matrix.text(str, x, y);
}

void TinyScreen::text(const String& str, int x, int y) {
    matrix.text(str, x, y);
}

void TinyScreen::textFont(const Font& font) {
    matrix.textFont(font);
}

int TinyScreen::textFontWidth() {
    return matrix.textFontWidth();
}

int TinyScreen::textFontHeight() {
    return matrix.textFontHeight();
}

//--- Scrolling Text ---

void TinyScreen::beginText(int x, int y) {
    matrix.beginText(x, y);
}

void TinyScreen::beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    matrix.beginText(x, y, r, g, b);
}

void TinyScreen::beginText(int x, int y, uint32_t color) {
    matrix.beginText(x, y, color);
}

void TinyScreen::endText(int scrollDirection) {
    matrix.endText(scrollDirection);
}

void TinyScreen::textScrollSpeed(unsigned long speed) {
    matrix.textScrollSpeed(speed);
}

//--- Print Interface ---

size_t TinyScreen::print(const char* str) {
    return matrix.print(str);
}

size_t TinyScreen::print(const String& str) {
    return matrix.print(str);
}

size_t TinyScreen::print(char c) {
    return matrix.print(c);
}

size_t TinyScreen::print(int n) {
    return matrix.print(n);
}

size_t TinyScreen::println() {
    return matrix.println();
}

size_t TinyScreen::println(const char* str) {
    return matrix.println(str);
}

size_t TinyScreen::println(const String& str) {
    return matrix.println(str);
}

//--- Hybrid Mode ---

void TinyScreen::beginOverlay() {
    inOverlay = true;
    // Update animations first
    combinedFrame[0] = 0;
    combinedFrame[1] = 0;
    combinedFrame[2] = 0;
    
    uint32_t frame[3];
    for (int i = 0; i < layerCount; i++) {
        layers[i].updateFrame();
        if (layers[i].getFrame(frame)) {
            combinedFrame[0] |= frame[0];
            combinedFrame[1] |= frame[1];
            combinedFrame[2] |= frame[2];
        }
    }
    
    // Load animation frame, then allow drawing on top
    matrix.loadFrame(combinedFrame);
    matrix.beginDraw();
}

void TinyScreen::endOverlay() {
    matrix.endDraw();
    inOverlay = false;
}

void TinyScreen::displayFrame(const uint32_t frame[3]) {
    matrix.loadFrame(frame);
}

//==============================================================================
// CombinedFilmFestival (Backward Compatibility)
//==============================================================================

bool CombinedFilmFestival::addFilm(TinyScreen& film) {
    // This is a simplified backward-compat layer
    // In the new model, layers are internal to TinyScreen
    // For legacy code, we just track that something was added
    if (count >= MAX_LAYERS) return false;
    count++;
    return true;
}
