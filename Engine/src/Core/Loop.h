#ifndef VULKANLAB_LOOP_H
#define VULKANLAB_LOOP_H

#pragma once

#include <map>
#include "Profiler.h"
#include "Clock.h"

#define MAX_SAMPLES 60

class Engine;

class Loop
{
public:
    /**
     * Loop constructor
     */
    Loop(Engine* engine);

    /**
     * Loop callback function definition
     */
    typedef void(*LoopCallback)(Loop* loop, Engine* engine);

    /**
     * Start the loop
     */
    void start();

    /**
     * Stop the loop
     */
    void stop();

    /**
     * Check if the loop is running.
     */
    inline bool isRunning() { return running; }

    /**
     * Return the loop profiler.
     * @return
     */
    inline Profiler* getProfiler() { return profiler; }

    /**
     * return the loop clock.
     * @return
     */
    inline Clock* getClock() { return clock; }

    /**
     * Set the update callback function.
     */
    inline void setUpdateCallback(LoopCallback callback) { updateCallback = callback; }

    /**
     * Set the render callback function.
     */
    inline void setRenderCallback(LoopCallback callback) { renderCallback = callback; }

    /**
     * Return the frame time.
     */
    inline double getFrameTime() { return frameTime; }

    /*
     * Return the elapsed time.
     */
    inline double getPassedTime() { return passedTime; }

    /**
     * Return the current image per second.
     */
    inline float getFps() { return fps; }

    /**
     * Compute an average of FPS during the interval fixed by MAX_SAMPLES.
     */
    float computeAverageFps(float fps);

    /**
     * Return the fps list of last frames.
     */
    inline std::map<int, float>& getFpsList() { return fpsList; }

    /**
     * Loop destructor
     */
    ~Loop();

    Clock* clock;
    Profiler* profiler;

private:
    Engine* engine;
    LoopCallback updateCallback;
    LoopCallback renderCallback;

    bool running;
    bool render;
    int sleepTime;
    float fps;
    double lastTime;
    double startTime;
    double frameTime;
    double frameCounter;
    double unprocessedTime = 0;
    int frames = 0;
    double passedTime;

    int fpsIndex;
    float fpsSum;
    std::map<int, float> fpsList;
};


#endif //VULKANLAB_LOOP_H
