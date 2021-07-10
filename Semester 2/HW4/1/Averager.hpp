
#ifndef HW4_AVERAGER_HPP
#define HW4_AVERAGER_HPP


#include "Message.hpp"
#include "Subscriber.hpp"
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// Averager is a type of Subscriber, which saves data and
// returns the average of the data when `read()` is called.
// Data is provided with the `signal()` method.
// Average of N numbers = sum(all numbers) / N
class Averager : public Subscriber {
public:
    Averager(const std::string &id);

    Averager *clone() const override;

    // signal adds a new data point
    void signal(const Message &message) override;

    // read calculates the average of all data points provided so far
    // returns 0 if there's no data points
    int read() const override;
};


#endif //HW4_AVERAGER_HPP
