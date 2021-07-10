
#ifndef HW4_SEMAPHORE_HPP
#define HW4_SEMAPHORE_HPP


#include "LimitedTwowayCounter.hpp"

class Semaphore : private LimitedTwowayCounter {
private:
    // int minValue             from LimitedTwowayCounter
    // int maxValue             from LimitedCounter
    // int startingValue        from Counter.hpp
    // int currentValue         from Counter.hpp
    // unsigned int step        from Counter.hpp
public:
    Semaphore(const bool &startingValue = false);

    bool isAvailable() const;

    void wait();

    void signal();
};


#endif //HW4_SEMAPHORE_HPP
