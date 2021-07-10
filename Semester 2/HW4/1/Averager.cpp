
#include "Averager.hpp"

Averager::Averager(const std::string &id) : Subscriber(id) {
}

void Averager::signal(const Message &message) {
    // add the message to all other messages
    this->messages.push_back(message);
}

int Averager::read() const {
    // cannot divide by zero
    if (this->messages.empty()) {
        return 0;
    }
    // calculate average message data
    int average = 0;
    for (auto message :this->messages) {
        average += message.data;
    }
    return average / (int) this->messages.size();
}

Averager *Averager::clone() const {
    return new Averager(*this);
}
