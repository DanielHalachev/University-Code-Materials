//
// Created by User on 29.5.2021 г..
//

#ifndef EXERCISES_MYSTRING_HPP
#define EXERCISES_MYSTRING_HPP


#include <cstddef>

class MyString {
public:
    MyString(const char *content = "");

    MyString(const MyString &other);

    MyString &operator=(const MyString &other);

    ~MyString();

    size_t length() const;

    void push_back(const char &ch);

    bool empty() const;

    void clear();

    const char *c_str() const;

    const char &operator[](const unsigned int &index) const;

    char &operator[](const unsigned int &index);

    friend MyString operator+(const MyString &lhs, const MyString &rhs);

    friend MyString operator+(const MyString &lhs, const char *rhs);

    MyString &operator+=(const MyString &other);

    MyString &operator+=(const char *other);

    bool operator==(const MyString &other);

private:
    char *str;
};


#endif //EXERCISES_MYSTRING_HPP
