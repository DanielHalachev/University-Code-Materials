//
// Created by User on 14.6.2021 г..
//

#include "StoreProduct.hpp"

#include <utility>

StoreProduct::StoreProduct(std::string name, std::string code, const double &price)
        : name(std::move(name)), code(std::move(code)), price(price) {
}

std::string StoreProduct::getName() const {
    return this->name;
}

std::string StoreProduct::getCode() const {
    return this->code;
}

double StoreProduct::getPrice() const {
    return this->price;
}

std::ostream &operator<<(std::ostream &out, const StoreProduct *const &product) {
    product->print(out);
    return out;
}
