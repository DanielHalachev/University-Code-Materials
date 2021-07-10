//
// Created by User on 25.5.2021 г..
//

#ifndef HW4_SERIALIZABLE_HPP
#define HW4_SERIALIZABLE_HPP


#include <string>

class Serializable {
public:
    Serializable() = default;

    // virtual function to be inherited
    virtual std::string to_string() const = 0;

    virtual void from_string(const std::string &myString) = 0;

    virtual ~Serializable() = default;
};


#endif //HW4_SERIALIZABLE_HPP
