//
// Daniel Halachev, #62547
// Clion, GCC
//

#ifndef EXAM_BASESHAPE_HPP
#define EXAM_BASESHAPE_HPP

// for shape color
#include <string>

class BaseShape {
public:
    explicit BaseShape(const std::string &color = "");

    std::string getColor() const;

    // I added this method to make sure the task makes sense
    void setColor(const std::string &newColor);

    // to be defined in inherited classes
    virtual double getSize() const = 0;

    // polymorphism requires this
    virtual ~BaseShape() = default;

    virtual BaseShape *clone() const = 0;

protected:
    std::string color;
};


#endif //EXAM_BASESHAPE_HPP
