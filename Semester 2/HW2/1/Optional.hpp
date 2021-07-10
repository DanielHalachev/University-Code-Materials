#pragma once

// Add whatever else is required to exist in or out the class
// as well as whatever you think is good to be declared too
#include "Error.hpp"

template<typename T>

class Optional {
public:
    Optional();

    Optional(const T &value);

    ~Optional();

    bool is_none() const;

    T get_value() const;

private:
    T *content;
};

template<typename T>
Optional<T>::Optional() {
    this->content = nullptr;
}

template<typename T>
Optional<T>::Optional(const T &value) {
    this->content = new T(value);
}

template<typename T>
Optional<T>::~Optional() {
    delete this->content;
}

template<typename T>
bool Optional<T>::is_none() const {
    return this->content == nullptr;
}

template<typename T>
T Optional<T>::get_value() const {
    if (this->is_none()) {
        return T();
    }
    return *this->content;
}
