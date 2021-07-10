//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_SHOES_HPP
#define EXERCISES_SHOES_HPP


#include "StoreItem.hpp"

class Shoes : public StoreItem {
public:
    Shoes(const std::string &name = "", const double &price = 0, const std::string &color = "",
          const std::string &type = "", const int &size = 0);

    Shoes *clone() const override;

    std::string getShoeType() const;

    std::string getColor() const;

    int getSize() const;

    void setType(const std::string &newType);

    void setColor(const std::string &newColor);

    void setSize(const int &newSize);

private:
    std::string type;
    std::string color;
    int size;
};


#endif //EXERCISES_SHOES_HPP
