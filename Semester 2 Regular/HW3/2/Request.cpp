//
// Created by User on 3.5.2021 г..
//

#include "Request.hpp"

int Request::objectCount = 0;

Request::Request(const std::string &message, const std::string &sender) {
    this->message = message;
    this->sender = sender;
    // increase the counter
    objectCount++;
    // the ID is the same as the number of objects
    this->ID = objectCount;
}

std::string Request::getMessage() const {
    return this->message;
}

std::string Request::getSender() const {
    return this->sender;
}

int Request::getCount() {
    return objectCount;
}

int Request::getID() const {
    return this->ID;
}
