
#include "Semaphore.hpp"

Semaphore::Semaphore(const bool &startingValue) : LimitedTwowayCounter(0, 1, startingValue ? 1 : 0, 1) {}

bool Semaphore::isAvailable() const {
    return (this->currentValue > 0);
}

void Semaphore::wait() {
    this->decrement();
}

void Semaphore::signal() {
    this->increment();
}
