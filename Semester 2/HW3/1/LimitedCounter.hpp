
#ifndef HW4_LIMITEDCOUNTER_HPP
#define HW4_LIMITEDCOUNTER_HPP


#include "Counter.hpp"

class LimitedCounter : public virtual Counter {
private:
    int maxValue;
    // int startingValue        from Counter.hpp
    // int currentValue         from Counter.hpp
    // unsigned int step        from Counter.hpp
public:
    LimitedCounter(const int &max, const int &initial = 0, const unsigned int &step = 1);

    void increment() override;

    int getMax() const;

    //getTotal() and getStep() from Counter.hpp
};


#endif //HW4_LIMITEDCOUNTER_HPP
