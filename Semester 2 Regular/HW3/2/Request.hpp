//
// Created by User on 3.5.2021 г..
//

#ifndef HW4_REQUEST_HPP
#define HW4_REQUEST_HPP


#include <string>

class Request {
protected:
    std::string message;
    std::string sender;
    int ID;
    static int objectCount;
public:
    Request(const std::string &message, const std::string &sender);

    std::string getMessage() const;

    std::string getSender() const;

    static int getCount();

    int getID() const;
};


#endif //HW4_REQUEST_HPP
