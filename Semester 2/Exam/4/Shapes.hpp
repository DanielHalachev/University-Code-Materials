//
// Daniel Halachev
// Clion GCC
//

#ifndef EXAM_SHAPES_HPP
#define EXAM_SHAPES_HPP


#include "Circle.hpp"
#include "Rectangle.hpp"
#include "vector"

class Shapes {
public:
    Shapes() = default;

    Shapes(const Shapes &other);

    Shapes &operator=(const Shapes &other);

    ~Shapes();

    void addCircle(Circle *circle);

    void addRectangle(Rectangle *rectangle);

    // I wasn't sure if the task demanded this method implicitly so I added it to make sure
    void addShape(const BaseShape *shape);

    // this method isn't required but the task would make more sense with it
    bool removeShape(const unsigned int &index);

    double getRectangleSizes();

    double getCircleSizes();

    BaseShape *getShape(const unsigned int &index);


private:
    std::vector<BaseShape *> shapes;

    void freeMemory();
};


#endif //EXAM_SHAPES_HPP
