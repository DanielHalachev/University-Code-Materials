//
// Created by User on 14.6.2021 г..
//

#ifndef EXERCISES_STOREPRODUCT_HPP
#define EXERCISES_STOREPRODUCT_HPP


#include <string>
#include "iostream"

class StoreProduct {
public:
    explicit StoreProduct(std::string name = "", std::string code = "", const double &price = 0);

    virtual ~StoreProduct() = default;

    virtual StoreProduct *clone() const = 0;

    std::string getName() const;

    std::string getCode() const;

    double getPrice() const;

    friend std::ostream &operator<<(std::ostream &out, const StoreProduct *const &product);

    virtual void print(std::ostream &out) const = 0;

protected:
    std::string name;
    std::string code;
    double price;
};


#endif //EXERCISES_STOREPRODUCT_HPP
