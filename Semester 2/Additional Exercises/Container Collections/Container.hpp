//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_CONTAINER_HPP
#define EXERCISES_CONTAINER_HPP

#include <stdexcept>

template<class T>
class Container {
public:
    Container();

    Container(const Container<T> &other);

    Container<T> &operator=(const Container<T> &other);

    ~Container();

    bool member(const T &object) const;

    virtual bool add(const T &object);

    bool remove(const T &object);

    int size() const;

    T &operator[](int i);

protected:
    T *array;
    int currentSize;
};

template<class T>
Container<T>::Container() {
    this->currentSize = 0;
    this->array = nullptr;
}

template<class T>
Container<T>::Container(const Container<T> &other) {
    this->currentSize = other.currentSize;
    this->array = new T[this->currentSize];
    for (int i = 0; i < this->currentSize; i++) {
        this->array[i] = other.array[i];
    }
}

template<class T>
Container<T> &Container<T>::operator=(const Container<T> &other) {
    if (this != &other) {
        this->currentSize = other.currentSize;
        delete[] this->array;
        this->array = new T[this->currentSize];
        for (int i = 0; i < this->currentSize; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}

template<class T>
Container<T>::~Container() {
    delete[] this->array;
}

template<class T>
bool Container<T>::member(const T &object) const {
    for (auto element :this->array) {
        if (element == object) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Container<T>::add(const T &object) {
    T *newArray = new T[this->currentSize + 1];
    for (int i = 0; i < this->currentSize; i++) {
        newArray[i] = this->array[i];
    }
    newArray[currentSize] = object;
    delete[] this->array;
    this->array = newArray;
    this->currentSize++;
    return true;
}

template<class T>
bool Container<T>::remove(const T &object) {
    T *newArray = new T[this->currentSize - 1];
    int index = -1;
    for (int i = 0; i < this->currentSize; i++) {
        if (this->array[i] == object) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return false;
    }
    for (int i = 0; i < index; i++) {
        newArray[i] = this->array[i];
    }
    for (int i = index; i < this->currentSize - 1; i++) {
        newArray[i] = this->array[i + 1];
    }
    delete[] this->array;
    this->array = newArray;
    this->currentSize--;
}

template<class T>
int Container<T>::size() const {
    return this->currentSize;
}

template<class T>
T &Container<T>::operator[](int i) {
    if (i > this->currentSize - 1 || i < 0) {
        throw std::out_of_range("Invalid index");
    }
    return this->array[i];
}


#endif //EXERCISES_CONTAINER_HPP
