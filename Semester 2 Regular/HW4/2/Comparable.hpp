
#ifndef HW4_COMPARABLE_HPP
#define HW4_COMPARABLE_HPP

#include <string>

class Comparable {
public:
    Comparable() = default;

    // virtual function to be inherited
    virtual bool operator==(const Comparable *other) const = 0;

    virtual bool operator!=(const Comparable *other) const = 0;

    virtual ~Comparable() = default;
};

#endif //HW4_COMPARABLE_HPP
