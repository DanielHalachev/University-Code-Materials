//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_SET_HPP
#define EXERCISES_SET_HPP

#define ENLARGEMENT_SCALE 1.2

#include <cstddef>
#include <stdexcept>


template<class T>
class Set {
public:
    Set();

    Set(const Set<T> &other);

    Set<T> &operator=(const Set<T> &other);

    ~Set();

    bool insert(const T &object);

    bool erase(const T &object);

    bool contains(const T &object) const;

    size_t size() const;

    T operator[](const unsigned int &index) const;

    T &operator[](const unsigned int &index);

    Set<T> setUnion(const Set<T> &set2) const;

    Set<T> intersection(const Set<T> &set2) const;

private:
    T *array;
    size_t currentSize;
    size_t capacity;
};

template<class T>
Set<T>::Set() {
    this->array = new T[10];
    this->capacity = 10;
    this->currentSize = 0;
}

template<class T>
Set<T>::Set(const Set<T> &other) {
    this->currentSize = other.currentSize;
    this->capacity = other.capacity;
    this->array = new T[this->capacity];
    for (int i = 0; i < this->currentSize; i++) {
        this->array[i] = other.array[i];
    }
}

template<class T>
Set<T> &Set<T>::operator=(const Set<T> &other) {
    if (this != &other) {
        delete[] this->array;
        this->capacity = other.capacity;
        this->currentSize = other.currentSize;
        this->array = new T[other.capacity];
        for (int i = 0; i < this->currentSize; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}

template<class T>
Set<T>::~Set() {
    delete[] this->array;
}

template<class T>
bool Set<T>::insert(const T &object) {
    if (this->contains(object)) {
        return false;
    }
    if (this->currentSize == this->capacity) {
        unsigned int newSize = this->capacity * ENLARGEMENT_SCALE;
        T *newArray = new T[newSize];
        for (int i = 0; i < this->currentSize; i++) {
            newArray[i] = this->array[i];
        }
        delete[] this->array;
        this->array = newArray;
    }
    this->array[currentSize] = object;
    this->currentSize++;
    return true;
}

template<class T>
bool Set<T>::erase(const T &object) {
    for (int i = 0; i < this->currentSize; i++) {
        if (this->array[i] == object) {
            for (int j = i; j < this->currentSize - 1; j++) {
                this->array[j] = this->array[j + 1];
            }
            this->currentSize--;
            return true;
        }
    }
    return false;
}

template<class T>
bool Set<T>::contains(const T &object) const {
    for (int i = 0; i < this->currentSize; i++) {
        if (this->array[i] == object) {
            return true;
        }
    }
    return false;
}

template<class T>
size_t Set<T>::size() const {
    return this->currentSize;
}

template<class T>
T Set<T>::operator[](const unsigned int &index) const {
    if (index >= this->currentSize) {
        throw std::out_of_range("Requested element out of range");
    }
    return this->array[index];
}

template<class T>
T &Set<T>::operator[](const unsigned int &index) {
    if (index >= this->currentSize) {
        throw std::out_of_range("Requested element out of range");
    }
    return this->array[index];
}

template<class T>
Set<T> Set<T>::setUnion(const Set<T> &set2) const {
    Set<T> newSet;
    for (int i = 0; i < this->currentSize; i++) {
        newSet.insert(this->array[i]);
    }
    for (int i = 0; i < set2.currentSize; i++) {
        newSet.insert(set2.array[i]);
    }
    return newSet;
}

template<class T>
Set<T> Set<T>::intersection(const Set<T> &set2) const {
    Set<T> newSet;
    if (this->currentSize < set2.currentSize) {
        for (int i = 0; i < this->currentSize; i++) {
            if (set2.contains(this->array[i])) {
                newSet.insert(this->array[i]);
            }
        }
    } else {
        for (int i = 0; i < set2.currentSize; i++) {
            if (this->contains(set2.array[i])) {
                newSet.insert(set2.array[i]);
            }
        }
    }
    return newSet;
}


#endif //EXERCISES_SET_HPP
