//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_TSHIRT_HPP
#define EXERCISES_TSHIRT_HPP


#include "StoreItem.hpp"

class TShirt : public StoreItem {
public:
    TShirt(const std::string &name = "", const double &price = 0, const std::string &color = "",
           const std::string &size = "");

    TShirt *clone() const override;

    std::string getColor() const;

    std::string getSize() const;

    void setColor(const std::string &newColor);

    void setSize(const std::string &newSize);

    bool operator==(const TShirt &other);


private:
    std::string color;
    std::string size;
};


#endif //EXERCISES_TSHIRT_HPP
