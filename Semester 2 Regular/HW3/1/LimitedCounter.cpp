

#include "LimitedCounter.hpp"

LimitedCounter::LimitedCounter(const int &max, const int &initial, const unsigned int &step) : Counter(initial, step) {
    this->maxValue = max;
}

void LimitedCounter::increment() {
    this->currentValue = this->currentValue + step;
    if (this->currentValue > maxValue) {
        this->currentValue = this->currentValue - step;
    }
}

int LimitedCounter::getMax() const {
    return this->maxValue;
}
