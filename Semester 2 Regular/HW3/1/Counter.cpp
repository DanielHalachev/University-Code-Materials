
#include "Counter.hpp"

Counter::Counter(const int &initial, const unsigned int &step) {
    this->startingValue = initial;
    this->currentValue = startingValue;
    this->step = step;
}

void Counter::increment() {
    this->currentValue = this->currentValue + this->step;
}

int Counter::getTotal() const {
    return this->currentValue;
}

unsigned int Counter::getStep() const {
    return this->step;
}
