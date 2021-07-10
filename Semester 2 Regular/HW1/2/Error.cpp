//
// Created by User on 22.3.2021 г..
//
#include <cstring>
#include "Error.hpp"

Error::Error() {
    this->message = nullptr;
    this->errorType = ErrorType::None;
}

Error::Error(const Error &error) {
    if (error.hasMessage()) {
        strcpy(this->message, error.message);
        this->message = new char[strlen(error.message) + 1];
    } else {
        this->message = nullptr;
    }
    this->errorType = error.errorType;
}

Error::~Error() {
    delete[] this->message;
}

Error &Error::operator=(const Error &other) {
    if (this != &other) {
        delete[] this->message;
        if (other.hasMessage()) {
            this->message = new char[strlen(other.message) + 1];
            strcpy(this->message, other.message);
        } else {
            this->message = nullptr;
        }
        this->errorType = other.errorType;
    }
    return *this;
}

bool Error::hasMessage() const {
    return (this->message != nullptr);
}

const char *Error::getMessage() const {
    //returns message or nullptr
    return this->message;
}

ErrorType Error::getType() const {
    return this->errorType;
}

Error Error::newNone() {
    Error error;
    error.message = nullptr;
    error.errorType = ErrorType::None;
    return error;
}

Error Error::newBuildFailed(const char *message) {
    Error error;
    if (message == nullptr) {
        error.message = nullptr;
    } else {
        error.message = new char[strlen(message) + 1];
        strcpy(error.message, message);
    }
    error.errorType = ErrorType::BuildFailed;
    return error;
}

Error Error::newWarning(const char *message) {
    Error error;
    if (message == nullptr) {
        error.message = nullptr;
    } else {
        error.message = new char[strlen(message) + 1];
        strcpy(error.message, message);
    }
    error.errorType = ErrorType::Warning;
    return error;
}

Error Error::newFailedAssertion(const char *message) {
    Error error;
    if (message == nullptr) {
        error.message = nullptr;
    } else {
        error.message = new char[strlen(message) + 1];
        strcpy(error.message, message);
    }
    error.errorType = ErrorType::FailedAssertion;
    return error;
}
