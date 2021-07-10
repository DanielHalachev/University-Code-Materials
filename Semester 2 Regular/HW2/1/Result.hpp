#pragma once

#include "Error.hpp"
#include "Optional.hpp"

template<typename T>
class Result {
public:
    Result();

    Result(const T &result);

    Result(const std::string &error_message);

    ~Result();

    Optional<T> get_result() const;

    Optional<Error> get_error() const;

    bool operator==(const Error &other) const;

    bool operator==(const T &other) const;


private:
    T *object;
    std::string *errorMessage;
};

template<typename T>
Result<T>::Result() {
    this->object = nullptr;
    this->errorMessage = nullptr;

}

template<typename T>
Result<T>::Result(const T &result) {
    this->object = new T(result);
    this->errorMessage = nullptr;
}

template<typename T>
Result<T>::Result(const std::string &error_message) {
    this->object = nullptr;
    this->errorMessage = new std::string(error_message);
}

template<typename T>
Result<T>::~Result() {
    delete this->object;
    delete this->errorMessage;
}

template<typename T>
Optional<T> Result<T>::get_result() const {

    if (this->object == nullptr) {
        return Optional<T>();
    }
    return Optional<T>(*this->object);
}

template<typename T>
Optional<Error> Result<T>::get_error() const {
    if (errorMessage == nullptr) {
        return Optional<Error>();
    }
    return Optional<Error>(*this->errorMessage);
}

template<typename T>
bool Result<T>::operator==(const Error &other) const {
    if (this->errorMessage == nullptr) {
        return false;
    }
    return true;
}

template<typename T>
bool Result<T>::operator==(const T &other) const {
    if (this->errorMessage == nullptr) {
        return true;
    }
    return false;
}
