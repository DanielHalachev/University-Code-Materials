//
// Created by User on 22.3.2021 г..
//
#include "TestCase.hpp"

TestCase::TestCase(const std::string &name, const Error &error) {
    this->name = name;
    this->error = error;
}

TestCase::TestCase(const TestCase &testCase) {
    this->error = testCase.error;
    this->name = testCase.name;
}

std::string TestCase::getName() const {
    return this->name;
}

bool TestCase::isPassing() const {
    return (this->error.getType() == ErrorType::Warning || this->error.getType() == ErrorType::None);
}

bool TestCase::hasError() const {
    return (this->error.getType() != ErrorType::None);
}

ErrorType TestCase::getErrorType() const {
    return this->error.getType();
}

std::string TestCase::getErrorMessage() const {
    if (this->hasError()) {
        return this->error.getMessage();
    } else {
        return "";
    }
}
