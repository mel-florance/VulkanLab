#include <iostream>
#include <unistd.h>
#include <GLFW/glfw3.h>
#include "Loop.h"
#include "Engine.h"
#include "Clock.h"
#include "../Display/Window.h"

Loop::Loop(Engine* engine) :
    running(false),
    render(false),
    sleepTime(0),
    fps(0.0f),
    lastTime(0.0),
    startTime(0.0),
    frameTime(1.0 / 60.0f),
    frameCounter(0.0),
    unprocessedTime(0),
    frames(0),
    passedTime(0.0),
    fpsIndex(0),
    fpsSum(0.0f)
{
    this->engine = engine;
    this->clock = new Clock();
    this->profiler = new Profiler(this->clock);

    this->profiler->addTimer("frame");
    this->profiler->addTimer("update");
    this->profiler->addTimer("render");
    this->profiler->addTimer("sleep");

    this->updateCallback = nullptr;
    this->renderCallback = nullptr;
}

void Loop::start()
{
    if (this->running)
        return;

    this->running = true;
    this->lastTime = this->clock->getTime();
    this->frameCounter = 0;
    this->unprocessedTime = 0;
    this->frames = 0;

    while (this->running)
    {
        this->render = false;
        this->startTime = this->clock->getTime();

        this->passedTime = this->startTime - this->lastTime;
        this->lastTime = this->startTime;

        this->unprocessedTime += this->passedTime;
        this->frameCounter += this->passedTime;

        if (this->frameCounter >= 0.5f)
        {
            this->fps = computeAverageFps(1.0f / (float)this->passedTime);
            this->frames = 0;
            this->frameCounter = 0;
        }

        this->profiler->startTimer("frame");

        if (this->unprocessedTime > this->frameTime)
        {
            this->profiler->startTimer("update");

            if (this->updateCallback != nullptr)
                this->updateCallback(this, this->engine);

            this->profiler->stopTimer("update");

            this->render = true;
            this->unprocessedTime -= this->passedTime;
        }

        this->profiler->startTimer("render");

        if (this->renderCallback != nullptr)
            this->renderCallback(this, this->engine);

        this->profiler->stopTimer("render");

        this->frames++;

        this->profiler->startTimer("sleep");
        usleep(this->sleepTime);
        this->profiler->stopTimer("sleep");

        this->profiler->stopTimer("frame");
    }
}

float Loop::computeAverageFps(float fps)
{
    this->fpsSum -= this->fpsList[this->fpsIndex];
    this->fpsSum += fps;
    this->fpsList[this->fpsIndex] = fps;
    this->fpsIndex++;

    if (this->fpsIndex == MAX_SAMPLES)
        this->fpsIndex = 0;

    return this->fpsSum / MAX_SAMPLES;
}

void Loop::stop()
{
    this->running = false;
}

Loop::~Loop()
{
    delete this->clock;
    delete this->profiler;
}
