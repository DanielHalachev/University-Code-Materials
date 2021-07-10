
#include "MovingAverager.hpp"

MovingAverager::MovingAverager(const std::string &id, const size_t &windowSize)
        : Subscriber(id), windowSize(windowSize) {
}

void MovingAverager::signal(const Message &message) {
    // if the window_size has been reached, delete the oldest
    // message before adding the newest one
    if (this->messages.size() == this->windowSize) {
        this->messages.pop_front();
    }
    this->messages.push_back(message);
}

int MovingAverager::read() const {
    // cannot divide by zero
    if (this->messages.empty()) {
        return 0;
    }
    // calculate the average of all message data
    int average = 0;
    for (auto message : this->messages) {
        average += message.data;
    }
    return average / (int) this->messages.size();
}

MovingAverager *MovingAverager::clone() const {
    return new MovingAverager(*this);
}
