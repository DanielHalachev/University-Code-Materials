//
// Created by User on 24.5.2021 г..
//

#ifndef HW4_SIMPLEPUBLISHER_HPP
#define HW4_SIMPLEPUBLISHER_HPP

#pragma once

#include "Averager.hpp"
#include "Message.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
#include "Publisher.hpp"

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// SimplePublisher is a Publisher, which can have one
// or more subscribers and upon receiving a message
// via `signal()`, it replays that message to all the
// subscribers
class SimplePublisher : public Publisher {
public:
    SimplePublisher() = default;

    // forbid these methods in order to prevent mistakes
    SimplePublisher(const SimplePublisher &other) = delete;

    SimplePublisher &operator=(const SimplePublisher &other) = delete;

    // subscribe registers a Subscriber to start receiving messages
    void subscribe(Subscriber *subscriber) override;

    // void unsubscribe(Subscriber *subscriber);        from Publisher.hpp
    // void signal(const Message &message) const;       from Publisher.hpp
};

#endif //HW4_SIMPLEPUBLISHER_HPP
