//
// Created by User on 24.5.2021 г..
//

#ifndef HW4_REPOSITORY_HPP
#define HW4_REPOSITORY_HPP

#include "Averager.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// Repository is the single place where Subscribers will
// be stored. A Repository has ownership of the Subscribers
// stored inside it.
// The only way to access the available Subscribers in the
// repository is via the Subscriber's unique id.
// id's are guaranteed to be unique
class Repository {
public:
    Repository() = default;

    Repository(const Repository &other);

    Repository &operator=(const Repository &other);

    ~Repository();

    // add registers a new Subscriber in the Repository
    void add(Subscriber *subscriber);

    // acts as unsubscribe
    void remove(Subscriber *subscriber);

    // signals all subs in the repository
    void signal(const Message &message) const;

    // get returns a Subscriber in the Repository if a
    // Subscriber with the given id exists.
    // Returns nullptr otherwise
    Subscriber *get(const std::string &id);

private:
    // holds all subscribers
    std::vector<Subscriber *> subscribers;
};

#endif //HW4_REPOSITORY_HPP
