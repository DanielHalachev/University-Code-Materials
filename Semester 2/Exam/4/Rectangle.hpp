//
// Daniel Halachev
// Clion GCC
//

#ifndef EXAM_RECTANGLE_HPP
#define EXAM_RECTANGLE_HPP

#include "BaseShape.hpp"

class Rectangle : public BaseShape {
public:
    explicit Rectangle(const double &width = 0, const double &height = 0, const std::string &color = "");

    double getWidth() const;

    double getHeight() const;

    //no setters required but I'll add them to make the program complete
    void setWidth(const double &newWidth);

    void setHeight(const double &newHeight);

    double getSize() const override;

    Rectangle *clone() const override;

private:
    double width;
    double height;
};


#endif //EXAM_RECTANGLE_HPP
