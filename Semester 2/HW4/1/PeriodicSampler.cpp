
#include "PeriodicSampler.hpp"

PeriodicSampler::PeriodicSampler(const std::string &id, const size_t &period) : Subscriber(id), period(period), n(0) {
}

void PeriodicSampler::signal(const Message &message) {
    // signal stores only the period-th messages
    // and discards all others
    n++;
    if ((n - 1) % this->period == 0) {
        this->messages.push_back(message);
    }
}

int PeriodicSampler::read() const {
    // cannot return non-existent data
    if (this->messages.empty()) {
        return 0;
    }
    // return latest message
    return this->messages.back().data;
}

PeriodicSampler *PeriodicSampler::clone() const {
    return new PeriodicSampler(*this);
}
