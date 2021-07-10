//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_STOREITEM_HPP
#define EXERCISES_STOREITEM_HPP

#include <string>

enum ProductType {
    T_SHIRT, SHOES, NONE
};

class StoreItem {
public:
    StoreItem(const std::string &name = "", const ProductType &productType = NONE, const double &price = 0);

    std::string getName() const;

    ProductType getType() const;

    double getPrice() const;

    void setName(const std::string &newName);

    void setType(const ProductType &type);

    void setPrice(const double &newPrice);

    virtual void print() const;

    virtual StoreItem *clone() const = 0;

    virtual ~StoreItem() = default;

protected:
    std::string name;
    ProductType productType;
    double price;
};


#endif //EXERCISES_STOREITEM_HPP
