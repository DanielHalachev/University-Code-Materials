

#ifndef HW4_TWOWAYCOUNTER_HPP
#define HW4_TWOWAYCOUNTER_HPP


#include "Counter.hpp"

class TwowayCounter : public virtual Counter {
private:
    // int startingValue        from Counter.hpp
    // int currentValue         from Counter.hpp
    // unsigned int step        from Counter.hpp
public:
    TwowayCounter();

    TwowayCounter(const int &initial);

    TwowayCounter(const int &initial, const unsigned int &step);

    virtual void decrement();

    // getStep(), increment() and getTotal() from Counter.hpp
};


#endif //HW4_TWOWAYCOUNTER_HPP
