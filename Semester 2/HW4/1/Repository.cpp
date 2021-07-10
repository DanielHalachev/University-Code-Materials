
#include "Repository.hpp"

Repository::Repository(const Repository &other) {
    for (auto subscriber :other.subscribers) {
        this->subscribers.push_back(subscriber->clone());
    }
}

Repository &Repository::operator=(const Repository &other) {
    if (this != &other) {
        for (auto subscriber :this->subscribers) {
            delete subscriber;
        }
        this->subscribers.clear();
        for (auto subscriber :other.subscribers) {
            this->subscribers.push_back(subscriber->clone());
        }
    }
    return *this;
}

Repository::~Repository() {
    for (auto subscriber :this->subscribers) {
        delete subscriber;
    }
    this->subscribers.clear();
}

void Repository::add(Subscriber *subscriber) {
    if (subscriber != nullptr) {
        // add the subscriber
        this->subscribers.push_back(subscriber->clone());
    }
}

void Repository::remove(Subscriber *subscriber) {
    // cannot remove non-existent objects
    if (subscriber == nullptr) {
        return;
    }
    // search for match by ID
    for (unsigned int i = 0; i < this->subscribers.size(); i++) {
        if (subscribers[i]->id == subscriber->id) {
            delete this->subscribers[i];
            this->subscribers.erase(this->subscribers.begin() + i);
            break;
        }
    }
}

void Repository::signal(const Message &message) const {
    // send message to everyone
    for (auto subscriber:this->subscribers) {
        subscriber->signal(message);
    }
}

Subscriber *Repository::get(const std::string &id) {
    // search by ID
    for (auto subscriber:this->subscribers) {
        if (subscriber->id == id) {
            return subscriber;
        }
    }
    // return this if nothing found
    return nullptr;
}
