

#ifndef EXERCISES_VECTOR_HPP
#define EXERCISES_VECTOR_HPP


#include "Vector.hpp"
#include <cstddef>
#include <stdexcept>


template<typename T>
class Vector;

template<typename T>
Vector<T> operator+(const Vector<T> &lhs, const Vector<T> &rhs);

template<typename T>
class Vector {
public:
    Vector();

    Vector(const Vector<T> &other);

    Vector &operator=(const Vector<T> &other);

    ~Vector();

    size_t getSize() const;

    void push_back(const T &object);

    bool insert(const unsigned int &index, const T &element);

    bool erase(const unsigned int &index);

    bool empty() const;

    void clear();

    const T &operator[](const unsigned int &index) const;

    T &operator[](const unsigned int &index);

    friend Vector<T> operator+<>(const Vector<T> &lhs, const Vector<T> &rhs);

    Vector operator+=(const Vector<T> &rhs);

    bool operator==(const Vector<T> &other);

    int find(const T &object) const;

private:
    T *array;
    size_t size;
};

template<typename T>
Vector<T>::Vector():size(0) {

}

template<typename T>
Vector<T>::Vector(const Vector<T> &other) {
    this->size = other.size;
    this->array = new T[this->size];
    for (int i = 0; i < other.size; i++) {
        this->array[i] = other.array[i];
    }
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other) {
        this->size = other.size;
        T *newArray = new T[this->size];
        for (int i = 0; i < other.size; i++) {
            this->array[i] = other.array[i];
        }
        delete[] this->array;
        this->array = newArray;
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] this->array;
}

template<typename T>
size_t Vector<T>::getSize() const {
    return this->size;
}

template<typename T>
void Vector<T>::push_back(const T &object) {
    T *newArray = new T[this->size + 1];
    for (int i = 0; i < this->size; i++) {
        newArray[i] = this->array[i];
    }
    newArray[this->size] = object;
    this->size++;
    delete[] this->array;
    this->array = newArray;
}

template<typename T>
bool Vector<T>::insert(const unsigned int &index, const T &element) {
    if (index >= this->size) {
        return false;
    }
    T *newArray = new T[this->size + 1];
    for (int i = 0; i < index; i++) {
        newArray[i] = this->array[i];
    }
    newArray[index] = element;
    for (int i = index + 1; i <= this->size; i++) {
        newArray[i] = this->array[i - 1];
    }
    this->size++;
    delete[] this->array;
    this->array = newArray;
    return true;
}

template<typename T>
bool Vector<T>::erase(const unsigned int &index) {
    if (index >= this->size) {
        return false;
    }
    T *newArray = new T[this->size - 1];
    for (int i = 0; i < index; i++) {
        newArray[i] = this->array[i];
    }
    for (int i = index; i < this->size - 1; i++) {
        newArray[i] = this->array[i + 1];
    }
    this->size--;
    delete[] this->array;
    this->array = newArray;
    return true;
}

template<typename T>
bool Vector<T>::empty() const {
    return (this->size == 0);
}

template<typename T>
void Vector<T>::clear() {
    delete[] this->array;
    this->size = 0;
}

template<typename T>
const T &Vector<T>::operator[](const unsigned int &index) const {
    if (index >= this->size) {
        throw std::out_of_range("Out of range");
    }
    return this->array[index];
}

template<typename T>
T &Vector<T>::operator[](const unsigned int &index) {
    if (index >= this->size) {
        throw std::out_of_range("Out of range");
    }
    return this->array[index];
}

template<typename T>
Vector<T> operator+(const Vector<T> &lhs, const Vector<T> &rhs) {
    size_t size1 = lhs.size;
    size_t size2 = rhs.size;
    T *newArray = new T[size1 + size2];
    for (int i = 0; i < size1; i++) {
        newArray[i] = lhs.array[i];
    }
    for (int i = 0; i < size2; i++) {
        newArray[size1 + i] = rhs.array[i];
    }
    Vector<T> vector;
    vector.array = newArray;
    return vector;
}

template<typename T>
Vector<T> Vector<T>::operator+=(const Vector<T> &rhs) {
    size_t size1 = this->size;
    size_t size2 = rhs.size;
    T *newArray = new T[size1 + size2];
    for (int i = 0; i < size1; i++) {
        newArray[i] = rhs.array[i];
    }
    for (int i = 0; i < size2; i++) {
        newArray[size1 + i] = rhs.array[i];
    }
    delete[] this->array;
    this->array = newArray;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &other) {
    if (this->size != other.size) {
        return false;
    }
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] != other.array[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
int Vector<T>::find(const T &object) const {
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == object) {
            return i;
        }
    }
    return -1;
}


#endif //EXERCISES_VECTOR_HPP
