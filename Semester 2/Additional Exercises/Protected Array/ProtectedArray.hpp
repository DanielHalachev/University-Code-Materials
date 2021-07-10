//
// Created by User on 4.6.2021 г..
//

#ifndef EXERCISES_PROTECTEDARRAY_HPP
#define EXERCISES_PROTECTEDARRAY_HPP


#include "ProtectedValue.hpp"

template<class T>
class ProtectedArray {
public:
    ProtectedArray();

    ProtectedArray(const ProtectedArray<T> &other);

    ProtectedArray &operator=(const ProtectedArray<T> &other);

    ~ProtectedArray();

    T getElement(const unsigned int &index, const unsigned int &code) const;

    void addElement(const ProtectedValue<T> &object);

private:
    ProtectedValue<T> *array;
    unsigned int size;
};

template<class T>
ProtectedArray<T>::ProtectedArray() {
    this->array = nullptr;
    this->size = 0;
}

template<class T>
void ProtectedArray<T>::addElement(const ProtectedValue<T> &object) {
    T *newArray = new T[this->size + 1];
    for (int i = 0; i < this->size; i++) {
        newArray[i] = this->array[i];
    }
    newArray[size] = object;
    delete[] this->array;
    this->array = newArray;
    this->size++;
}

template<class T>
T ProtectedArray<T>::getElement(const unsigned int &index, const unsigned int &code) const {
    if (index > this->size - 1) {
        return T();
    }
    return this->array[index].getValue;
}

template<class T>
ProtectedArray<T>::ProtectedArray(const ProtectedArray<T> &other) {
    this->size = other.size;
    this->array = new T[this->size];
    for (int i = 0; i < this->size; i++) {
        this->array[i] = other.array[i];
    }
}

template<class T>
ProtectedArray<T> &ProtectedArray<T>::operator=(const ProtectedArray<T> &other) {
    if (this != other) {
        delete[] this->array;
        this->size = other.size;
        this->array = new T[this->size];
        for (int i = 0; i < this->size; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}

template<class T>
ProtectedArray<T>::~ProtectedArray() {
    delete[] this->array;
}


#endif //EXERCISES_PROTECTEDARRAY_HPP
