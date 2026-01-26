// TinyScreen.h
// Unified wrapper for Arduino R4 WiFi LED Matrix
// Combines Animation Mode + Canvas Mode in one simple interface
#pragma once

// ArduinoGraphics MUST be included before Arduino_LED_Matrix
// for drawing methods to work properly
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#define MAX_LAYERS 5  // Maximum animation layers

// Forward declarations
class Animation;
class AnimationLayer;

//------------------------------------------------------------------------------
// PlayMode - How animations play back
//------------------------------------------------------------------------------
enum PlayMode {
    PLAY_ONCE,
    PLAY_LOOP,
    PLAY_BOOMERANG
};

// Shorthand aliases
static const PlayMode ONCE = PLAY_ONCE;
static const PlayMode LOOP = PLAY_LOOP;
static const PlayMode BOOMERANG = PLAY_BOOMERANG;

//------------------------------------------------------------------------------
// AnimationState - Current state of an animation
//------------------------------------------------------------------------------
enum AnimationState {
    IDLE,
    PLAYING,
    PAUSED,
    COMPLETED
};

//------------------------------------------------------------------------------
// Animation - Wrapper for LED Matrix Editor frame data
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// AnimationLayer - Internal class for managing one animation track
//------------------------------------------------------------------------------
class AnimationLayer {
private:
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
    bool isValidAnimation() const { return currentAnimation != nullptr && frameCount > 0; }

public:
    AnimationLayer();
    ~AnimationLayer();

    void start(const Animation& animation, PlayMode mode, int startFrame, int endFrame);
    void setSpeed(int speedMs);
    void pause();
    void resume();
    void restoreOriginalSpeed();
    void stop();
    bool updateFrame();  // Returns true if frame updated
    bool getFrame(uint32_t frame[3]) const;  // Get current frame data

    // Status
    bool isPaused() const { return currentState == PAUSED; }
    bool isComplete() const { return currentState == COMPLETED; }
    bool isPlaying() const { return currentState == PLAYING; }
    bool isIdle() const { return currentState == IDLE; }
    bool isCustomSpeedActive() const { return isCustomSpeed; }
    bool isPlayingBackwards() const { return isPlayingBackward; }
    
    AnimationState getState() const { return currentState; }
    int getTotalFrames() const { return frameCount; }
    int getCurrentFrameNum() const { return currentFrameIndex + 1; }
    int getCurrentSpeed() const;
    int getStartFrame() const { return startFrameIndex + 1; }
    int getEndFrame() const { return endFrameIndex + 1; }
};

//------------------------------------------------------------------------------
// TinyScreen - The main unified class
//------------------------------------------------------------------------------
class TinyScreen {
private:
    ArduinoLEDMatrix matrix;
    AnimationLayer layers[MAX_LAYERS];
    uint8_t layerCount;
    uint32_t combinedFrame[3];
    bool inOverlay;
    
    // For backward compatibility - primary layer access
    AnimationLayer& primary() { return layers[0]; }
    const AnimationLayer& primary() const { return layers[0]; }

public:
    TinyScreen();
    
    //--- Initialization ---
    bool begin();
    
    //--- Animation Mode (simple single animation) ---
    void play(const Animation& animation, PlayMode mode = LOOP);
    void play(const Animation& animation, PlayMode mode, int startFrame, int endFrame);
    
    // Full API alias (backward compatible)
    void startAnimation(const Animation& animation, PlayMode mode = PLAY_ONCE, int startFrame = 0, int endFrame = 0);
    
    template<size_t N>
    void startAnimation(const uint32_t (&frames)[N][4], PlayMode mode = PLAY_ONCE, int startFrame = 0, int endFrame = 0) {
        Animation anim(frames);
        startAnimation(anim, mode, startFrame, endFrame);
    }
    
