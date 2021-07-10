
#ifndef HW4_PUBLISHER_HPP
#define HW4_PUBLISHER_HPP

#include "Averager.hpp"
#include "Message.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
#include "Repository.hpp"


class Publisher {
public:
    Publisher() = default;

    virtual ~Publisher() = default;

    // forbid copying of these functions to prevent mistakes
    // because of dynamic data usage
    Publisher(const Publisher &other) = delete;

    Publisher &operator=(const Publisher &other) = delete;

    // subscribe registers a Subscriber to start receiving messages
    virtual void subscribe(Subscriber *subscriber) = 0;

    // unsubscribe removes a Subscriber from the Publisher
    // Subscribers are removed based on their `id`
    // id-s will always be unique
    void unsubscribe(Subscriber *subscriber);

    // signal receives a message from an external source
    // and replays that message to all the current subscribers
    void signal(const Message &message);

protected:
    // holds all subscribers
    std::vector<Subscriber *> subscribers;
    // holds all messages sent by now
    std::deque<Message> sentMessages;
};


#endif //HW4_PUBLISHER_HPP
