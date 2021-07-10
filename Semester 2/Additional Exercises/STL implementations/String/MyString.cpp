//
// Created by User on 29.5.2021 г..
//

#include <cstring>
#include <stdexcept>
#include "MyString.hpp"

MyString::MyString(const char *content) {
    this->str = new char[strlen(content) + 1];
    strcpy(this->str, content);
}

MyString::MyString(const MyString &other) {
    this->str = new char[strlen(other.str) + 1];
    strcpy(this->str, other.str);
}

MyString &MyString::operator=(const MyString &other) {
    if (this != &other) {
        delete[] this->str;
        this->str = new char[strlen(other.str) + 1];
        strcpy(this->str, other.str);
    }
    return *this;
}

MyString::~MyString() {
    delete[] this->str;
}

size_t MyString::length() const {
    return strlen(this->str);
}

void MyString::push_back(const char &ch) {
    char *newString = new char[strlen(this->str) + 2];
    strcpy(newString, this->str);
    newString[strlen(this->str)] = ch;
    newString[strlen(this->str) + 1] = '\0';
    delete[] this->str;
    this->str = newString;
}

bool MyString::empty() const {
    return strlen(this->str) == 0;
}

void MyString::clear() {
    delete[] this->str;
    this->str = new char[1];
    this->str[0] = '\0';
}

const char *MyString::c_str() const {
    return this->str;
}

const char &MyString::operator[](const unsigned int &index) const {
    if (index > strlen(this->str)) {
        throw std::out_of_range("Index is bigger than length");
    }
    return this->str[index];
}

char &MyString::operator[](const unsigned int &index) {
    if (index > strlen(this->str)) {
        throw std::out_of_range("Index is bigger than length");
    }
    return this->str[index];
}

MyString operator+(const MyString &lhs, const MyString &rhs) {
    MyString m1;
    size_t size1 = strlen(lhs.str);
    size_t size2 = strlen(rhs.str);
    char *str = new char[size1 + size2 + 1];
    for (int i = 0; i < size1; i++) {
        str[i] = lhs.str[i];
    }
    for (int i = 0; i < size2; i++) {
        str[i + size1] = rhs.str[i];
    }
    str[size1 + size2] = '\0';
    delete[] m1.str;
    m1.str = str;
    return m1;
}

MyString &MyString::operator+=(const MyString &other) {
    int size1 = strlen(this->str);
    int size2 = strlen(other.str);
    char *string = new char[size1 + size2 + 1];
    for (int i = 0; i < size1; i++) {
        string[i] = this->str[i];
    }
    for (int i = 0; i < size2; i++) {
        string[size1 + i] = other.str[i];
    }
    string[size1 + size2] = '\0';
    delete[] this->str;
    this->str = string;
    return *this;
}

bool MyString::operator==(const MyString &other) {
    return !strcmp(this->str, other.str);
}

MyString operator+(const MyString &lhs, const char *rhs) {
    MyString m1;
    size_t size1 = strlen(lhs.str);
    size_t size2 = strlen(rhs);
    char *str = new char[size1 + size2 + 1];
    for (int i = 0; i < size1; i++) {
        str[i] = lhs.str[i];
    }
    for (int i = 0; i < size2; i++) {
        str[size1 + i] = rhs[i];
    }
    str[size1 + size2] = '\0';
    delete[] m1.str;
    m1.str = str;
    return m1;
}

MyString &MyString::operator+=(const char *other) {
    int size1 = strlen(this->str);
    int size2 = strlen(other);
    char *string = new char[size1 + size2 + 1];
    for (int i = 0; i < size1; i++) {
        string[i] = this->str[i];
    }
    for (int i = 0; i < size2; i++) {
        string[size1 + i] = other[i];
    }
    string[size1 + size2] = '\0';
    delete[] this->str;
    this->str = string;
    return *this;
}
