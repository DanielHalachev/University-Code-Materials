//
// Daniel Halachev
// Clion GCC
//

#ifndef EXAM_CIRCLE_HPP
#define EXAM_CIRCLE_HPP

// I wasn't sure which PI from <cmath> to chose;
#define PI 3.14

#include "BaseShape.hpp"

class Circle : public BaseShape {
public:
    explicit Circle(const double &radius = 0, const std::string &color = "");

    double getRadius() const;

    void setRadius(const double &newRadius);

    double getSize() const override;

    Circle *clone() const override;

private:
    double radius;
};


#endif //EXAM_CIRCLE_HPP