    //--- Layered Animations ---
    int addLayer();  // Returns layer index, or -1 if full
    void playOnLayer(int layer, const Animation& animation, PlayMode mode = LOOP);
    void playOnLayer(int layer, const Animation& animation, PlayMode mode, int startFrame, int endFrame);
    void setSpeedOnLayer(int layer, int speedMs);
    void pauseLayer(int layer);
    void resumeLayer(int layer);
    void stopLayer(int layer);
    
    //--- Playback Control (affects primary layer) ---
    void setSpeed(int speedMs);
    void pause();
    void resume();
    void restoreOriginalSpeed();
    void stop();
    
    //--- Frame Update (call in loop!) ---
    void update();
    
    //--- Canvas Mode (direct drawing) ---
    void beginDraw();
    void endDraw();
    void clear();
    
    // Drawing primitives
    void set(int x, int y, bool on);      // Single pixel
    void point(int x, int y);              // Pixel on (alias)
    void line(int x1, int y1, int x2, int y2);
    void rect(int x, int y, int width, int height);
    void circle(int cx, int cy, int diameter);
    void ellipse(int cx, int cy, int width, int height);
    
    // Style control
    void stroke(uint8_t r, uint8_t g, uint8_t b);
    void stroke(uint32_t color);
    void noStroke();
    void fill(uint8_t r, uint8_t g, uint8_t b);
    void fill(uint32_t color);
    void noFill();
    void background(uint8_t r, uint8_t g, uint8_t b);
    void background(uint32_t color);
    
    // Text methods
    void text(const char* str, int x, int y);
    void text(const String& str, int x, int y);
    void textFont(const Font& font);
    int textFontWidth();
    int textFontHeight();
    
    // Scrolling text
    void beginText(int x = 0, int y = 0);
    void beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void beginText(int x, int y, uint32_t color);
    void endText(int scrollDirection = NO_SCROLL);
    void textScrollSpeed(unsigned long speed);
    
    // Print interface (works after beginText)
    size_t print(const char* str);
    size_t print(const String& str);
    size_t print(char c);
    size_t print(int n);
    size_t println();
    size_t println(const char* str);
    size_t println(const String& str);
    
    // Matrix info
    int width() { return matrix.width(); }
    int height() { return matrix.height(); }
    
    //--- Hybrid Mode (draw over animation) ---
    void beginOverlay();
    void endOverlay();
    
    //--- Status (primary layer) ---
    bool isPaused() const { return primary().isPaused(); }
    bool isComplete() const { return primary().isComplete(); }
    bool isPlaying() const { return primary().isPlaying(); }
    bool isIdle() const { return primary().isIdle(); }
    bool isCustomSpeedActive() const { return primary().isCustomSpeedActive(); }
    bool isPlayingBackwards() const { return primary().isPlayingBackwards(); }
    
    AnimationState getState() const { return primary().getState(); }
    int getTotalFrames() const { return primary().getTotalFrames(); }
    int getCurrentFrame() const { return primary().getCurrentFrameNum(); }
    int getCurrentSpeed() const { return primary().getCurrentSpeed(); }
    int getStartFrame() const { return primary().getStartFrame(); }
    int getEndFrame() const { return primary().getEndFrame(); }
    
    //--- Direct matrix access (advanced) ---
    ArduinoLEDMatrix& getMatrix() { return matrix; }
    void displayFrame(const uint32_t frame[3]);
};

//------------------------------------------------------------------------------
// Backward Compatibility Aliases
//------------------------------------------------------------------------------

// TinyFilmFestival now maps to TinyScreen
using TinyFilmFestival = TinyScreen;

// CombinedFilmFestival is deprecated but still works
class CombinedFilmFestival {
private:
    TinyScreen screen;
    int layerIndices[MAX_LAYERS];
    int count;
    
public:
    CombinedFilmFestival() : count(0) {}
    
    bool begin() { return screen.begin(); }
    
    bool addFilm(TinyScreen& film);  // Note: now takes TinyScreen
    
    void update() { screen.update(); }
};
