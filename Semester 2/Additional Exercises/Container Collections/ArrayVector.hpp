//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_ARRAYVECTOR_HPP
#define EXERCISES_ARRAYVECTOR_HPP


#define DEFAULT_CAPACITY 10

#include "Container.hpp"

template<class T>
class ArrayVector : public Container<T> {
public:
    ArrayVector();

    bool add(const T &object) override;

private:
    int capacity;
};

template<class T>
ArrayVector<T>::ArrayVector():Container<T>() {
    this->capacity = DEFAULT_CAPACITY;
}

template<class T>
bool ArrayVector<T>::add(const T &object) {
    if (this->currentSize == 10) {
        return false;
    }
    Container<T>::add(object);
}


#endif //EXERCISES_ARRAYVECTOR_HPP
