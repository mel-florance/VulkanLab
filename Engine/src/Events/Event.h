#ifndef VULKANLAB_EVENT_H
#define VULKANLAB_EVENT_H

#include <functional>
#include <unordered_map>

template<typename... Args>
class Event {
public:
    /**
     * Event constructor
     */
    Event() : currentId(0) {}

    /**
     * Event copy constructor
     * @param other
     */
    Event(const Event &other) : currentId(0) {
    }

    /*
     * Event destructor
     */
    ~Event() {}

    /**
     * Connect a function to the event.
     * @tparam T
     * @param instance
     * @param func
     * @return int - Connect function response
     */
    template<typename T>
    int attach(T *instance, void (T::*func)(Args...)) {
        return this->connect([=](Args... args) {
            (instance->*func)(args...);
        });
    }

    /**
     * Connect a std::function to the event.
     * @param std::function - slot
     * @return int - currentId
     */
    int connect(std::function<void(Args...)> const &slot) {
        this->slots.insert(std::make_pair(++this->currentId, slot));
        return this->currentId;
    }

    /**
     * Disconnect a previously connected function
     * @param id
     */
    void disconnect(int id) const {
        this->slots.erase(id);
    }

    /**
     * Call all the connected functions
     * @param p
     */
    void emit(Args... p) {
        for (auto const &it : this->slots) {
            it.second(std::forward<Args>(p)...);
        }
    }

    /**
     * Assignment operator, creates a new signal.
     * @param other
     * @return
     */
    Event &operator=(Event const &other) {
        this->disconnectAll();
    }

    /**
     * Disconnect all the previously connected functions.
     */
    void disconnectAll() const {
        this->slots.clear();
    }

    /**
     * Return the current event id.
     * @return
     */
    int getCurrentId() const {
        return this->currentId;
    }

    /**
     * Set the current event id.
     * @param currentId
     */
    void setCurrentId(int currentId) {
        this->currentId = currentId;
    }

private:
    int currentId;
    std::unordered_map<int, std::function<void(Args...)>> slots;
};

#endif //VULKANLAB_EVENT_H
