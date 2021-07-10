//
// Daniel Halachev, #62547
// Clion, GCC//

#ifndef EXAM_NAMEDOBJECTARRAY_HPP
#define EXAM_NAMEDOBJECTARRAY_HPP

#include <stdexcept>
#include "NamedObject.hpp"

template<class T>
class NamedObjectArray {
public:
    NamedObjectArray();

    NamedObjectArray(const NamedObjectArray<T> &other);

    NamedObjectArray &operator=(const NamedObjectArray<T> &other);

    ~NamedObjectArray();

    unsigned int size() const;

    // this version only returns the object without permission tp change it
    const NamedObject<T> &operator[](const unsigned int &index) const;

    // this version allows the element to be changed
    NamedObject<T> &operator[](const unsigned int &index);

    void addObject(const NamedObject<T> &object);

    // no method to remove object required

private:
    NamedObject<T> *array;
    unsigned int count;

    void freeMemory();
};

template<class T>
NamedObjectArray<T>::NamedObjectArray():count(0) {
    this->array = nullptr;
}

template<class T>
NamedObjectArray<T>::NamedObjectArray(const NamedObjectArray<T> &other) {
    // copy the size
    this->count = other.count;
    // copy the data
    this->array = new NamedObject<T>[this->count];
    for (int i = 0; i < this->count; i++) {
        this->array[i] = other.array[i];
    }
}

template<class T>
NamedObjectArray<T> &NamedObjectArray<T>::operator=(const NamedObjectArray<T> &other) {
    // prevent self-assignment
    if (this != &other) {
        // clear the old data first to prevent memory leaks
        this->freeMemory();
        // assign the new data
        this->array = new NamedObject<T>[this->count];
        for (int i = 0; i < this->count; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}

template<class T>
NamedObjectArray<T>::~NamedObjectArray() {
    this->freeMemory();
}

template<class T>
unsigned int NamedObjectArray<T>::size() const {
    return this->count;
}

template<class T>
const NamedObject<T> &NamedObjectArray<T>::operator[](const unsigned int &index) const {
    // index is already unsigned
    // it can only be too big
    if (index > this->count - 1) {
        throw std::out_of_range("Invalid index");
    }
    return this->array[index];
}

template<class T>
NamedObject<T> &NamedObjectArray<T>::operator[](const unsigned int &index) {
    // index is already unsigned
    // it can only be too big
    if (index > this->count - 1) {
        throw std::out_of_range("Invalid index");
    }
    return this->array[index];
}

template<class T>
void NamedObjectArray<T>::addObject(const NamedObject<T> &object) {
    // create a new bigger array and copy all existing data from the old one
    auto newArray = new NamedObject<T>[this->count + 1];
    for (int i = 0; i < this->count; i++) {
        newArray[i] = this->array[i];
    }
    // now add the new object
    newArray[this->count] = object;
    // clear the old data
    this->freeMemory();
    // finally replace the old data with the new one
    this->array = newArray;
    // increase the count;
    this->count++;
}

template<class T>
void NamedObjectArray<T>::freeMemory() {
    delete[] this->array;
}


#endif //EXAM_NAMEDOBJECTARRAY_HPP
