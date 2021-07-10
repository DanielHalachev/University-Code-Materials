

#include "TwowayCounter.hpp"

TwowayCounter::TwowayCounter() : Counter() {

}

TwowayCounter::TwowayCounter(const int &initial) : Counter(initial) {

}

TwowayCounter::TwowayCounter(const int &initial, const unsigned int &step) : Counter(initial, step) {

}

void TwowayCounter::decrement() {
    this->currentValue = this->currentValue - this->step;
}
