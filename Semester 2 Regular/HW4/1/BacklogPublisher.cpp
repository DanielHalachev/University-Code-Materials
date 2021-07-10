
#include "BacklogPublisher.hpp"

void BacklogPublisher::subscribe(Subscriber *subscriber) {
    // add subscriber
    this->subscribers.push_back(subscriber);
    // send all missed messages
    for (auto message :this->sentMessages) {
        subscriber->signal(message);
    }
}
