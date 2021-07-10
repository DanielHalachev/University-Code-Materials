//
// Created by User on 14.6.2021 г..
//

#ifndef EXERCISES_UNIQUEBOX_HPP
#define EXERCISES_UNIQUEBOX_HPP

#include <stdexcept>

template<class T>
class UniqueBox {
public:
    UniqueBox();

    UniqueBox(const UniqueBox<T> &other);

    UniqueBox &operator=(const UniqueBox<T> &other);

    ~UniqueBox();

    UniqueBox &operator+=(const T &object);

    const T &operator[](const unsigned int &index) const;

    T &operator[](const unsigned int &index);

    unsigned int size() const;

private:
    T *array;
    unsigned int count;
private:

};

template<class T>
UniqueBox<T>::UniqueBox() {
    this->count = 0;
    this->array = nullptr;
}

template<class T>
UniqueBox<T>::UniqueBox(const UniqueBox<T> &other) {
    this->count = other.count;
    this->array = new T[this->count];
    for (int i = 0; i < this->count; i++) {
        this->array[i] = other.array[i];
    }
}

template<class T>
UniqueBox<T> &UniqueBox<T>::operator=(const UniqueBox<T> &other) {
    if (this != &other) {
        this->count = other.count;
        delete[] this->array;
        this->array = new T[this->count];
        for (int i = 0; i < this->count; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}

template<class T>
UniqueBox<T>::~UniqueBox() {
    delete[] this->array;
}

template<class T>
UniqueBox<T> &UniqueBox<T>::operator+=(const T &object) {
    for (int i = 0; i < this->count; i++) {
        if (this->array[i] == object) {
            return *this;
        }
    }
    auto newArray = new T[this->count + 1];
    for (int i = 0; i < this->count; i++) {
        newArray[i] = this->array[i];
    }
    newArray[this->count] = object;
    this->count++;
    delete[] this->array;
    this->array = newArray;
}

template<class T>
const T &UniqueBox<T>::operator[](const unsigned int &index) const {
    if (index > this->count - 1) {
        throw std::out_of_range("Invalid index");
    }
    return this->array[index];
}

template<class T>
T &UniqueBox<T>::operator[](const unsigned int &index) {
    if (index > this->count - 1) {
        throw std::out_of_range("Invalid index");
    }
    return this->array[index];
}

template<class T>
unsigned int UniqueBox<T>::size() const {
    return this->count;
}


#endif //EXERCISES_UNIQUEBOX_HPP
