//
// Daniel Halachev, #62547
// Clion, GCC
//

#ifndef EXAM_NAMEDOBJECT_HPP
#define EXAM_NAMEDOBJECT_HPP

#include <cstring>

template<class T>
class NamedObject {
public:
    explicit NamedObject(const char *name = "", const unsigned int &id = 0, const T &object = T());

    NamedObject(const NamedObject<T> &other);

    NamedObject &operator=(const NamedObject<T> &other);

    ~NamedObject();

    const char *getName() const;

    T &getObject() const;

    unsigned int getID() const;


private:
    unsigned int id;
    char *name;
    T object;

    void assignName(const char *newName);

    void freeMemory();
};

template<class T>
NamedObject<T>::NamedObject(const char *name, const unsigned int &id = 0, const T &object)
        :object(object), id(id) {
    this->assignName(name);
}

template<class T>
NamedObject<T>::NamedObject(const NamedObject<T> &other) {
    this->object = other.object;
    this->id = other.id;
    this->assignName(other.name);
}

template<class T>
NamedObject<T> &NamedObject<T>::operator=(const NamedObject<T> &other) {
    if (this != &other) {
        this->freeMemory();
        this->object = other.object;
        this->id = other.id;
        this->assignName(other.name);
    }
    return *this;
}

template<class T>
NamedObject<T>::~NamedObject() {
    this->freeMemory();
}

template<class T>
const char *NamedObject<T>::getName() const {
    return this->name;
}

template<class T>
T &NamedObject<T>::getObject() const {
    return this->object;
}

template<class T>
void NamedObject<T>::assignName(const char *newName) {
    this->name = new char[strlen(newName) + 1];    // assign one extra character for terminating character
    strcpy(this->name, newName);                   // copy the characters, no danger of overflow here
}

template<class T>
void NamedObject<T>::freeMemory() {
    delete[] this->name;
}

template<class T>
unsigned int NamedObject<T>::getID() const {
    return this->id;
}


#endif //EXAM_NAMEDOBJECT_HPP
