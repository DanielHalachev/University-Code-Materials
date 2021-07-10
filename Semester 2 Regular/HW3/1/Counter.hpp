

#ifndef HW4_COUNTER_HPP
#define HW4_COUNTER_HPP


class Counter {
protected:
    int startingValue;
    unsigned int step;
    int currentValue;
public:

    Counter(const int &initial = 0, const unsigned int &step = 1);

    virtual void increment();

    int getTotal() const;

    unsigned int getStep() const;
};


#endif //HW4_COUNTER_HPP
