//
// Created by User on 3.5.2021 г..
//

#include "PromotionRequest.hpp"

PromotionRequest::PromotionRequest(const std::string &sender, const double &amount) : Request("I want a raise!",
                                                                                              sender) {
    this->amount = amount;
}

double PromotionRequest::getAmount() const {
    return this->amount;
}
