//
// Created by User on 24.5.2021 г..
//

#ifndef HW4_PERIODICSAMPLER_HPP
#define HW4_PERIODICSAMPLER_HPP

#include "Message.hpp"
#include "Subscriber.hpp"
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// PeriodicSampler is a type of Subscriber, which saves every
// period-th data point starting from the first data point provided.
// Data is provided with the `signal()` method.
//
// e.g if the period = 2, we save every 2nd data point provided
// so if we have
// signal(1), read(), signal(2), read(), signal(3), read(), signal(4), read()
// the output will be 1,1,3,3 as we skip every 2nd data point,
// which in our case is 2 and 4
class PeriodicSampler : public Subscriber {
public:
    PeriodicSampler(const std::string &id, const size_t &period);

    PeriodicSampler *clone() const override;

    // signal adds a new data point and saves only every period-th
    // data point, the data points in between are ignored
    void signal(const Message &message) override;

    // read returns the latest period-th data point if such exists
    // 0 otherwise
    int read() const override;

private:
    // stores the period
    size_t period;
    // stores the number of times data has been sent
    int n;
};

#endif //HW4_PERIODICSAMPLER_HPP
