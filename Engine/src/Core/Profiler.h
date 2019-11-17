#ifndef VULKANLAB_PROFILER_H
#define VULKANLAB_PROFILER_H

#include <unordered_map>
#include <string>
#include "Clock.h"
#include "Timer.h"

class Profiler {
public:
    /**
     * Profiler constructor
     * @param clock
     */
    Profiler(Clock *clock) : clock(clock) {
        this->clock = clock;
    }

    /**
     * Profiler destructor
     */
    ~Profiler() {
        for (const auto &timer : this->timers)
            delete timer.second;
    }

    /**
     * Get the registered timer given its name.
     * @param name
     * @return
     */
    inline Timer *getTimer(const std::string &name) {
        for (auto &timer : timers)
            if (timer.first == name)
                return timer.second;

        return nullptr;
    }

    /**
     * Add new timer for measuring.
     */
    inline void addTimer(const std::string &name) {
        this->timers[name] = new Timer(this->clock);
    }

    /**
     * Stop a previously added timer given its name.
     * @param name
     */
    inline void stopTimer(const std::string &name) {
        this->timers[name]->stop();
    }

    /**
     * Start a previously added timer given its name.
     * @param name
     */
    inline void startTimer(const std::string &name) {
        this->timers[name]->start();
    }

    /**
     * Return the report of a previously added timer, given its name.
     * @param name
     * @return
     */
    inline double getReport(const std::string &name) {
        return this->timers[name]->report(0);
    }

private:
    Clock *clock;
    std::unordered_map<std::string, Timer *> timers;
};

#endif //VULKANLAB_PROFILER_H
