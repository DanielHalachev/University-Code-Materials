
#ifndef HW4_SUBSCRIBER_HPP
#define HW4_SUBSCRIBER_HPP

#include <string>
#include <vector>
#include <deque>
#include "Message.hpp"

class Subscriber {
public:
    Subscriber(const std::string &id = "");

    virtual ~Subscriber() = default;

    virtual Subscriber *clone() const = 0;

    //does different things in all inherited classes
    virtual void signal(const Message &message) = 0;

    //does different things in all inherited classes
    virtual int read() const = 0;

    // id is a unique identifier for a Subscriber
    // Should never be changed once initialized
    const std::string id;
protected:
    // contains all messages
    std::deque<Message> messages;
};

#endif //HW4_SUBSCRIBER_HPP
