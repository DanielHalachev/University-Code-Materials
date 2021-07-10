//
// Created by User on 22.3.2021 г..
//

#include <cstring>
#include <utility>
#include "TestSuite.hpp"

TestSuite::TestSuite(std::string name) {
    this->name = std::move(name);
}

void TestSuite::add(const TestCase &testCase) {
    this->tests.push_back(testCase);
}

std::vector<TestCase> TestSuite::filterPassing() const {
    std::vector<TestCase> passingTests;
    for (const TestCase &test: this->tests) {
        if (test.isPassing()) {
            passingTests.push_back(test);
        }
    }
    return passingTests;
}

std::vector<TestCase> TestSuite::filterFailing() const {
    std::vector<TestCase> failingTests;
    for (const TestCase &test: this->tests) {
        if (!test.isPassing()) {
            failingTests.push_back(test);
        }
    }
    return failingTests;
}

std::vector<TestCase> TestSuite::filterByErrorType(ErrorType errorType) const {
    std::vector<TestCase> testsWithSameError;
    for (const TestCase &test: this->tests) {
        if (test.getErrorType() == errorType) {
            testsWithSameError.push_back(test);
        }
    }
    return testsWithSameError;
}

void TestSuite::removeByErrorType(ErrorType errorType) {
    //int i = 0;
//    for (const TestCase &test: this->tests) {
//        if (test.getErrorType() == errorType) {
//            this->tests.erase(this->tests.begin() + i);
//
//            continue;
//        }
//        i++;
//    }
    for (int i = 0; i < tests.size();) {
        if (tests[i].getErrorType() == errorType) {
            this->tests.erase(this->tests.begin() + i);
            continue;
        }
        i++;
    }
}

std::string TestSuite::getName() const {
    return this->name;
}

void TestSuite::setName(const std::string &newName) {
    this->name = newName;
}
