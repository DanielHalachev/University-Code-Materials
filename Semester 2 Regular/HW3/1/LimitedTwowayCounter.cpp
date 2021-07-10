
#include "LimitedTwowayCounter.hpp"

LimitedTwowayCounter::LimitedTwowayCounter(const int &min, const int &max, const int &initial,
                                           const unsigned int &step) : Counter(initial, step),
                                                                       LimitedCounter(max, initial, step),
                                                                       TwowayCounter(initial, step) {
    this->minValue = min;
}

void LimitedTwowayCounter::decrement() {
    this->currentValue = this->currentValue - this->step;
    if (this->currentValue < minValue) {
        this->currentValue = this->currentValue + step;
    }
}

int LimitedTwowayCounter::getMin() const {
    return this->minValue;
}
