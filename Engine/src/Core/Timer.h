#ifndef VULKANLAB_TIMER_H
#define VULKANLAB_TIMER_H

#include "Clock.h"

class Timer {
public:
    /**
     * Timer constructor
     * @param clock
     */
    Timer(Clock *clock) : clock(clock) {}

    /**
     * Start the timer
     */
    inline void start() {
        this->startTime = this->clock->getTime();
    }

    /**
     * Stop the timer
     */
    inline void stop() {
        this->calls++;
        this->totalTime += (this->clock->getTime() - this->startTime);
        this->startTime = 0;
    }

    /**
     * Get the timer report
     * @param divisor
     * @return
     */
    inline double report(double divisor) {
        divisor = (divisor == 0) ? this->calls : divisor;
        double result = (this->totalTime == 0 && divisor == 0.0)
                        ? 0.0
                        : (1000.0 * this->totalTime) / ((double) divisor);

        this->totalTime = 0.0;
        this->calls = 0;

        return result;
    }

private:
    int calls;
    Clock *clock;
    double startTime;
    double totalTime;
};

#endif //VULKANLAB_TIMER_H
