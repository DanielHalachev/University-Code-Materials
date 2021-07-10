
#include "SimplePublisher.hpp"

void SimplePublisher::subscribe(Subscriber *subscriber) {
    this->subscribers.push_back(subscriber);
}
