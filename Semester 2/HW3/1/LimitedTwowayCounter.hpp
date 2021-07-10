

#ifndef HW4_LIMITEDTWOWAYCOUNTER_HPP
#define HW4_LIMITEDTWOWAYCOUNTER_HPP


#include "LimitedCounter.hpp"
#include "TwowayCounter.hpp"

class LimitedTwowayCounter : public LimitedCounter, public TwowayCounter {
private:
    int minValue;
    // int maxValue             from LimitedCounter
    // int startingValue        from Counter.hpp
    // int currentValue         from Counter.hpp
    // unsigned int step        from Counter.hpp
public:
    LimitedTwowayCounter(const int &min, const int &max, const int &initial = 0, const unsigned int &step = 1);

    void decrement() override;

    int getMin() const;

    // getTotal() and getStep() from Counter.hpp
    // void decrement();        from TwowayCounter.hpp
    // void getMax()            from LimitedCounter.hpp


};


#endif //HW4_LIMITEDTWOWAYCOUNTER_HPP
