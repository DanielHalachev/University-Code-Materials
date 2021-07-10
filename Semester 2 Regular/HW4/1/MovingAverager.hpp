//
// Created by User on 24.5.2021 г..
//

#ifndef HW4_MOVINGAVERAGER_HPP
#define HW4_MOVINGAVERAGER_HPP

#include "Message.hpp"
#include "Subscriber.hpp"
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// MovingAverager is a type of Subscriber, which saves data
// and returns the average of the last `windowSize` number of
// data points when `read()` is called.
// Data is provided with the `signal()` method.
// Average of N numbers = sum(all numbers) / N
class MovingAverager : public Subscriber {
public:
    MovingAverager(const std::string &id, const size_t &windowSize);

    MovingAverager *clone() const override;

    // windowSize specifies how many most-recent data points
    // should be saved
    // Should never be changed once initialized
    const size_t windowSize;

    // signal adds a new data point
    // Remember, you only need the last windowSize number of
    // data points added, older data points should be ignored
    void signal(const Message &message) override;

    // read calculates the average of the last windowSize number
    // of data points
    // returns 0 if there's no data points
    int read() const override;
};

#endif //HW4_MOVINGAVERAGER_HPP
