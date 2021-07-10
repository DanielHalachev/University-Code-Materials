
#ifndef HW4_DEBUG_HPP
#define HW4_DEBUG_HPP

#include <string>

class Debug {
public:
    Debug() = default;

    //virtual function to be inherited
    virtual std::string debug_print() const = 0;

    virtual ~Debug() = default;
};


#endif //HW4_DEBUG_HPP
