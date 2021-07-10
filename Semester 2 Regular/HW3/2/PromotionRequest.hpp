//
// Created by User on 3.5.2021 г..
//

#ifndef HW4_PROMOTIONREQUEST_HPP
#define HW4_PROMOTIONREQUEST_HPP


#include "Request.hpp"

class PromotionRequest : public Request {
private:
    double amount;
public:
    PromotionRequest(const std::string &sender, const double &amount);

    double getAmount() const;
};


#endif //HW4_PROMOTIONREQUEST_HPP
