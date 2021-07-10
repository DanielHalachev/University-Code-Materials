
#include "Publisher.hpp"

void Publisher::signal(const Message &message) {
    // send the message to all
    for (auto subscriber:this->subscribers) {
        subscriber->signal(message);
    }
    // store the message in order to be sent to all new subscribers
    this->sentMessages.push_back(message);
}

void Publisher::unsubscribe(Subscriber *subscriber) {
    // search by ID
    for (unsigned int i = 0; i < this->subscribers.size(); i++) {
        if (this->subscribers[i]->id == subscriber->id) {
            this->subscribers.erase(this->subscribers.begin() + i);
        }
    }
}
