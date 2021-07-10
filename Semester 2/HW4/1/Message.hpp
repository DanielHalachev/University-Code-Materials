//
// Created by User on 24.5.2021 г..
//

#ifndef HW4_MESSAGE_HPP
#define HW4_MESSAGE_HPP

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// Message is an abstraction over a simple data point, which
// is sent from a Publisher to a Subscriber
class Message {
public:
    // Constructor
    Message(const int &data = 0);

    // data is the data point encapsulated in the message
    // Should never be changed once initialized
    const int data;
};

#endif //HW4_MESSAGE_HPP
