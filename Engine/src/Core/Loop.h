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
    Loop(Engine* engine);

    typedef void(*LoopCallback)(Loop* loop, Engine* engine);

    void start();
    void stop();

    inline bool isRunning() { return running; }
    inline Profiler* getProfiler() { return profiler; }
    inline Clock* getClock() { return clock; }

    inline void setUpdateCallback(LoopCallback callback) { updateCallback = callback; }
    inline void setRenderCallback(LoopCallback callback) { renderCallback = callback; }

    inline double getFrameTime() { return frameTime; }
    inline double getPassedTime() { return passedTime; }
    inline float getFps() { return fps; }

    float computeAverageFps(float fps);
    inline std::map<int, float>& getFpsList() { return fpsList; }

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
